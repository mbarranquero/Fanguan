
#include "plat.h"

Plat::Plat(int idb)
{
    id = idb;
}

QString Plat::getLabel(){
    return label;
}

QString Plat::getDescription(){
    return description;
}

QString Plat::getImageFile(){
    return imageFile;
}

float Plat::getPrix(){
    return prix;
}

int Plat::getId(){
    return id;
}

std::vector<QString> Plat::getIngredients(){
    return ingredients;
}

void Plat::setLabel(QString labelb){
    label =labelb;
}

void Plat::setDescription(QString descrip){
    description = descrip;
}

void Plat::setImageFile(QString imagePath){
    imageFile = imagePath;
}

void Plat::setPrix(float prixb){
    prix = prixb;
}

void Plat::setId(int idb){
    id = idb;
}

void Plat::setIngredients(std::vector<QString> ingredient){
    ingredients = ingredient;
}
