#ifndef FENOPTIONS_H
#define FENOPTIONS_H

#include <QDialog>

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

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenOptions *ui;
    QWidget* m_parent;
private slots:
    void on_ui_btnAjouter_released();
    void on_ui_btnAnnuler_released();
    void on_ui_btnEnregistrer_released();
};

#endif // FENOPTIONS_H
