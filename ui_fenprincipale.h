/********************************************************************************
** Form generated from reading UI file 'fenprincipale.ui'
**
** Created: Thu 17. Jun 23:40:54 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENPRINCIPALE_H
#define UI_FENPRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FenPrincipale
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QListWidget *ui_listeRealmlist;
    QTextEdit *ui_contenuRealmlist;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QPushButton *ui_btnLancerWoW;
    QPushButton *ui_btnAjouter;
    QPushButton *ui_btnSupprimer;
    QSpacerItem *horizontalSpacer;
    QPushButton *ui_btnQuitter;

    void setupUi(QWidget *FenPrincipale)
    {
        if (FenPrincipale->objectName().isEmpty())
            FenPrincipale->setObjectName(QString::fromUtf8("FenPrincipale"));
        FenPrincipale->resize(439, 181);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FenPrincipale->sizePolicy().hasHeightForWidth());
        FenPrincipale->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(FenPrincipale);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(FenPrincipale);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(FenPrincipale);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        ui_listeRealmlist = new QListWidget(FenPrincipale);
        ui_listeRealmlist->setObjectName(QString::fromUtf8("ui_listeRealmlist"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ui_listeRealmlist->sizePolicy().hasHeightForWidth());
        ui_listeRealmlist->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(ui_listeRealmlist, 1, 0, 1, 1);

        ui_contenuRealmlist = new QTextEdit(FenPrincipale);
        ui_contenuRealmlist->setObjectName(QString::fromUtf8("ui_contenuRealmlist"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(3);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ui_contenuRealmlist->sizePolicy().hasHeightForWidth());
        ui_contenuRealmlist->setSizePolicy(sizePolicy3);
        ui_contenuRealmlist->setReadOnly(true);
        ui_contenuRealmlist->setOverwriteMode(false);

        gridLayout->addWidget(ui_contenuRealmlist, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        line = new QFrame(FenPrincipale);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ui_btnLancerWoW = new QPushButton(FenPrincipale);
        ui_btnLancerWoW->setObjectName(QString::fromUtf8("ui_btnLancerWoW"));

        horizontalLayout->addWidget(ui_btnLancerWoW);

        ui_btnAjouter = new QPushButton(FenPrincipale);
        ui_btnAjouter->setObjectName(QString::fromUtf8("ui_btnAjouter"));

        horizontalLayout->addWidget(ui_btnAjouter);

        ui_btnSupprimer = new QPushButton(FenPrincipale);
        ui_btnSupprimer->setObjectName(QString::fromUtf8("ui_btnSupprimer"));

        horizontalLayout->addWidget(ui_btnSupprimer);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ui_btnQuitter = new QPushButton(FenPrincipale);
        ui_btnQuitter->setObjectName(QString::fromUtf8("ui_btnQuitter"));

        horizontalLayout->addWidget(ui_btnQuitter);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(FenPrincipale);

        QMetaObject::connectSlotsByName(FenPrincipale);
    } // setupUi

    void retranslateUi(QWidget *FenPrincipale)
    {
        FenPrincipale->setWindowTitle(QApplication::translate("FenPrincipale", "EasyRealm - Beta", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FenPrincipale", "Realmlists disponibles", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FenPrincipale", "Aper\303\247u du realmlist", 0, QApplication::UnicodeUTF8));
        ui_contenuRealmlist->setHtml(QApplication::translate("FenPrincipale", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        ui_btnLancerWoW->setText(QApplication::translate("FenPrincipale", "Lancer World of Warcraft", 0, QApplication::UnicodeUTF8));
        ui_btnAjouter->setText(QApplication::translate("FenPrincipale", "Ajouter", 0, QApplication::UnicodeUTF8));
        ui_btnSupprimer->setText(QApplication::translate("FenPrincipale", "Supprimer", 0, QApplication::UnicodeUTF8));
        ui_btnQuitter->setText(QApplication::translate("FenPrincipale", "Quitter", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FenPrincipale: public Ui_FenPrincipale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENPRINCIPALE_H
