#include "carte.h"
#include "catalogue.h"
#include "menu.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <iostream>

Carte::Carte(Template * parent, Model * m) : QWidget(parent)
{
    model = m;
    temp = parent;
    QHBoxLayout * mainLayout = new QHBoxLayout();
    QHBoxLayout * topLayout = new QHBoxLayout();
    topLayout->setSpacing(0);
    
    class CarteButton : public QPushButton
    {
    public:
        CarteButton(QString label, Model * m) : QPushButton(label){
            //Model * model = new Model();
            setMinimumSize(QSize(280, 70));
            setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
            setFont(m->getButtonFont());
            setCheckable(true);
            setStyleSheet("QPushButton:checked{background-color: yellow;} QPushButton:pressed {background-color: yellow;}");
        }
        virtual ~CarteButton() {}
    };

    QButtonGroup * group = new QButtonGroup();
    group->setExclusive(true);
    QPushButton * entreesButton = new CarteButton("Entrees", model);
    group->addButton(entreesButton);
    QPushButton * platsButton = new CarteButton("Plats", model);
    group->addButton(platsButton);
    QPushButton * dessertsButton = new CarteButton("Desserts", model);
    group->addButton(dessertsButton);
    QPushButton * menusButton = new CarteButton("Menus", model);
    menusButton->setChecked(true);
    group->addButton(menusButton);
    QPushButton * boissonsButton = new CarteButton("Boissons", model);
    group->addButton(boissonsButton);

    QVBoxLayout * buttonLayout = new QVBoxLayout();
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(menusButton);
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(entreesButton);
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(platsButton);
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(dessertsButton);
    buttonLayout->addStretch(5);

    buttonLayout->addWidget(boissonsButton);
    buttonLayout->addStretch(5);

    //Zone centrale
    centralLayout = new QHBoxLayout();
    centralWidget = new Menu(nullptr, temp, model);
    centralWidget->setMinimumSize(QSize(300, 300));
    centralWidget->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    centralLayout->addWidget(centralWidget);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addLayout(centralLayout);
    setLayout(mainLayout);

    connect(entreesButton, SIGNAL(clicked()), this, SLOT(displayEntrees()));
    connect(platsButton, SIGNAL(clicked()), this, SLOT(displayPlats()));
    connect(dessertsButton, SIGNAL(clicked()), this, SLOT(displayDesserts()));
    connect(menusButton, SIGNAL(clicked()), this, SLOT(displayMenus()));
    connect(boissonsButton, SIGNAL(clicked()), this, SLOT(displayBoissons()));
}

void Carte::displayEntrees() {
    centralWidget->hide();
    centralLayout->removeWidget(centralWidget);
    setCentralWidget(new Catalogue(nullptr, temp, model->getEntrees()));
    centralLayout->addWidget(centralWidget);
    update();
}

void Carte::displayPlats() {
    centralWidget->hide();
    centralLayout->removeWidget(centralWidget);
    setCentralWidget(new Catalogue(nullptr, temp, model->getPlats()));
    centralLayout->addWidget(centralWidget);
    update();
}

void Carte::displayDesserts() {
    centralWidget->hide();
    centralLayout->removeWidget(centralWidget);
    setCentralWidget(new Catalogue(nullptr, temp, model->getDesserts()));
    centralLayout->addWidget(centralWidget);
    update();
}



void Carte::displayMenus() {
    centralWidget->hide();
    centralLayout->removeWidget(centralWidget);
    setCentralWidget(new Menu(nullptr, temp, model));
    centralLayout->addWidget(centralWidget);
    update();
}

void Carte::displayBoissons() {
    centralWidget->hide();
    centralLayout->removeWidget(centralWidget);
    setCentralWidget(new Catalogue(nullptr, temp, model->getBoissons()));
    centralLayout->addWidget(centralWidget);
    update();
}

void Carte::paintEvent(QPaintEvent *){
}
