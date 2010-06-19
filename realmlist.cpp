#include "realmlist.h"

#define SET_REALMLIST   "set realmlist "
#define SET_PATCHLIST   "set patchlist "
#define ENDL            "\r\n"

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
    data += ENDL;
    //Si aucun patchlist n'est défini, ne pas inscrire SET_PATCHLIST
    if (!m_patchlist.isEmpty())
    {
        data += SET_PATCHLIST;
        data += m_patchlist;
        data += ENDL;
    }
    return data;
}

Realmlist Realmlist::chargerRealmlistDepuisFichier(QFile &fichier)
{
    if (!fichier.atEnd() && fichier.isReadable())
    {
        //Ne pas oublier de supprimer les retours à la ligne ! (ENDL)
        m_titre = ((QString) fichier.readLine()).remove(ENDL);
        m_realmlist = ((QString) fichier.readLine()).remove(ENDL);
        m_patchlist = ((QString) fichier.readLine()).remove(ENDL);
    }
    return *this;
}

void Realmlist::ecrireRealmlistDansFichier(QFile &fichier)
{
    if (fichier.isWritable())
    {
        fichier.write((m_titre + ENDL).toAscii());
        fichier.write((m_realmlist + ENDL).toAscii());
        fichier.write((m_patchlist + ENDL).toAscii());
    }
}
