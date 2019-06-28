#include "detail.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <iostream>
#include <QLineEdit>
#include <QLabel>
#include <QFrame>
#include <QGroupBox>
#include "membre.h"
#include "famille.h"
#include "quantityspinbox.h"

Detail::Detail(Template *parent, Model *m, Plat * plat) : QWidget(parent)
{

    model = m;
    std::vector<QString> ingredientList;
    ingredientList.push_back(QString("Carotte"));
    ingredientList.push_back(QString("Soja"));
    ingredientList.push_back(QString("Feuille de riz"));
    ingredientList.push_back(QString("poulet"));
    QString itemName = QString("%1 - %2 euros").arg(plat->getLabel()).arg(plat->getPrix());
    QString itemImage = plat->getImageFile();
    QString itemDescription = plat->getDescription();


    //mainLayout début
    QVBoxLayout * mainLayout = new QVBoxLayout();

    //topLayout début
    QHBoxLayout * topLayout = new QHBoxLayout();
    QPushButton * quitButton = new QPushButton();
    quitButton->setIcon(QIcon(":/images/cross.png"));
    QLabel * name = new QLabel(itemName);
    name->setFont(QFont("Arial", 28));
    topLayout->addWidget(name);
    topLayout->addStretch(5);
    topLayout->addWidget(quitButton);
    //topLayout fin

    //middleLayout début
    QHBoxLayout * middleLayout = new QHBoxLayout();

    //leftLayout début
    QVBoxLayout * leftLayout =new  QVBoxLayout();

    //middleLeftLayout début
    QHBoxLayout * middleLeftLayout = new QHBoxLayout();
    QPixmap pix(itemImage);
    QLabel * image = new QLabel(this);
    image->setPixmap(pix.scaled(QSize(350, 350), Qt::IgnoreAspectRatio,
                                Qt::SmoothTransformation));
    image->setScaledContents(true);
    image->setMinimumSize(QSize(400,400));

    QGroupBox * ingredientBox = new QGroupBox(tr("Ingredients"));
    QGridLayout * ingredientGrid = new QGridLayout(ingredientBox);
    std::vector<QPushButton *> buttonList = std::vector<QPushButton *>();

    for (unsigned int i = 0; i < ingredientList.size(); i++) {
        QPushButton * button = new QPushButton(ingredientList[i]);
        buttonList.push_back(button);
        button ->setIcon(QIcon(":/images/cross.png"));
        ingredientGrid->addWidget(button, i/2, i%2);
        button->setCheckable(true);
        button->setStyleSheet(QString(" QPushButton:checked{background-color: grey;} QPushButton {background-color: orange;}"));
    }

    QGroupBox * descriptionBox = new QGroupBox(tr("Description"));
    QVBoxLayout * descriptionLayout = new QVBoxLayout(descriptionBox);
    descriptionLayout->addWidget(new QLabel(itemDescription));

    QVBoxLayout * infosLayout = new  QVBoxLayout();

    infosLayout->addWidget(ingredientBox);
    infosLayout->addWidget(descriptionBox);

    middleLeftLayout->addWidget(image);
    middleLeftLayout->addLayout(infosLayout);
    //middleLeftLayout fin

    infos = new QLineEdit(tr("infos"));
    leftLayout->addLayout(middleLeftLayout);
    leftLayout->addWidget(infos);
    //leftLayout fin


    QFrame * rightFrame = new QFrame();
    QVBoxLayout * rightLayout =new  QVBoxLayout(rightFrame);
    QGroupBox * quantityBox = new QGroupBox(tr("Quantite"));
    QVBoxLayout * quantityLayout = new QVBoxLayout();



    std::vector<QuantitySpinBox*> spinBoxList = std::vector<QuantitySpinBox*>();

    if (model->getConnected()) {
        Famille * famille = model->getClients().at(model->getIndiceFamilleCourante());
        std::vector<Membre*>* membres = famille->getMembres();
        for (unsigned int i = 0; i < membres->size(); i++) {
            spinBoxList.push_back(new QuantitySpinBox(model, membres->at(i), plat, infos));
        }
    }
    else {
        spinBoxList.push_back(new QuantitySpinBox(model, nullptr, plat, infos));
    }

    for (unsigned int i = 0 ; i < spinBoxList.size(); i++) {
        quantityLayout->addWidget(spinBoxList[i]);
    }

    quantityBox->setLayout(quantityLayout);

    QPushButton * validateButton = new QPushButton("Ajouter \n a la commande");
    validateButton->setFont(model->getButtonFont());
    validateButton->setStyleSheet("QPushButton {background-color: orange;}");

    rightLayout->addWidget(quantityBox);
    rightLayout->addStretch(5);
    rightLayout->addWidget(validateButton);

    middleLayout->addLayout(leftLayout);
    middleLayout->addWidget(rightFrame);
    //middleLayout fin

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout);
    setLayout(mainLayout);
    //mainLayout fin

    connect(quitButton, SIGNAL(clicked()), parent, SLOT(retourCommande()));
    for (unsigned int i = 0; i < spinBoxList.size(); i++) {
        connect(validateButton, SIGNAL(clicked()), spinBoxList[i], SLOT(validateQuantity()));
    }
    connect(validateButton, SIGNAL(clicked()), parent, SLOT(retourCommande()));


}
