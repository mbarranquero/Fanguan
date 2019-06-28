#include "template.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <iostream>
#include "commande.h"
#include "selection.h"
#include "carte.h"
#include "connexion.h"
#include "detail.h"
#include "recherche.h"
#include "inscription.h"
#include "espaceabo.h"
#include <QTimer>


Template::Template(QWidget *parent, Model *m, Rubriques rub) : QWidget(parent)
{
    model = m;
    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    //Barre supérieure
    QHBoxLayout * topMenuLayout = new QHBoxLayout();

    QButtonGroup * topGroup = new QButtonGroup();
    topGroup->setExclusive(true);

    QString style = QString("QPushButton:checked{background-color: yellow;} QPushButton:pressed {background-color: yellow;}");

    QPushButton * aboButton = new QPushButton(tr("Espace Habitue"));
    topGroup->addButton(aboButton);
    aboButton->setCheckable(true);
    aboButton->setStyleSheet(style);
    QPushButton * carteButton = new QPushButton(tr("Carte"));
    topGroup->addButton(carteButton);
    carteButton->setCheckable(true);
    carteButton->setStyleSheet(style);
    QPushButton * rechercheButton = new QPushButton(tr("Recherche"));
    topGroup->addButton(rechercheButton);
    rechercheButton->setCheckable(true);
    rechercheButton->setStyleSheet(style);
    QPushButton * selectionButton = new QPushButton(tr("Selection du Chef"));
    topGroup->addButton(selectionButton);
    selectionButton->setCheckable(true);
    selectionButton->setStyleSheet(style);

    aboButton->setFont(model->getButtonFont());
    carteButton->setFont(model->getButtonFont());
    rechercheButton->setFont(model->getButtonFont());
    selectionButton->setFont(model->getButtonFont());

    topMenuLayout->addWidget(aboButton);
    topMenuLayout->addWidget(carteButton);
    topMenuLayout->addWidget(rechercheButton);
    topMenuLayout->addWidget(selectionButton);

    //Zone centrale
    switch (rub) {
    case CARTE:
        setCentralWidget(new Carte(this, model));
        setPreviousWidget(centralWidget);
        carteButton->setChecked(true);
        break;

    case CONNEXION:
        setCentralWidget(new Connexion(this, model));
        setPreviousWidget(centralWidget);
        aboButton->setChecked(true);
        break;

	case RECHERCHE:
        setCentralWidget(new Recherche(this, model));
        setPreviousWidget(centralWidget);
        rechercheButton->setChecked(true);
        break;

    case SELECTION:
        setCentralWidget(new Selection(this, model, model->getCarteEntiere()));
        setPreviousWidget(centralWidget);
        selectionButton->setChecked(true);
        break;

    default:
        centralWidget = new QWidget();
        break;
    }
    centralWidget->setMinimumSize(QSize(600, 400));
    centralLayout->addWidget(centralWidget);

    //Barre inférieure
    QHBoxLayout * bottomMenuLayout = new QHBoxLayout();

    serveurButton = new QPushButton(tr("Appeler Serveur"));
    QPushButton * commandeButton = new QPushButton(tr("Voir Recapitulaif"));

    serveurButton->setFont(model->getButtonFont());
    commandeButton->setFont(model->getButtonFont());

    bottomMenuLayout->addWidget(serveurButton);
    bottomMenuLayout->addWidget(commandeButton);

    //Layout général
    mainLayout->addLayout(topMenuLayout);
    mainLayout->addLayout(centralLayout);
    mainLayout->addLayout(bottomMenuLayout);

    //Connection des boutons aux slots
    connect(aboButton, SIGNAL(clicked()), this, SLOT(displayEspaceAbo()));
    connect(rechercheButton, SIGNAL(clicked()), this, SLOT(displayRecherche()));
    connect(carteButton, SIGNAL(clicked()), this, SLOT(displayCarte()));
    connect(commandeButton, SIGNAL(clicked()), this, SLOT(displayCommande()));
    connect(serveurButton, SIGNAL(clicked()), this, SLOT(appelServeur()));
    connect(selectionButton, SIGNAL(clicked()), this, SLOT(displaySelection()));
}

void Template::displayCarte() {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(new Carte(this,model));
    setPreviousWidget(centralWidget);
    centralLayout->addWidget(centralWidget);
    update();
}

void Template::displayRecherche() {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(new Recherche(this,model));
    setPreviousWidget(centralWidget);
    centralLayout->addWidget(centralWidget);
    update();
}

void Template::displayEspaceAbo(int i) {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    if(model->getConnected()){
        setCentralWidget(new EspaceAbo(this,model,i));
        setPreviousWidget(centralWidget);
    }
    else{
        setCentralWidget(new Connexion(this,model));
        setPreviousWidget(centralWidget);
    }
    centralLayout->addWidget(centralWidget);
    update();
}

void Template::displayInscription(){
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(new Inscription(this,model));
    setPreviousWidget(centralWidget);
    centralLayout->addWidget(centralWidget);
    update();
}


void Template::displayCommande() {
   centralLayout->removeWidget(centralWidget);
   centralWidget->hide();
   setCentralWidget(new Commande(this, model));
   centralLayout->addWidget(centralWidget);
}

void Template::displaySelection() {
   centralLayout->removeWidget(centralWidget);
   centralWidget->hide();
   setCentralWidget(new Selection(this,model,model->getCarteEntiere()));
   setPreviousWidget(centralWidget);
   centralLayout->addWidget(centralWidget);
}


void Template::displayDetail(Plat* p) {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(new Detail(this, model, p));
    centralLayout->addWidget(centralWidget);
}

void Template::appelServeur() {
    serveurButton->setText("Un serveur arrive !");
    serveurButton->setDisabled(true);
    QTimer * serveurTimer = new QTimer();
    serveurTimer->setSingleShot(true);
    serveurTimer->start(10000);
    connect(serveurTimer, SIGNAL(timeout()), this, SLOT(leServeurEstArrive()));

}

void Template::leServeurEstArrive() {
    serveurButton->setText("Appeler serveur");
    serveurButton->setDisabled(false);
}


void Template::retourCommande() {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(previousWidget);
    centralLayout->addWidget(centralWidget);
    centralWidget->show();
    update();
}

void Template::displayGererCompte() {
    centralLayout->removeWidget(centralWidget);
    centralWidget->hide();
    setCentralWidget(new GererCompte(this,model));
    setPreviousWidget(centralWidget);
    centralLayout->addWidget(centralWidget);
    update();
}


void Template::paintEvent(QPaintEvent *){
}
