#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QWidget>
#include <QFile>
#include "realmlist.h"

namespace Ui
{
    class FenPrincipale;
}

class FenPrincipale : public QWidget
{
    Q_OBJECT
public:
    FenPrincipale(QWidget *parent = 0);
    ~FenPrincipale();

    void ChargerRealmlists();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenPrincipale *ui;
    QList<Realmlist> m_listeRealmlist;
    QFile m_fichierRealmlist;

private slots:
    void on_ui_listeRealmlist_currentRowChanged(int currentRow);
    void on_ui_btnQuitter_released();
};

#endif // FENPRINCIPALE_H
