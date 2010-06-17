#include "realmlist.h"

#define SET_REALMLIST   "set realmlist "
#define SET_PATCHLIST   "set patchlist "

Realmlist::Realmlist() : m_titre(""), m_realmlist(""), m_patchlist("")
{

}

Realmlist::Realmlist(QFile &fichier)
{
    chargerRealmlistDepuisFichier(fichier);
}

QString Realmlist::getRealmlistData()
{
    QString data;
    data += SET_REALMLIST ;
    data += m_realmlist;
    data += '\n';
    if (!m_patchlist.isEmpty())
    {
        data += SET_PATCHLIST;
        data += m_patchlist;
        data += '\n';
    }
    return data;
}

Realmlist Realmlist::chargerRealmlistDepuisFichier(QFile &fichier)
{
    if (!fichier.atEnd() && fichier.isReadable())
    {
        QString data = fichier.readLine();
        data.chop(2);
        m_titre = data;
        data = fichier.readLine();
        data.chop(2);
        m_realmlist = data;
        data = fichier.readLine();
        data.chop(2);
        m_patchlist = data;
    }
    return *this;
}

void Realmlist::ecrireRealmlistDansFichier(QFile &fichier)
{
    if (fichier.isWritable())
    {
        fichier.write((m_titre + '\n').toAscii());
        fichier.write((m_realmlist + '\n').toAscii());
        fichier.write((m_patchlist + '\n').toAscii());
    }
}
