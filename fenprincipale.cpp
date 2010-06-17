#include "fenprincipale.h"
#include "ui_fenprincipale.h"

FenPrincipale::FenPrincipale(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FenPrincipale)
{
    ui->setupUi(this);
}

FenPrincipale::~FenPrincipale()
{
    delete ui;
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
