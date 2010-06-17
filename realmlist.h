#ifndef REALMLIST_H
#define REALMLIST_H

#include <QString>
#include <QFile>

class Realmlist
{
public:
    Realmlist();
    Realmlist(QFile&);

    QString getRealmlistData();
    QString getTitre() { return m_titre; }
    Realmlist chargerRealmlistDepuisFichier(QFile &fichier);
    void ecrireRealmlistDansFichier(QFile&);

private:
    QString m_titre;
    QString m_realmlist;
    QString m_patchlist;
};

#endif // REALMLIST_H
