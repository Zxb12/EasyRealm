#include "fenprincipale.h"
#include "ui_fenprincipale.h"

#define ENDL                        "\r\n"
#define MARQUEUR_FIN_DOSSIERS       "FIN_DOSSIERS_WOW"
#define MARQUEUR_VIDER_CACHE        "VIDER_CACHE"
#define MARQUEUR_PAS_VIDER_CACHE    "PAS_VIDER_CACHE"

#define WOW_EXE_POS                 "/Wow.exe"
#define REALMLIST_POS_WOTLK         "/Data/frFR/realmlist.wtf"
#define REALMLIST_POS_BC            "/realmlist.wtf"
#define CACHE_POS                   "/Cache/WDB/frFR/"

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

    //Lecture du status du vidage de cache.
    m_viderCache = (((QString) m_fichierRealmlist.readLine()).remove(ENDL) == "VIDER_CACHE");

    //Lecture du dossier WoW
    QString nomDossierWoW;
    //Tant qu'on est pas arrivés au marqueur de fin
    while ((nomDossierWoW = ((QString) m_fichierRealmlist.readLine()).remove(ENDL)) != "FIN_DOSSIERS_WOW" && !m_fichierRealmlist.atEnd())
    {
        //On lit le nom puis le dossier, on les stocke.
        m_listeDossiersWoW.insert(nomDossierWoW, ((QString) m_fichierRealmlist.readLine()).remove(ENDL));
    }
    //Vérification des dossiers WoW.
    VerifierDossierWoW();

    //Chargement de tous les realmlists
    while (!m_fichierRealmlist.atEnd())
    {
        Realmlist realmlist(m_fichierRealmlist);

        //Vérification du dossier associé.
        if (!m_listeDossiersWoW.contains(realmlist.getNomDossier()))
            realmlist.setDossierExiste(false);

        //Vérification des doublons
        bool ok = !EstUnDoublon(realmlist.getTitre());
        while (!ok)
        {
            QMessageBox::warning(this, tr("EasyRealm"), tr("Erreur de chargement: le nom d'un realmlist est en conflit avec un autre, veuillez le renommer."));
            //Ouverture de la fenêtre d'édition
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
    m_fichierRealmlist.write(QByteArray::number(ui->ui_listeRealmlist->currentRow()));
    m_fichierRealmlist.write(ENDL);

    //Enregistrement du status du vidage du cache
    if (m_viderCache)
        m_fichierRealmlist.write(MARQUEUR_VIDER_CACHE);
    else
        m_fichierRealmlist.write(MARQUEUR_PAS_VIDER_CACHE);
    m_fichierRealmlist.write(ENDL);

    //Enregistrement des dossiers WoW
    QMap<QString, QString>::const_iterator i = m_listeDossiersWoW.constBegin();
    while (i != m_listeDossiersWoW.constEnd())
    {
        m_fichierRealmlist.write(i.key().toAscii());
        m_fichierRealmlist.write(ENDL);
        m_fichierRealmlist.write(i.value().toAscii());
        m_fichierRealmlist.write(ENDL);
        ++i;
    }
    //Enregistrement du marqueur de fin.
    m_fichierRealmlist.write(MARQUEUR_FIN_DOSSIERS);
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

void FenPrincipale::VerifierDossierWoW()
{
    //TODO: Revoir entièrement cette fonction pour ne pas utiliser de deuxième liste...
    //Je ne connais certainement pas assez les itérateurs pour faire un truc en finesse.
    QList<QString> dossiersASupprimer;
    QMap<QString, QString>::iterator i = m_listeDossiersWoW.begin();
    while (i != m_listeDossiersWoW.end())
    {
        QString dossier = i.value();
        QString nomDossier = i.key();

        //Vérification de la validité du dossier.
        while (!QFile::exists(dossier + WOW_EXE_POS) && !dossier.isEmpty())
        {
            QMessageBox::warning(this, tr("EasyRealm"),
                                 tr("Le dossier World of Warcraft n'existe pas/plus dans l'emplacement enregistré ou le dossier n'est pas un dossier World of Warcraft.\n"
                                    "Veuillez sélectionner le dossier World of Warcraft."));

            dossier = QFileDialog::getExistingDirectory(this, tr("Choisissez le dossier d'installation de World of Warcraft"), dossier);

            m_listeDossiersWoW.remove(nomDossier);
            if (dossier.isEmpty())
            {
                QMessageBox::warning(this, tr("EasyRealm"), tr("L'installation ") + nomDossier + tr(" a été supprimée."));
                dossiersASupprimer.append(nomDossier);
            }
            m_listeDossiersWoW.insert(nomDossier, dossier);
        }
        i++;
    }

    //On supprime tous les dossiers marqués.
    foreach(QString nomDossier, dossiersASupprimer)
    {
        m_listeDossiersWoW.remove(nomDossier);
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
    if (!realmlist.getDossierExiste())
        ui->ui_btnLancerWoW->setEnabled(false);
    else
        ui->ui_btnLancerWoW->setEnabled(true);
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

void FenPrincipale::on_ui_btnLancerWoW_released()
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

    //On récupère le dossier
    Realmlist realmlist = m_listeRealmlist.value(ui->ui_listeRealmlist->currentItem()->text());
    QString dossierWoW = m_listeDossiersWoW.value(realmlist.getNomDossier());

    //Vérification du type d'installation.
    QFile realmlistFichier;
    if (QFile::exists(dossierWoW + REALMLIST_POS_WOTLK))
        realmlistFichier.setFileName(dossierWoW + REALMLIST_POS_WOTLK);
    else if (QFile::exists(dossierWoW + REALMLIST_POS_BC))
        realmlistFichier.setFileName(dossierWoW + REALMLIST_POS_BC);
    else
    {
        QMessageBox::warning(this, tr("EasyRealm"), tr("EasyRealm ne trouve pas de fichier realmlist.wtf avec le dossier d'installation spécifié."));
        return;
    }

    //Ecriture du realmlist.
    realmlistFichier.open(QIODevice::Truncate | QIODevice::WriteOnly);
    realmlistFichier.write(realmlist.getRealmlistData().toAscii());

    //Suppression du cache
    if (m_viderCache)
    {
        QDir cacheDir = dossierWoW + CACHE_POS;
        foreach(QString fichier, cacheDir.entryList())
        {
            QFile::remove(dossierWoW + CACHE_POS + fichier);
        }
    }

    QString program = "\"" + dossierWoW + WOW_EXE_POS "\"";

    QProcess Wow;
    Wow.startDetached(program);
}

void FenPrincipale::on_ui_btnOptions_released()
{
    FenOptions fen(this);
    fen.exec();
}
