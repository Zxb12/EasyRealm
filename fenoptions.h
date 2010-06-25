#ifndef FENOPTIONS_H
#define FENOPTIONS_H

#include <QDialog>
#include <QInputDialog>
#include <QMap>

#include "fenprincipale.h"

namespace Ui
{
    class FenOptions;
}

class FenOptions : public QDialog
{
    Q_OBJECT
public:
    FenOptions(QWidget *parent = 0);
    ~FenOptions();

    void rafraichirUI();
    bool estUnDoublon(QString check) { return m_listeDossiersWoW.contains(check); }

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenOptions *ui;
    QWidget* m_parent;
    QMap<QString, QString> m_listeDossiersWoW;

private slots:
    void on_ui_btnEditer_released();
    void on_ui_btnSupprimer_released();
    void on_ui_btnAjouter_released();
    void on_ui_btnAnnuler_released();
    void on_ui_btnEnregistrer_released();
};

#endif // FENOPTIONS_H
