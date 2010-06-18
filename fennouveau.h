#ifndef FENNOUVEAU_H
#define FENNOUVEAU_H

#include <QDialog>
#include "realmlist.h"

namespace Ui
{
    class FenNouveau;
}

class FenNouveau : public QDialog
{
    Q_OBJECT
public:
    FenNouveau(QWidget *parent = 0, Realmlist *realmlist = NULL, bool *ok = NULL);
    ~FenNouveau();

    void rafraichirUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenNouveau *ui;
    Realmlist* m_realmlist;
    bool *m_ok;

private slots:
    void on_ui_btnAjouter_released();
    void on_ui_patchlist_textChanged(QString );
    void on_ui_realmlist_textChanged(QString );
    void on_ui_titre_textChanged(QString );
    void on_ui_btnAnnuler_released();
};

#endif // FENNOUVEAU_H
