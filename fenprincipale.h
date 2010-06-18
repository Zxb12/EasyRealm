#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QWidget>
#include <QFile>
#include <QMap>
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
//    QMap<QString, Realmlist> m_listeRealmlist;
    QMap<QString, Realmlist> m_listeRealmlist;
    QFile m_fichierRealmlist;

private slots:
    void on_ui_listeRealmlist_currentTextChanged(QString currentText);
    void on_ui_btnQuitter_released();
};

#endif // FENPRINCIPALE_H
