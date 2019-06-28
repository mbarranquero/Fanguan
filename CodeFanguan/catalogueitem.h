#ifndef CATALOGUEITEM_H
#define CATALOGUEITEM_H

#include <QToolButton>
#include "plat.h"
#include "catalogue.h"
#include "template.h"
#include "model.h"

/*Cet classe est celle qui permet d'afficher les articles de la carte sous la forme de bouton rectangulaire
contenant une image de l'article et un label affichant son nom et son prix*/
class CatalogueItem : public QToolButton
{
    Q_OBJECT
public:
    explicit CatalogueItem(Template * parent = nullptr, Plat * plat = nullptr, bool _inMenu = false);
    virtual ~CatalogueItem() {}
    const Plat * getPlat() {return plat;}
    void setInMenu(bool b) {inMenu = b;}

signals:
    /*Ce signal signifie qu'on doit afficher la vue detail associe au plat de ce CatalogueItem*/
    void detailRequis(Plat * p);

public slots:
   /*Ce slot est appele quand on clique sur ce CatalogueItem, il emet le signal detail requis*/
   void sendDetailSignal();

private:
    /*Article qui est affiche*/
    Plat* plat = nullptr;

    /*Objet contenant les donnees necessaires a l'application*/
    Model * model = nullptr;

    /*Vaut true si l'article est affiche dans un menu*/
    bool inMenu = false;
};

#endif // CATALOGUEITEM_H

