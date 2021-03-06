#ifndef FENNOUVEAU_H
#define FENNOUVEAU_H

#include <QDialog>

#include "fenprincipale.h"
#include "realmlist.h"

namespace Ui
{
    class FenNouveau;
}

class FenNouveau : public QDialog
{
    Q_OBJECT
public:
    FenNouveau(QWidget *parent = 0, Realmlist *realmlist = NULL, bool *ok = NULL, bool renommer = false);
    ~FenNouveau();

    void rafraichirUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenNouveau *ui;
    Realmlist* m_realmlist;
    bool *m_ok;
    bool m_renommer;

private slots:
    void on_ui_btnAjouter_released();
    void on_ui_patchlist_textChanged(QString );
    void on_ui_realmlist_textChanged(QString );
    void on_ui_titre_textChanged(QString );
    void on_ui_btnAnnuler_released();
    void on_ui_listeDossiers_currentIndexChanged(int index);
};

#endif // FENNOUVEAU_H
