#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QMap>
#include "realmlist.h"
#include "fennouveau.h"

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
    void SauvegarderRealmlists();
    void RechargerRealmlists();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenPrincipale *ui;
    QMap<QString, Realmlist> m_listeRealmlist;
    QFile m_fichierRealmlist;

private slots:
    void on_ui_listeRealmlist_currentTextChanged(QString currentText);
    void on_ui_btnAjouter_released();
    void on_ui_btnSupprimer_released();
    void on_ui_btnQuitter_released();
};

#endif // FENPRINCIPALE_H
