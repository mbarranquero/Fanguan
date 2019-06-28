#ifndef MENUMODEL_H
#define MENUMODEL_H
#include <QString>
#include "plat.h"

class MenuModel
{
public:
    MenuModel();
    MenuModel(QString name, float p);
    void addMenuEntree(Plat * plat);
    void addMenuPlat(Plat * plat);
    void addMenuDessert(Plat * plat);
    QString getName();
    float getPrix() { return price;}
    std::vector<Plat*> getMenuEntrees();
    std::vector<Plat*> getMenuPlats();
    std::vector<Plat*> getMenuDesserts();

private:
    QString name = "default";
    float price =0;
    std::vector<Plat*> menuEntrees;
    std::vector<Plat*> menuPlats;
    std::vector<Plat*> menuDesserts;
};

#endif // MENUMODEL_H
