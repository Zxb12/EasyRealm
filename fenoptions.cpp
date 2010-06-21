#include "fenoptions.h"
#include "ui_fenoptions.h"

FenOptions::FenOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenOptions),
    m_parent(parent)
{
    ui->setupUi(this);
    if (parent)
        ui->ui_viderCache->setChecked(((FenPrincipale*) parent)->getViderCache());
}

FenOptions::~FenOptions()
{
    delete ui;
}

void FenOptions::changeEvent(QEvent *e)
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

void FenOptions::on_ui_btnAnnuler_released()
{
    this->close();
}

void FenOptions::on_ui_btnAjouter_released()
{

}

void FenOptions::on_ui_btnEnregistrer_released()
{
    FenPrincipale* parent = (FenPrincipale*) m_parent;
    parent->setViderCache(ui->ui_viderCache->isChecked());

    this->close();
}
