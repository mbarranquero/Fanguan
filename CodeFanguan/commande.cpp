
#include "commande.h"
#include "template.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <iostream>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QMessageBox>
#include "commandeitem.h"

Commande::Commande(Template *p, Model * model) : QWidget(p)
{
    m = model;
    parent = p;
    //Interface
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QFont font = QFont("Arial", 22);

    //top
    QHBoxLayout * topLayout = new QHBoxLayout();
    QLabel * title = new QLabel(tr("Commande"));
    title->setFont(font);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    QPushButton * backButton = new QPushButton();
    backButton->setIcon(QIcon(":/images/back.png"));
    backButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    topLayout->addWidget(title);
    topLayout->addWidget(backButton);
    mainLayout->addLayout(topLayout);
    mainLayout->addStretch(1);

    mainWidget = new QWidget(this);
    //Cas connecté
    if(m->getConnected()){

        //Récupération des commandes des clients
        std::vector<Famille*> clients = m->getClients();
        int currentFamilyInd = m->getIndiceFamilleCourante();
        Famille * familleCourante = clients[currentFamilyInd];
        std::vector<Membre*> * membresCourants = familleCourante->getMembres();
        unsigned int nbOfCommands = membresCourants->size();

        QHBoxLayout * columns = new QHBoxLayout();

        for(unsigned int i = 0; i < nbOfCommands; i++){
            Membre * membreCourant = membresCourants->at(i);
            QWidget * membreCommande = newColonne(membreCourant);
            columns->addWidget(membreCommande);
        }

        mainWidget->setLayout(columns);


    }

    else {
        std::vector<CommandeModel*> commande = m->getCommandes();
        int nbOfCommands = commande.size();
        QGridLayout * grid = new QGridLayout();
        unsigned int j = 0;
        for (int i = 0; i < nbOfCommands; i++) {
            CommandeModel * commandeItem = commande[i];
            if(commandeItem->getNbUnites() > 0){
                grid->addWidget(new CommandeItem(this, commandeItem), j/3, j%3);
                j = j+1 ;
            }
        }
        grid->setHorizontalSpacing(30);
        mainWidget->setLayout(grid);
    }

    centralLayout->addWidget(mainWidget);
    mainLayout->addLayout(centralLayout);
    QHBoxLayout * bottomLayout = new QHBoxLayout();
    sendButton = new QPushButton("Envoyer en cuisine");
    sendButton->setFont(font);
    m->calculateTotal();
    float totalPrice = m->getTotal();
    total = new QLabel(QString("%1 euros").arg(totalPrice));
    total->setFont(font);
    bottomLayout->addWidget(total);
    bottomLayout->addStretch(10);
    bottomLayout->addWidget(sendButton);

    mainLayout->addStretch(1);
    mainLayout->addLayout(bottomLayout);

    connect(backButton, SIGNAL(clicked()), parent, SLOT(retourCommande()));
    connect(sendButton, SIGNAL(clicked()), this, SLOT(envoieCommande()));
}

QGroupBox * Commande::newColonne(Membre * membre){
    QString nom = membre->getName();
    QGroupBox * newColonne = new QGroupBox(nom);
    QVBoxLayout * colonne = new QVBoxLayout();
    colonne->addStretch(5);
    QButtonGroup * group = new QButtonGroup();
    group->setExclusive(true);
    std::vector<CommandeModel*> listePlats = membre->getCommande();
    float sousTotal = membre->getSousTotal();

    for(unsigned int i = 0; i < listePlats.size(); i++){
        CommandeModel * commande = listePlats[i];
        CommandeItem * commandeItem = new CommandeItem(this, commande);
        if(commande->getNbUnites() > 0){
            colonne->addWidget(commandeItem);
            colonne->addStretch(5);
        }
    }
    QLabel * total = new QLabel(QString("%1 euros").arg(sousTotal));
    sousTotaux.push_back(total);
    colonne->addWidget(total);
    colonne->setAlignment(Qt::AlignCenter);
    newColonne->setLayout(colonne);
    return newColonne;
}

void Commande::displayTotal(){

    m->calculateTotal();
    total->setText(QString("%1 euros").arg(m->getTotal()));
    std::vector<Famille*> clients = m->getClients();
    int currentFamilyInd = m->getIndiceFamilleCourante();
    Famille * familleCourante = clients[currentFamilyInd];
    std::vector<Membre*> * membres = familleCourante->getMembres();

    for(unsigned int i = 0; i < sousTotaux.size(); i++){
        float nouveauSousTotal = membres->at(i)->getSousTotal();
        sousTotaux[i]->setText(QString("%1 euros").arg(nouveauSousTotal));
    }
}

void Commande::refresh() {
    sousTotaux.clear();
    mainWidget->hide();
    centralLayout->removeWidget(mainWidget);
    mainWidget = new QWidget();
    //Cas connecté
    if(m->getConnected()){

        //Récupération des commandes des clients
        std::vector<Famille*> clients = m->getClients();
        int currentFamilyInd = m->getIndiceFamilleCourante();
        Famille * familleCourante = clients[currentFamilyInd];
        std::vector<Membre*> * membresCourants = familleCourante->getMembres();
        unsigned int nbOfCommands = membresCourants->size();

        QHBoxLayout * columns = new QHBoxLayout();
        for(unsigned int i = 0; i < nbOfCommands; i++){
            Membre * membreCourant = membresCourants->at(i);
            QWidget * membreCommande = newColonne(membreCourant);
            columns->addWidget(membreCommande);
        }
        mainWidget->setLayout(columns);
    }

    else{
        std::vector<CommandeModel*> commande = m->getCommandes();
        int nbOfCommands = commande.size();
        QGridLayout * grid = new QGridLayout();
        unsigned int j = 0;
        for (int i = 0; i < nbOfCommands; i++) {
            CommandeModel * commandeItem = commande[i];
            if(commandeItem->getNbUnites() > 0){
                grid->addWidget(new CommandeItem(this, commandeItem), j/3, j%3);
                j = j +1;
            }
        }
        grid->setHorizontalSpacing(30);
        mainWidget->setLayout(grid);
    }
    centralLayout->addWidget(mainWidget);


}

void Commande::envoieCommande() {


    m->clear();

    QMessageBox msgBox(this);
    msgBox.setText("Votre commande a ete envoyee en cuisine.");
    msgBox.exec();
    parent->retourCommande();
}
