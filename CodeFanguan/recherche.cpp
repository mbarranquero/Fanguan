#include "recherche.h"
#include <QLineEdit>

Recherche::Recherche(Template *parent, Model * m) : QWidget(parent)
{
    model = m;
    QHBoxLayout * mainLayout = new QHBoxLayout();

    //Création de la colonne recherche
    QVBoxLayout * vlayout = new QVBoxLayout();

    //Groupe fourchette de prix
    QGroupBox * priceGroupBox = new QGroupBox(tr("Prix"));
    QSlider * slider = new QSlider(Qt::Horizontal, this);
    QHBoxLayout * priceLayout = new QHBoxLayout();
    priceLayout->addWidget(slider);
    priceGroupBox->setLayout(priceLayout);

    //Groupe choix pays
    QGroupBox * countryGroupBox = new QGroupBox(tr("Pays"));
    QHBoxLayout * countryLayout = new QHBoxLayout();

    QToolButton * chButton = new QToolButton();
    chButton->setIcon(QIcon(":/images/chine.png"));
    countryLayout->addWidget(chButton);

    QToolButton * jpButton = new QToolButton();
    jpButton->setIcon(QIcon(":/images/japon.jpg"));
    countryLayout->addWidget(jpButton);

    QToolButton * thButton = new QToolButton();
    thButton->setIcon(QIcon(":/images/thailande.png"));
    countryLayout->addWidget(thButton);

    countryGroupBox->setLayout(countryLayout);

    //Groupe choix type
    QGroupBox * typeGroupBox = new QGroupBox(tr("Type"));
    QVBoxLayout * typeLayout = new QVBoxLayout();

    QHBoxLayout * dishLayout = new QHBoxLayout();
    QPushButton * starterButton = new QPushButton(tr("Entrees"));
    starterButton->setCheckable(true);
    starterButton->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    QPushButton * mealButton = new QPushButton(tr("Plats"));
    mealButton->setCheckable(true);
    mealButton->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    QPushButton * dessertsButton = new QPushButton(tr("Desserts"));
    dessertsButton ->setCheckable(true);
    dessertsButton->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    dishLayout->addWidget(starterButton);
    dishLayout->addWidget(mealButton);
    dishLayout->addWidget(dessertsButton);

    QHBoxLayout * detailLayout = new QHBoxLayout();
    QPushButton * spicyButton = new QPushButton(tr("Epice"));
    spicyButton->setCheckable(true);
    spicyButton->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    QPushButton * vegButton = new QPushButton(tr("Vegetarien"));
    vegButton->setCheckable(true);
    vegButton->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    detailLayout->addWidget(spicyButton);
    detailLayout->addWidget(vegButton);

    typeLayout->addLayout(dishLayout);
    typeLayout->addLayout(detailLayout);
    typeGroupBox->setLayout(typeLayout);

    //Groupe choix ingrédient
    QGroupBox * ingGroupBox = new QGroupBox(tr("Ingredients"));
    QGridLayout * ingLayout = new QGridLayout();

    QToolButton * carotteButton = new QToolButton();
    carotteButton->setIcon(QIcon(":/images/carotte.png"));
    ingLayout->addWidget(carotteButton);

    QToolButton * tomateButton = new QToolButton();
    tomateButton->setIcon(QIcon(":/images/tomate.png"));
    ingLayout->addWidget(tomateButton);

    QToolButton * oignonButton = new QToolButton();
    oignonButton->setIcon(QIcon(":/images/piment.png"));
    ingLayout->addWidget(oignonButton);

    ingGroupBox->setLayout(ingLayout);
    vlayout->addWidget(new QLineEdit());
    vlayout->addWidget(priceGroupBox);
    vlayout->addWidget(countryGroupBox);
    vlayout->addWidget(typeGroupBox);
    vlayout->addWidget(ingGroupBox);
    QFrame * buttonFrame = new QFrame();
    buttonFrame->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
    buttonFrame->setLayout(vlayout);

    //Zone centrale
    centralLayout = new QHBoxLayout();
    centralWidget = new Catalogue(this, parent,  model->getCarteEntiere());
    centralWidget->setMinimumSize(QSize(300, 300));
    centralLayout->addWidget(centralWidget);
    centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

    mainLayout->addWidget(buttonFrame);
    mainLayout->addLayout(centralLayout);

    setLayout(mainLayout);
}
