#include "famille.h"

Famille::Famille()
{

}

Famille::Famille(QString name, QString password){
    this->name = name;
    this->password = password;
    membres = new std::vector<Membre*>();
}

QString Famille::getName(){
    return name;
}

QString Famille::getPassword(){
    return password;
}

int Famille::getSize(){
    return membres->size();
}

void Famille::setPassword(QString password){
    this->password = password;
}

std::vector<Membre*> * Famille::getMembres(){
    return membres;
}

void Famille::addMembre(Membre * membre){
    membres->push_back(membre);
}
