#include "fenprincipale.h"
#include "ui_fenprincipale.h"

#define ENDL                "\r\n"
#define WOW_EXE_POS         "/Wow.exe"
#define REALMLIST_POS_WOTLK "/Data/frFR/realmlist.wtf"
#define REALMLIST_POS_BC    "/realmlist.wtf"
#define CACHE_POS           "/Cache/WDB/frFR/"

FenPrincipale::FenPrincipale(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FenPrincipale),
        m_fichierRealmlist("realmlist.dat")
{
    ui->setupUi(this);

    //Ouverture du fichier de sauvegarde des realmlists.
    m_fichierRealmlist.open(QIODevice::ReadWrite);
    //Premier chargement.
    ChargerRealmlists();
}

FenPrincipale::~FenPrincipale()
{
    //Fermeture du fichier de sauvegarde des realmlists.
    m_fichierRealmlist.close();
    delete ui;
}

void FenPrincipale::ChargerRealmlists()
{
    //Vérification du fichier de sauvegarde
    if (!m_fichierRealmlist.isReadable())
    {
        QMessageBox::critical(this, tr("EasyRealm - Erreur"), tr("Impossible de charger les realmlists depuis le fichier."));
        return;
    }

    //On supprime tous les realmlists enregistrés dans l'UI
    ui->ui_listeRealmlist->clear();
    m_listeRealmlist.clear();

    //Positionnement en début de fichier
    m_fichierRealmlist.reset();
    //Lecture du realmlist précédemment sélectionné.
    //Suppression des caractères de retour à la ligne
    int row = ((QString) m_fichierRealmlist.readLine()).remove(ENDL).toInt();

    //Lecture du dossier WoW
    QString dossierWoW = ((QString) m_fichierRealmlist.readLine()).remove(ENDL);
    ui->ui_dossierWoW->setText(dossierWoW);
    //Vérification du dossier WoW.
    VerifierDossierWoW();


    //

    //Chargement de tous les realmlists
    while (!m_fichierRealmlist.atEnd())
    {
        Realmlist realmlist(m_fichierRealmlist);

        //Vérification des doublons
        bool ok = !EstUnDoublon(realmlist.getTitre());
        while (!ok)
        {
            QMessageBox::warning(this, tr("EasyRealm"), tr("Erreur de chargement: le nom d'un realmlist est en conflit avec un autre, veuillez le renommer."));
            //Ouverture de la fenêtre d'édition
            //Le bouton Annuler est grisé en mode édition de titre: on ne peut que modifier le titre.
            FenEditer fen(this, &realmlist, &ok, true);
            fen.exec();

            if (ok)
                QMessageBox::information(this, tr("EasyRealm"), tr("Realmlist édité avec succès."));
        }
        //Assignation à la QMap
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
    }

    //Mise à jour de l'UI à proprement parler.
    ui->ui_listeRealmlist->addItems(m_listeRealmlist.keys());
    ui->ui_listeRealmlist->setCurrentRow(row);
}

void FenPrincipale::SauvegarderRealmlists()
{
    //Vérif du fichier de sauvegarde
    if (!m_fichierRealmlist.isWritable())
    {
        QMessageBox::critical(this, tr("Easyrealm - Erreur"), tr("Impossible de charger les realmlists depuis le fichier."));
        return;
    }

    //On vide le fichier
    m_fichierRealmlist.resize(0);

    //Enregistrement du realmlist actuellement sélectionné.
    QString row;
    m_fichierRealmlist.write(QByteArray::number(ui->ui_listeRealmlist->currentRow()));
    m_fichierRealmlist.write(ENDL);

    //Enregistrement du dossier WoW
    m_fichierRealmlist.write(ui->ui_dossierWoW->text().toAscii());
    m_fichierRealmlist.write(ENDL);

    //Enregistrement des realmlists
    foreach (Realmlist realmlist, m_listeRealmlist)
        realmlist.ecrireRealmlistDansFichier(m_fichierRealmlist);
}

void FenPrincipale::RechargerRealmlists()
{
    //Mise à jour du fichier de sauvegarde
    SauvegarderRealmlists();
    //Puis mise à jour de l'UI
    ChargerRealmlists();
}

bool FenPrincipale::VerifierDossierWoW(bool forcerChangement)
{
    bool afficherMessage = !forcerChangement;
    QString dossierWoW = ui->ui_dossierWoW->text();

    //Si on n'affiche pas le message, c'est que le changement a été forcé.
    while ((!QFile::exists(dossierWoW + WOW_EXE_POS) && !dossierWoW.isEmpty()) || !afficherMessage)
    {
        if (afficherMessage)
            QMessageBox::warning(this, tr("EasyRealm"),
                                 tr("Le dossier World of Warcraft n'existe pas/plus dans l'emplacement enregistré ou le dossier n'est pas un dossier World of Warcraft.\n"
                                    "Veuillez sélectionner le dossier World of Warcraft."));
        else
            afficherMessage = true;
        //Si l'utilisateur clique sur Annuler, dossierWoW sera vide.
        dossierWoW = QFileDialog::getExistingDirectory(this, tr("Choisissez le dossier d'installation de Worlf of Warcraft"), dossierWoW);
    }

    if (!(dossierWoW.isEmpty() && forcerChangement))
        ui->ui_dossierWoW->setText(dossierWoW);

    if (QFile::exists(ui->ui_dossierWoW->text() + "\\Wow.exe"))
    {
        ui->ui_btnLancerWoW->setEnabled(true);
        return true;
    }
    else
    {
        ui->ui_btnLancerWoW->setEnabled(false);
        return false;
    }
}

void FenPrincipale::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FenPrincipale::on_ui_btnQuitter_released()
{
    //Sauvegarde avant la fermeture
    SauvegarderRealmlists();
    this->close();
}

void FenPrincipale::on_ui_listeRealmlist_currentTextChanged(QString currentText)
{
    //Mise à jour de l'aperçu du realmlist
    Realmlist realmlist = m_listeRealmlist.value(currentText);
    ui->ui_contenuRealmlist->setText(realmlist.getRealmlistData());
}

void FenPrincipale::on_ui_btnAjouter_released()
{
    //Création du nouveau realmlist
    Realmlist realmlist;
    bool ok = true;
    bool doublon = false;

    do
    {
        //Affichage de la fenêtre d'ajout
        FenNouveau fen(this, &realmlist, &ok, doublon);
        fen.exec();

        doublon = EstUnDoublon(realmlist.getTitre());
        if (ok && doublon)
            QMessageBox::warning(this, tr("EasyRealm"), tr("Le nom du nouveau realmlist est déjà utilisé. Veuillez le renommer."));

        //Si n'a pas annulé et qu'on n'a pas de doublon
        if (ok && !doublon)
        {
            //On ajoute le realmlist résultant de la fenêtre d'ajout
            m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
            //On met à jour le fichier et l'UI
            RechargerRealmlists();
            QMessageBox::information(this, tr("EasyRealm"), tr("Nouveau realmlist ajouté avec succès."));
        }
    }
    while(ok && doublon);
}

void FenPrincipale::on_ui_btnEditer_released()
{
    //Vérifications de la liste des realmlists.
    if (m_listeRealmlist.isEmpty())
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("La liste de realmlists est vide."));
        return;
    }
    if (ui->ui_listeRealmlist->currentRow() == -1)
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("Aucun realmlist n'est sélectionné."));
        return;
    }

    //Chargement du realmlist à éditer
    Realmlist realmlist = m_listeRealmlist.value(ui->ui_listeRealmlist->currentItem()->text());
    bool ok;
    //Ouverture de la fenêtre d'édition
    FenEditer fen(this, &realmlist, &ok);
    fen.exec();

    //Si le realmlist a été modifié
    if (ok)
    {
        //On supprime l'ancien et on ajoute le nouveau
        m_listeRealmlist.remove(ui->ui_listeRealmlist->currentItem()->text());
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
        //Mise à jour
        RechargerRealmlists();
        QMessageBox::information(this, tr("EasyRealm"), tr("Realmlist édité avec succès."));
    }
}

void FenPrincipale::on_ui_btnSupprimer_released()
{
    //Vérifications de la liste des realmlists.
    if (m_listeRealmlist.isEmpty())
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("La liste de realmlists est vide."));
        return;
    }
    if (ui->ui_listeRealmlist->currentRow() == -1)
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("Aucun realmlist n'est sélectionné."));
        return;
    }

    //Message de confirmation
    int reponse = QMessageBox::warning(this, tr("EasyRealm"), tr("Êtes-vous sur de vouloir supprimer le realmlist sélectionné ?"), QMessageBox::Yes, QMessageBox::No);

    //Si l'utilisateur confirme
    if (reponse == QMessageBox::Yes)
    {
        //On supprimer et on actualise le fichier & l'UI
        m_listeRealmlist.remove(ui->ui_listeRealmlist->currentItem()->text());
        RechargerRealmlists();
    }
}

void FenPrincipale::on_ui_btnParcourir_released()
{
    VerifierDossierWoW(true);
}

void FenPrincipale::on_ui_btnLancerWoW_released()
{
    //Si on a un mauvais dossier et que l'utilisateur ne nous donne pas de nouvelle adresse, annuler.
    if (!VerifierDossierWoW())
        return;

    //Vérifications de la liste des realmlists.
    if (m_listeRealmlist.isEmpty())
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("La liste de realmlists est vide."));
        return;
    }
    if (ui->ui_listeRealmlist->currentRow() == -1)
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("Aucun realmlist n'est sélectionné."));
        return;
    }

    QString dossierWoW = ui->ui_dossierWoW->text();

    //Ecriture du realmlist.
    QFile realmlistFichier(dossierWoW + REALMLIST_POS_WOTLK, this);
    Realmlist realmlist = m_listeRealmlist.value(ui->ui_listeRealmlist->currentItem()->text());
    realmlistFichier.open(QIODevice::Truncate | QIODevice::WriteOnly);
    realmlistFichier.write(realmlist.getRealmlistData().toAscii());

    //Suppression du cache
    QDir cacheDir = dossierWoW + CACHE_POS;
    foreach(QString fichier, cacheDir.entryList())
    {
        QFile::remove(dossierWoW + CACHE_POS + fichier);
    }

    QString program = "\"" + dossierWoW + WOW_EXE_POS "\"";

    //TODO: Modifier ça, c'est moche...
//    program = ((QString) "START /MAX \"\" " + program);
//    system(program.toStdString().c_str());
    QProcess Wow;
    Wow.startDetached(program);
}
