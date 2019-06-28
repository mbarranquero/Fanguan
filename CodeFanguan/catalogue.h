//Margot
#ifndef CATALOGUE_H
#define CATALOGUE_H

#include <QScrollArea>
#include "catalogueitem.h"
#include "plat.h"
#include "template.h"

/*Scroll area permettant d'afficher une liste de plats*/
class Catalogue : public QScrollArea
{
    Q_OBJECT
public:
    Catalogue(QWidget *parent = nullptr, Template *t = nullptr, std::vector<Plat *> listePlat = std::vector<Plat *>());

public slots:

private:
    Template * temp = nullptr;

};

#endif // CATALOGUE_H
