//Nils
#ifndef COMMANDE_H
#define COMMANDE_H

#include <QDialog>
#include "model.h"
#include "commandemodel.h"
#include "plat.h"
#include <QGroupBox>
#include <QLayout>
#include "template.h"

/*Cette classe correspond a la vue permettant d'afficher le recapitulatif de la commande*/
class Commande : public QWidget
{
    Q_OBJECT
private:

    /*Widget parent*/
    Template *parent;

    /*Objet contenant les donnees necessaires a l'application*/
    Model * m;

    /*Prix total de la commande*/
    QLabel * total;

    /*Vide en dehors du cas connecte. Contient les labels affichant les sout-totaux par membre*/
    std::vector<QLabel*> sousTotaux= std::vector<QLabel*> ();

    /*Widget et layout centraux*/
    QWidget * mainWidget = nullptr;
    QVBoxLayout * centralLayout =  new QVBoxLayout();

    /*Bouton servant a confimer la commande*/
    QPushButton * sendButton;

    /*Contruit la colonne recapitulative des commandes d'un membre dans le cas connecte*/
    QGroupBox * newColonne(Membre * membre); //ne sert que dans le cas connecté

public:
    explicit Commande(Template *parent = nullptr, Model * model = nullptr);



signals:

public slots:

    /*Reaffiche le total quand cela est necessaire*/
    void displayTotal();

    /*Reaffiche les commandeItem quand cela est necessaire (en particulier, lorsqu'un item est retire) */
    void refresh();

    /*En principe, envoie un message en cuisine pour valider la commande et affiche un feedback. En
    realite, affiche seulement en feedback.*/
    void envoieCommande();
};

#endif // COMMANDE_H
