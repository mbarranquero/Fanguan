#include "catalogue.h"
#include "catalogueitem.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolButton>
#include <QLabel>
#include <QIcon>
#include <QPixmap>
#include <QtGui>
#include <iostream>

#include "detail.h"

Catalogue::Catalogue(QWidget *parent, Template * t, std::vector<Plat *> listePlat) : QScrollArea(parent)
{
    temp = t;
    QWidget * centralWidget = new QWidget();
    centralWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    QGridLayout * mainLayout = new QGridLayout(centralWidget);
    for (unsigned int i = 0; i < listePlat.size(); i++) {
        mainLayout->addWidget(new CatalogueItem(temp, listePlat[i] ), i%3, i/3);
    }
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->setSpacing(20);
    setWidget(centralWidget);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

}

