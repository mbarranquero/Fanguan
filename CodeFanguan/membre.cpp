#include "membre.h"

Membre::Membre()
{

}

Membre::Membre(QString name, int id){
    this->name = name;
    this->id = id;
    this->favoris = new std::vector<Plat*>();
    this->recommendations = new std::vector<Plat*>();
    this->avantages = new std::vector<QString>();
    this->progress = 0;
}


int Membre::getId(){
    return id;
}

QString Membre::getName(){
    return name;
}

void Membre::addFavori(Plat *plat){
    favoris->push_back(plat);
}

std::vector<Plat*> * Membre::getFavoris(){
    return favoris;
}

void Membre::addRecommendation(Plat *plat){
    recommendations->push_back(plat);
}

std::vector<Plat*> * Membre::getRecommendations(){
    return recommendations;
}

void Membre::addAvantage(QString avantage){
    avantages->push_back(avantage);
}

std::vector<QString> * Membre::getAvantages(){
    return avantages;
}

int Membre::getProgress(){
    return progress;
}

void Membre::setProgress(int value){
    progress = value;
}

void Membre::addCommande(CommandeModel * com) {
    listeCommandes.push_back(com);
}

float Membre::getSousTotal(){
    sousTotal = 0;
    for(unsigned int i = 0; i < listeCommandes.size(); i++){
        CommandeModel * cm = listeCommandes[i];
        int quantity = cm->getNbUnites();
        sousTotal += cm->getItemPrice()*quantity;
    }

    return sousTotal;
}
