#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QProcess>
#include <QWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QMap>

#include "realmlist.h"
#include "fennouveau.h"
#include "fenediter.h"
#include "fenoptions.h"

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

    void chargerRealmlists();
    void sauvegarderRealmlists();
    void rechargerRealmlists();
    bool estUnDoublon(QString check) { return m_listeRealmlist.contains(check); }
    void verifierDossierWoW();

    void setViderCache(bool viderCache) { m_viderCache = viderCache; }
    bool getViderCache() { return m_viderCache; }
    void setEteindreER(bool eteindreER) { m_eteindreER = eteindreER; }
    bool getEteindreER() { return m_eteindreER; }
    void setListeDossiersWoW(QMap<QString, QString> liste) { m_listeDossiersWoW = liste; }
    QMap<QString, QString> getListeDossiersWoW() { return m_listeDossiersWoW; }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenPrincipale *ui;
    QMap<QString, Realmlist> m_listeRealmlist;
    QMap<QString, QString> m_listeDossiersWoW;
    QFile m_fichierRealmlist;
    bool m_viderCache;
    bool m_eteindreER;

private slots:
    void on_ui_listeRealmlist_currentTextChanged(QString currentText);
    void on_ui_btnAjouter_released();
    void on_ui_btnEditer_released();
    void on_ui_btnSupprimer_released();
    void on_ui_btnQuitter_released();
    void on_ui_btnLancerWoW_released();
    void on_ui_btnOptions_released();
};

#endif // FENPRINCIPALE_H
