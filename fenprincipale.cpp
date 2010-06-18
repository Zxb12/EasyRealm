#include "fenprincipale.h"
#include "ui_fenprincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenPrincipale),
    m_fichierRealmlist("realmlist.dat")
{
    m_fichierRealmlist.open(QIODevice::ReadWrite);
    ui->setupUi(this);
    ChargerRealmlists();
}

FenPrincipale::~FenPrincipale()
{
    m_fichierRealmlist.close();
    delete ui;
}

void FenPrincipale::ChargerRealmlists()
{
    ui->ui_listeRealmlist->clear();
    m_listeRealmlist.clear();

    if (!m_fichierRealmlist.isReadable())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les realmlists depuis le fichier.");
        return;
    }

    m_fichierRealmlist.reset();
    QString sRow = m_fichierRealmlist.readLine();
    sRow.chop(2);
    int row = sRow.toInt();

    while (!m_fichierRealmlist.atEnd())
    {
        Realmlist realmlist(m_fichierRealmlist);
        m_listeRealmlist.insert(realmlist.getTitre(), realmlist);
    }

    ui->ui_listeRealmlist->addItems(m_listeRealmlist.keys());
    ui->ui_listeRealmlist->setCurrentRow(row);
}

void FenPrincipale::SauvegarderRealmlists()
{
    if (!m_fichierRealmlist.isWritable())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de charger les realmlists depuis le fichier.");
        return;
    }

    m_fichierRealmlist.resize(0);

    QString row;
    m_fichierRealmlist.write(QByteArray::number(ui->ui_listeRealmlist->currentRow()));
    m_fichierRealmlist.write("\r\n");

    foreach (Realmlist realmlist, m_listeRealmlist)
        realmlist.ecrireRealmlistDansFichier(m_fichierRealmlist);
}

void FenPrincipale::RechargerRealmlists()
{
    SauvegarderRealmlists();
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
    SauvegarderRealmlists();
    this->close();
}

void FenPrincipale::on_ui_listeRealmlist_currentTextChanged(QString currentText)
{
    Realmlist realmlist = m_listeRealmlist.value(currentText);
    ui->ui_contenuRealmlist->setText(realmlist.getRealmlistData());
}

void FenPrincipale::on_ui_btnAjouter_released()
{
    RechargerRealmlists();
}

void FenPrincipale::on_ui_btnSupprimer_released()
{
    RechargerRealmlists();
}
