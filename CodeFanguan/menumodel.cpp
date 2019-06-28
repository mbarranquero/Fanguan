#include "menumodel.h"

MenuModel::MenuModel()
{

}

MenuModel::MenuModel(QString n, float p)
{
    name = n;
    price = p;

}

void MenuModel::addMenuEntree(Plat * plat){
    menuEntrees.push_back(plat);
}

void MenuModel::addMenuPlat(Plat * plat){
    menuPlats.push_back(plat);
}

void MenuModel::addMenuDessert(Plat * plat){
    menuDesserts.push_back(plat);
}

QString MenuModel::getName(){
    return name;
}

std::vector<Plat*> MenuModel::getMenuEntrees(){
    return menuEntrees;
}

std::vector<Plat*> MenuModel::getMenuPlats(){
    return menuPlats;
}

std::vector<Plat*> MenuModel::getMenuDesserts(){
    return menuDesserts;
}
