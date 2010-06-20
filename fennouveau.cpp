#include "fennouveau.h"
#include "ui_fennouveau.h"

FenNouveau::FenNouveau(QWidget *parent,  Realmlist *realmlist, bool *ok, bool renommer) : QDialog(parent), ui(new Ui::FenNouveau), m_realmlist(realmlist), m_ok(ok),
m_renommer(renommer)
{
    ui->setupUi(this);
    if (renommer)
    {
        ui->ui_titre->setText(realmlist->getTitre());
        ui->ui_realmlist->setText(realmlist->getRealmlist());
        ui->ui_patchlist->setText(realmlist->getPatchlist());
    }

    rafraichirUI();
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
    //Si les données sont incorrectes, impossible de valider.
    //Dans le cas d'un ajout, titre=="" donc la condition sera fausse. Elle ne pourra être vraie que si le realmlist doit etre renommé.
    if (ui->ui_titre->text().isEmpty() || ui->ui_realmlist->text().isEmpty() || ui->ui_titre->text() == m_realmlist->getTitre())
    {
        ui->ui_btnAjouter->setEnabled(false);
    }
    else
    {
        ui->ui_btnAjouter->setEnabled(true);
    }
}

void FenNouveau::on_ui_btnAnnuler_released()
{
    //Annulation : aucune valeur modifiée, pas ok...
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
    //Mise à jour du contenu du realmlist.
    m_realmlist->setTitre(ui->ui_titre->text());
    m_realmlist->setRealmlist(ui->ui_realmlist->text());
    m_realmlist->setPatchlist(ui->ui_patchlist->text());

    //Nous avons modifié le realmlist, nous sommes ok...
    *m_ok = true;
    this->close();
}
