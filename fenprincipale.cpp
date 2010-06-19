#include "fenprincipale.h"
#include "ui_fenprincipale.h"

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
    //V�rification du fichier de sauvegarde
    if (!m_fichierRealmlist.isReadable())
    {
        QMessageBox::critical(this, tr("EasyRealm - Erreur"), tr("Impossible de charger les realmlists depuis le fichier."));
        return;
    }

    //On supprime tous les realmlists enregistr�s dans l'UI
    ui->ui_listeRealmlist->clear();
    m_listeRealmlist.clear();

    //Positionnement en d�but de fichier
    m_fichierRealmlist.reset();
    //Lecture du realmlist pr�c�demment s�lectionn�.
    QString sRow = m_fichierRealmlist.readLine();
    //Suppression des caract�res de retour � la ligne
    sRow.chop(2);
    int row = sRow.toInt();

    //Chargement de tous les realmlists
    while (!m_fichierRealmlist.atEnd())
    {
        Realmlist realmlist(m_fichierRealmlist);
        //Assignation � la QMap
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
    }

    //Mise � jour de l'UI � proprement parler.
    ui->ui_listeRealmlist->addItems(m_listeRealmlist.keys());
    ui->ui_listeRealmlist->setCurrentRow(row);
}

void FenPrincipale::SauvegarderRealmlists()
{
    //V�rif du fichier de sauvegarde
    if (!m_fichierRealmlist.isWritable())
    {
        QMessageBox::critical(this, tr("Easyrealm - Erreur"), tr("Impossible de charger les realmlists depuis le fichier."));
        return;
    }

    //On vide le fichier
    m_fichierRealmlist.resize(0);

    //Enregistrement du realmlist actuellement s�lectionn�.
    QString row;
    m_fichierRealmlist.write(QByteArray::number(ui->ui_listeRealmlist->currentRow()));
    m_fichierRealmlist.write("\r\n");

    //Enregistrement des realmlists
    foreach (Realmlist realmlist, m_listeRealmlist)
        realmlist.ecrireRealmlistDansFichier(m_fichierRealmlist);
}

void FenPrincipale::RechargerRealmlists()
{
    //Mise � jour du fichier de sauvegarde
    SauvegarderRealmlists();
    //Puis mise � jour de l'UI
    ChargerRealmlists();
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
    //Mise � jour de l'aper�u du realmlist
    Realmlist realmlist = m_listeRealmlist.value(currentText);
    ui->ui_contenuRealmlist->setText(realmlist.getRealmlistData());
}

void FenPrincipale::on_ui_btnAjouter_released()
{
    //Cr�ation du nouveau realmlist
    Realmlist realmlist;
    bool ok;
    //Affichage de la fen�tre d'ajout
    FenNouveau fen(this, &realmlist, &ok);
    fen.exec();

    //Si l'utilisateur n'a pas annul�
    if (ok)
    {
        //On ajoute le realmlist r�sultant de la fen�tre d'ajout
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
        //On met � jour le fichier et l'UI
        RechargerRealmlists();
        QMessageBox::information(this, tr("EasyRealm"), tr("Nouveau realmlist ajout� avec succ�s."));
    }
}

void FenPrincipale::on_ui_btnSupprimer_released()
{
    //Message de confirmation
    int reponse = QMessageBox::warning(this, tr("EasyRealm"), tr("�tes-vous sur de vouloir supprimer le realmlist s�lectionn� ?"), QMessageBox::Yes, QMessageBox::No);

    //Si l'utilisateur confirme
    if (reponse == QMessageBox::Yes)
    {
        //On supprimer et on actualise le fichier & l'UI
        m_listeRealmlist.remove(ui->ui_listeRealmlist->currentItem()->text());
        RechargerRealmlists();
    }
}

void FenPrincipale::on_ui_btnEditer_released()
{
    //Chargement du realmlist � �diter
    Realmlist realmlist = m_listeRealmlist.value(ui->ui_listeRealmlist->currentItem()->text());
    bool ok;
    //Ouverture de la fen�tre d'�dition
    FenEditer fen(this, &realmlist, &ok);
    fen.exec();

    //Si le realmlist a �t� modifi�
    if (ok)
    {
        //On supprime l'ancien et on ajoute le nouveau
        m_listeRealmlist.remove(ui->ui_listeRealmlist->currentItem()->text());
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
        //Mise � jour
        RechargerRealmlists();
        QMessageBox::information(this, tr("EasyRealm"), tr("Realmlist �dit� avec succ�s."));
    }
}
