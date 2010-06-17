#ifndef FENPRINCIPALE_H
#define FENPRINCIPALE_H

#include <QWidget>

namespace Ui {
    class FenPrincipale;
}

class FenPrincipale : public QWidget {
    Q_OBJECT
public:
    FenPrincipale(QWidget *parent = 0);
    ~FenPrincipale();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::FenPrincipale *ui;
};

#endif // FENPRINCIPALE_H
