//Arthur
#ifndef DETAIL_H
#define DETAIL_H

#include <QWidget>
#include <QSpinBox>
#include "plat.h"
#include "template.h"
#include <QLineEdit>


/*Correspond a la vue affichant plus de detail pour un article de la carte*/
class Detail : public QWidget
{
    Q_OBJECT
public:
    explicit Detail(Template *parent = nullptr , Model *m = nullptr, Plat * plat = nullptr);

signals:

public slots:

private :
    /*Objet contenant les donnees necessaires a l'application*/
   Model * model =  nullptr;
   /*Line edit permettant aux utilisateurs de remplir des requetes particulieres*/
   QLineEdit * infos = nullptr;
};

#endif // DETAIL_H
