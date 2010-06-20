#include "fenediter.h"
#include "ui_fenediter.h"

FenEditer::FenEditer(QWidget *parent,  Realmlist *realmlist, bool *ok, bool editerTitre) : QDialog(parent), ui(new Ui::FenEditer), m_realmlist(realmlist),
m_ok(ok), m_editerTitre(editerTitre)
{
    ui->setupUi(this);

    //Chargement du realmlist dans l'interface
    ui->ui_titre->setText(realmlist->getTitre());
    ui->ui_realmlist->setText(realmlist->getRealmlist());
    ui->ui_patchlist->setText(realmlist->getPatchlist());

    //Changement des verrouillages de la fenêtre si on édite le titre. Pas possible d'annuler.
    if (editerTitre)
    {
        ui->ui_titre->setEnabled(true);
        ui->ui_realmlist->setEnabled(false);
        ui->ui_patchlist->setEnabled(false);
        ui->ui_btnAnnuler->setEnabled(false);
    }

    rafraichirUI();
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
    if (!m_editerTitre)
    {
        //Si les données sont incorrectes, impossible de valider.
        if (ui->ui_titre->text().isEmpty() || ui->ui_realmlist->text().isEmpty())
        {
            ui->ui_btnEditer->setEnabled(false);
        }
        else
        {
            ui->ui_btnEditer->setEnabled(true);
        }
    }
    else
    {
        if (ui->ui_titre->text().isEmpty() || ui->ui_titre->text() == m_realmlist->getTitre())
            ui->ui_btnEditer->setEnabled(false);
        else
            ui->ui_btnEditer->setEnabled(true);
    }
}

void FenEditer::on_ui_btnAnnuler_released()
{
    //Annulation : aucune valeur modifiée, pas ok...
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
    //Mise à jour du contenu du realmlist.
    m_realmlist->setTitre(ui->ui_titre->text());
    m_realmlist->setRealmlist(ui->ui_realmlist->text());
    m_realmlist->setPatchlist(ui->ui_patchlist->text());

    //Nous avons modifié le realmlist, nous sommes ok...
    *m_ok = true;
    this->close();
}
