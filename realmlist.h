#ifndef REALMLIST_H
#define REALMLIST_H

#include <QString>
#include <QFile>

class Realmlist
{
public:
    Realmlist();
    Realmlist(QFile&);

    Realmlist chargerRealmlistDepuisFichier(QFile &fichier);
    void ecrireRealmlistDansFichier(QFile&);
    QString getRealmlistData();
    QString getTitre() { return m_titre; }
    QString getRealmlist() { return m_realmlist; }
    QString getPatchlist() { return m_patchlist; }
    QString getNomDossier() { return m_nomDossier; }
    bool getDossierExiste() { return m_dossierExiste; }
    void setTitre(QString titre) { m_titre = titre; }
    void setRealmlist(QString realmlist) { m_realmlist = realmlist; }
    void setPatchlist(QString patchlist) { m_patchlist = patchlist; }
    void setNomDossier(QString nomDossier) { m_nomDossier = nomDossier; }
    void setDossierExiste(bool dossierExiste) { m_dossierExiste = dossierExiste; }

private:
    QString m_titre;
    QString m_realmlist;
    QString m_patchlist;
    QString m_nomDossier;
    bool m_dossierExiste;
};

#endif // REALMLIST_H
