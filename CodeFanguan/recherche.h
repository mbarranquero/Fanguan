#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QGroupBox>
#include <QPushButton>
#include <QSlider>
#include <QGridLayout>
#include <QIcon>
#include "catalogue.h"
#include "model.h"
#include "template.h"

/*Cette classe correspond a la vue de la rubrique recherche de notre carte. A gauche, sont affiches
des boutons qui permettent de filtrer la recherche, et au centre un objet de la classe Catalogue*/
class Recherche : public QWidget
{
    Q_OBJECT
public:
    explicit Recherche(Template *parent = nullptr, Model * m = nullptr);

signals:

public slots:

private:
    QWidget * centralWidget =nullptr;
    QLayout * centralLayout = nullptr;
    Model * model = nullptr;
};

#endif // RECHERCHE_H
