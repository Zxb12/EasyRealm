#include "fenediter.h"
#include "ui_fenediter.h"

FenEditer::FenEditer(QWidget *parent,  Realmlist *realmlist, bool *ok) : QDialog(parent), ui(new Ui::FenEditer), m_realmlist(realmlist), m_ok(ok)
{
    ui->setupUi(this);
    ui->ui_titre->setText(realmlist->getTitre());
    ui->ui_realmlist->setText(realmlist->getRealmlist());
    ui->ui_patchlist->setText(realmlist->getPatchlist());
}

FenEditer::~FenEditer()
{
    delete ui;
}

void FenEditer::changeEvent(QEvent *e)
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

void FenEditer::rafraichirUI()
{
    if (ui->ui_titre->text().isEmpty() || ui->ui_realmlist->text().isEmpty())
    {
        ui->ui_btnEditer->setEnabled(false);
        ui->ui_patchlist->setEnabled(false);
    }
    else
    {
        ui->ui_btnEditer->setEnabled(true);
        ui->ui_patchlist->setEnabled(true);
    }
}

void FenEditer::on_ui_btnAnnuler_released()
{
    *m_ok = false;
    this->close();
}

void FenEditer::on_ui_titre_textChanged(QString txt)
{
    rafraichirUI();
}

void FenEditer::on_ui_realmlist_textChanged(QString txt)
{
    rafraichirUI();
}

void FenEditer::on_ui_patchlist_textChanged(QString txt)
{
    rafraichirUI();
}

void FenEditer::on_ui_btnEditer_released()
{
    m_realmlist->setTitre(ui->ui_titre->text());
    m_realmlist->setRealmlist(ui->ui_realmlist->text());
    m_realmlist->setPatchlist(ui->ui_patchlist->text());
    *m_ok = true;
    this->close();
}