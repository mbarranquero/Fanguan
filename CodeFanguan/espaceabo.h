//Julien
#ifndef ESPACEABO_H
#define ESPACEABO_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextListFormat>
#include <QToolButton>
#include <QButtonGroup>
#include <QIcon>
#include <QScrollArea>
#include "catalogueitem.h"
#include "gerercompte.h"
#include "model.h"
#include "template.h"

/*Correspond a la vue de l'espace habitue*/
class EspaceAbo : public QWidget
{
    Q_OBJECT
private:
    Model * model;
    Template * temp;

public:
    explicit EspaceAbo(Template * t = nullptr, Model * m = nullptr, int indiceMembreCourant = 0);

signals:


public slots:
    void disconnect();
};

#endif // ESPACEABO_H
