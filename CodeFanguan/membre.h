#ifndef MEMBRE_H
#define MEMBRE_H
#include <QString>
#include <iostream>
#include <string>
#include <vector>
#include "plat.h"
#include "commandemodel.h"

/*Contient toutes les donnees necessaires pour representer un habitues*/
class Membre
{
private:
    QString name;
    int id;

    /*Listes des articles commandes*/
    std::vector<CommandeModel*> listeCommandes = std::vector<CommandeModel*>();

    /*Listes des articles favoris*/
    std::vector<Plat*> * favoris;
    /*Listes des articles recommandes*/
    std::vector<Plat*> * recommendations;
    /*Listes des avantages*/
    std::vector<QString> * avantages;

    /*Point de fidelite du meme*/
    int progress;

    /*total du prix des plats commandes par ce membre*/
    float sousTotal = 0;

public:
    Membre();
    QString getName();
    int getId();
    Membre(QString name, int id);
    void addCommande(CommandeModel * com);
    std::vector<CommandeModel*>  getCommande() {return listeCommandes;}
    std::vector<Plat*> * getFavoris();
    void addFavori(Plat * plat);
    std::vector<Plat*> * getRecommendations();
    void addRecommendation(Plat * plat);
    std::vector<QString> * getAvantages();
    void addAvantage(QString avantage);
    int getProgress();
    void setProgress(int value);
    float getSousTotal();
    void clearCommande() {listeCommandes.clear();}
};

#endif // MEMBRE_H
