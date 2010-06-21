#include <QtGui/QApplication>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>

#include "fenprincipale.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Chargement des traductions.
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("easyrealm_") + locale);
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    FenPrincipale w;
    w.show();
    return a.exec();
}
