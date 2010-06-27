#include "fenoptions.h"
#include "ui_fenoptions.h"

#define ENDL                "\r\n"
#define WOW_EXE_POS         "/Wow.exe"

FenOptions::FenOptions(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::FenOptions),
        m_parent(parent)
{
    ui->setupUi(this);

    //Chargements.
    if (parent)
    {
        //Vider le cache ?
        ui->ui_viderCache->setChecked(((FenPrincipale*) parent)->getViderCache());
        //Eteindre ER ?
        ui->ui_eteindreER->setChecked(((FenPrincipale*) parent)->getEteindreER());
        //Liste dossiers WoW
        m_listeDossiersWoW = ((FenPrincipale*) parent)->getListeDossiersWoW();
        //Remplissage de l'affichage
        rafraichirUI();
    }
}

FenOptions::~FenOptions()
{
    delete ui;
}

void FenOptions::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FenOptions::rafraichirUI()
{
    ui->ui_listeDossiers->clear();
    QMap<QString, QString>::const_iterator i = m_listeDossiersWoW.constBegin();
    while (i != m_listeDossiersWoW.constEnd())
    {
        QString texte;
        texte += i.key() + ENDL;
        texte += i.value();
        ui->ui_listeDossiers->addItem(texte);
        i++;
    }
}

void FenOptions::on_ui_btnAnnuler_released()
{
    this->close();
}

void FenOptions::on_ui_btnAjouter_released()
{
    QString nomDossierWoW;
    QString dossierWoW;

    //On demande le nom de l'installation à l'utilisateur.
    bool ok, doublon = true;
    //Tant qu'il n'y a pas de doublon et que l'utilisateur clique sur OK
    while (!ok || doublon || nomDossierWoW.isEmpty())
    {
        nomDossierWoW = QInputDialog::getText(this, tr("EasyRealm"), tr("Entrez le nom de la nouvelle installation"), QLineEdit::Normal, "", &ok);

        //Si l'utilisateur a cliqué sur Annuler, on quitte.
        if (!ok)
            return;
        //Vérification des doublons.
        doublon = estUnDoublon(nomDossierWoW);
        if (doublon)
            QMessageBox::warning(this, tr("EasyRealm"), tr("Ce nom d'installation est déjà utilisé."));
    }


    //On demande à l'utilisateur le dossier tant qu'il n'a pas cliqué sur Annuler ou qu'il a sélectionné un mauvais dossier.
    while (!QFile::exists(dossierWoW + WOW_EXE_POS))
    {
        //Si l'utilisateur clique sur Annuler, dossierWoW sera vide.
        dossierWoW = QFileDialog::getExistingDirectory(this, tr("Choisissez le dossier d'installation de World of Warcraft"), dossierWoW);

        //On vérifie si l'utilisatuer a cliqué sur Annuler.
        if (dossierWoW.isEmpty())
            return;

        //On vérifie que le dossier est correct.
        if (!QFile::exists(dossierWoW + WOW_EXE_POS))
            QMessageBox::warning(this, tr("EasyRealm"),
                                 tr("Le dossier World of Warcraft n'existe pas/plus dans l'emplacement enregistré ou le dossier n'est pas un dossier World of Warcraft.\n"
                                    "Veuillez sélectionner le dossier World of Warcraft."));
    }

    if (QFile::exists(dossierWoW + WOW_EXE_POS))
    {
        m_listeDossiersWoW.insert(nomDossierWoW, dossierWoW);
        QMessageBox::information(this, tr("EasyRealm"), tr("Nouvelle installation de World of Warcraft ajoutée avec succès."));
        rafraichirUI();
        return;
    }
}

void FenOptions::on_ui_btnEnregistrer_released()
{
    FenPrincipale* parent = (FenPrincipale*) m_parent;
    parent->setViderCache(ui->ui_viderCache->isChecked());
    parent->setEteindreER(ui->ui_eteindreER->isChecked());
    parent->setListeDossiersWoW(m_listeDossiersWoW);
    parent->RechargerRealmlists();

    this->close();
}

void FenOptions::on_ui_btnSupprimer_released()
{
    //Vérifications de la liste des dossiers.
    if (m_listeDossiersWoW.isEmpty())
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("La liste de dossiers World of Warcraft est vide."));
        return;
    }
    if (ui->ui_listeDossiers->currentRow() == -1)
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("Aucun dossier World of Warcraft n'est sélectionné."));
        return;
    }

    //Message de confirmation
    int reponse = QMessageBox::warning(this, tr("EasyRealm"), tr("Êtes-vous sur de vouloir supprimer le dossier World of Warcraft sélectionné ?"), QMessageBox::Yes, QMessageBox::No);

    //Si l'utilisateur confirme
    if (reponse == QMessageBox::Yes)
    {
        //On supprimer et on actualise le fichier & l'UI
        m_listeDossiersWoW.remove(ui->ui_listeDossiers->currentItem()->text().section(ENDL, 0, 0));
        rafraichirUI();
    }


}

void FenOptions::on_ui_btnEditer_released()
{
    //Vérifications de la liste des dossiers.
    if (m_listeDossiersWoW.isEmpty())
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("La liste de dossiers World of Warcraft est vide."));
        return;
    }
    if (ui->ui_listeDossiers->currentRow() == -1)
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("Aucun dossier World of Warcraft n'est sélectionné."));
        return;
    }

    //Initialisation des données.
    bool premiereBoucle = true;
    QString nomDossierWoW = ui->ui_listeDossiers->currentItem()->text().section(ENDL, 0, 0);
    QString dossierWoW = ui->ui_listeDossiers->currentItem()->text().section(ENDL, 1, 1);

    //On demande à l'utilisateur le dossier tant qu'il n'a pas cliqué sur Annuler ou qu'il a sélectionné un mauvais dossier.
    while (!QFile::exists(dossierWoW + WOW_EXE_POS) || premiereBoucle)
    {
        premiereBoucle = false;
        //Si l'utilisateur clique sur Annuler, dossierWoW sera vide.
        dossierWoW = QFileDialog::getExistingDirectory(this, tr("Choisissez le dossier d'installation de World of Warcraft"), dossierWoW);

        //On vérifie si l'utilisatuer a cliqué sur Annuler.
        if (dossierWoW.isEmpty())
            return;

        //On vérifie que le dossier est correct.
        if (!QFile::exists(dossierWoW + WOW_EXE_POS))
            QMessageBox::warning(this, tr("EasyRealm"),
                                 tr("Le dossier World of Warcraft n'existe pas/plus dans l'emplacement enregistré ou le dossier n'est pas un dossier World of Warcraft.\n"
                                    "Veuillez sélectionner le dossier World of Warcraft."));
    }

    m_listeDossiersWoW.remove(nomDossierWoW);
    m_listeDossiersWoW.insert(nomDossierWoW, dossierWoW);
    rafraichirUI();
}
