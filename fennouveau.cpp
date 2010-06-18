#include "fennouveau.h"
#include "ui_fennouveau.h"

FenNouveau::FenNouveau(QWidget *parent,  Realmlist *realmlist, bool *ok) : QDialog(parent), ui(new Ui::FenNouveau), m_realmlist(realmlist), m_ok(ok)
{
    ui->setupUi(this);
}

FenNouveau::~FenNouveau()
{
    delete ui;
}

void FenNouveau::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FenNouveau::rafraichirUI()
{
    if (ui->ui_titre->text().isEmpty() || ui->ui_realmlist->text().isEmpty())
    {
        ui->ui_btnAjouter->setEnabled(false);
        ui->ui_patchlist->setEnabled(false);
    }
    else
    {
        ui->ui_btnAjouter->setEnabled(true);
        ui->ui_patchlist->setEnabled(true);
    }
}

void FenNouveau::on_ui_btnAnnuler_released()
{
    *m_ok = false;
    this->close();
}

void FenNouveau::on_ui_titre_textChanged(QString txt)
{
    rafraichirUI();
}

void FenNouveau::on_ui_realmlist_textChanged(QString txt)
{
    rafraichirUI();
}

void FenNouveau::on_ui_patchlist_textChanged(QString txt)
{
    rafraichirUI();
}

void FenNouveau::on_ui_btnAjouter_released()
{
    m_realmlist->setTitre(ui->ui_titre->text());
    m_realmlist->setRealmlist(ui->ui_realmlist->text());
    m_realmlist->setPatchlist(ui->ui_patchlist->text());
    *m_ok = true;
    this->close();
}
