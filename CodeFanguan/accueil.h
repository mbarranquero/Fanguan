//Arthur
#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QPixmap>
#include <QWidget>
#include "model.h"
#include <QPushButton>

class Accueil : public QWidget
{
    Q_OBJECT
public:
    explicit Accueil(QWidget *parent = nullptr, Model * m = nullptr);
    Model * model= nullptr;

signals:

public slots:

    /*En principe, modifie la langue de l'application. Pour l'instant, modifie la langue du titre de
    l'écran d'accueil*/
    void changeLangueFR();
    void changeLangueEN();
    void changeLangueCH();

    /*En principe, envoie un message d'appel a un serveur et affiche un feedback.
     * Pour l'instant, ne fait que rafraichir la vue lorsque le serveur est appele*/
    void appelServeur();

    /*Rafraichit la vue lorsque le serveur arrive*/
    void leServeurEstArrive();

private :
    /*Widget central*/
    QWidget * mainWidget = new QWidget();

    /*QLabel qui contient l'image du titre de l'écran d'accueil*/
    QLabel * welcomeSentence = new QLabel();
    QPixmap pix = QPixmap(":/images/titreFanguan.png" );

    /*Bouton servant a appeler le serveur*/
    QPushButton * serveurButton = nullptr;
};

#endif // ACCUEIL_H
