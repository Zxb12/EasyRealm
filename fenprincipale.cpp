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

    m_fichierRealmlist.seek(0);
    while (!m_fichierRealmlist.atEnd())
    {
        Realmlist realmlist(m_fichierRealmlist);
        m_listeRealmlist.append(realmlist);
        ui->ui_listeRealmlist->addItem(m_listeRealmlist.last().getTitre());
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
    this->close();
}

void FenPrincipale::on_ui_listeRealmlist_currentRowChanged(int currentRow)
{
    ui->ui_contenuRealmlist->setText(m_listeRealmlist[currentRow].getRealmlistData());
}
