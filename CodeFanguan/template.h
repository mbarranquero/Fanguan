//Arthur
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QHBoxLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QPushButton>
#include "model.h"

/*Cette classe est le widget qui dans lequel sont affichees les differentes rubriques de la carte en son centre.
Il affiche en haut des boutons permettant de naviguer entre les differentes widgets*/
class Template : public QWidget
{
    Q_OBJECT
public:
    enum Rubriques{CARTE = 0, ESPACEABO, CONNEXION, INSCRIPTION, RECHERCHE, SELECTION, GERERCOMPTE};
    explicit Template(QWidget *parent = nullptr, Model *m =nullptr, Rubriques rub = CARTE);
    QWidget * getCentralWidget();
    void setCentralWidget(QWidget * w) {
        centralWidget =  w;
        centralWidget->setObjectName("tito");
        centralWidget->setStyleSheet("QWidget#tito{border-image: url(:/images/fondFanguan.png) 0 0 0 0 stretch stretch;} ");
    }
    void setPreviousWidget(QWidget * w){
        previousWidget = w;
    }
    void paintEvent(QPaintEvent *);

signals:

public slots:
    void displayCarte();
    void displayEspaceAbo(int i=0);
    void displayInscription();
    void displayRecherche();
    void displaySelection();
    void displayCommande();
    void displayGererCompte();
    void displayDetail(Plat* p);

    /*Slot simulant l'appel et l'arrivee d'un serveur*/
    void appelServeur();
    void leServeurEstArrive();

    void retourCommande();


private :
    /*Widget precedemment affiche au centre*/
    QWidget * previousWidget = nullptr;

    /*Widget actuellement affiche au centre*/
    QWidget * centralWidget = nullptr;
    QHBoxLayout * centralLayout = new QHBoxLayout() ;
    QVBoxLayout * mainLayout = nullptr;
    Model *model = nullptr;
    QPushButton * serveurButton = nullptr;
};

#endif // TEMPLATE_H
