//Margot
#ifndef CARTE_H
#define CARTE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "model.h"
#include "template.h"

/*Cette classe correspond a une vue qui affiche les boutons qui permettent de naviguer entre les
differentes categories de la carte ("entree", "plat", "dessert" etc.) a gauche et une zone centrale qui sera remplie
par une vue Catalogue pour les categories "entree", "plat", "dessert" et "boisson" et une Menu pour la categorie menue*/
class Carte : public QWidget
{
    Q_OBJECT
public:
    explicit Carte(Template *parent = nullptr, Model * m = nullptr);
    void setCentralWidget(QWidget * w) {
        centralWidget =  w;
    }
    void paintEvent(QPaintEvent *);

signals:

public slots:
    /*Rafraichit la vue pour afficher la rubrique désirée de la carte*/
    void displayEntrees();
    void displayPlats();
    void displayDesserts();
    void displayMenus();
    void displayBoissons();

private:
    /*Objet contenant les donnees necessaires a l'application*/
    Model * model = nullptr;

    /*Widget et layout centraux*/
    QWidget * centralWidget = nullptr;
    QLayout * centralLayout = nullptr;

    /*Widget parent*/
    Template * temp;
};

#endif // CARTE_H
