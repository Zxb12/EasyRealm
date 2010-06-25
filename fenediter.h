#ifndef FENEDITER_H
#define FENEDITER_H

#include <QDialog>
#include "realmlist.h"
#include "fenprincipale.h"

namespace Ui
{
    class FenEditer;
}

class FenEditer : public QDialog
{
    Q_OBJECT
public:
    FenEditer(QWidget *parent = 0, Realmlist *realmlist = NULL, bool *ok = NULL, bool editerTitre = false);
    ~FenEditer();

    void rafraichirUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenEditer *ui;
    Realmlist* m_realmlist;
    bool *m_ok;
    bool m_editerTitre;

private slots:
    void on_ui_btnEditer_released();
    void on_ui_patchlist_textChanged(QString );
    void on_ui_realmlist_textChanged(QString );
    void on_ui_titre_textChanged(QString );
    void on_ui_btnAnnuler_released();
    void on_ui_listeDossiers_currentIndexChanged(int index);
};

#endif // FENEDITER_H
