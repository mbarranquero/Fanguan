#include "menu.h"
#include <QGroupBox>

Menu::Menu(QWidget *parent, Template * t, Model * model) : QWidget(parent)
{
    temp = t;
    this->model = model;
    menuList = model->getMenus();
    //std::cout << "j'ai récupere les menus" << std::endl;
    unsigned int sizeMenu = menuList.size();
    std::cout << sizeMenu << std::endl;

    currentMenu = menuList[0];
    currentIndex = 0;

    QVBoxLayout * mainLayout = new QVBoxLayout(this);

    //Partie en-tête du menu
    QHBoxLayout * menu = new QHBoxLayout();
    menu->setAlignment(Qt::AlignCenter);

    QToolButton * flecheG = new QToolButton();
    flecheG->setIcon(QIcon(":/images/left.png"));

    QToolButton * flecheD = new QToolButton();
    flecheD->setIcon(QIcon(":/images/right.png"));

    menuLabel = new QLabel(QString("%1 \n %2 euros").arg(currentMenu->getName()).arg(currentMenu->getPrix()));
    menuLabel->setFont(QFont("Arial", 22));

    menu->addWidget(flecheG);
    menu->addWidget(menuLabel);
    menu->addWidget(flecheD);

    mainLayout->addLayout(menu);

    //Partie contenu du menu
    columns = new QHBoxLayout();
    entreesColumn = newColonne(currentMenu->getMenuEntrees(), "Entrees");
    platsColumn = newColonne(currentMenu->getMenuPlats(), "Plats");
    dessertsColumn = newColonne(currentMenu->getMenuDesserts(), "Desserts");

    columns->addWidget(entreesColumn);
    columns->addWidget(platsColumn);
    columns->addWidget(dessertsColumn);

    mainLayout->addLayout(columns);

    QHBoxLayout * choiceLayout = new QHBoxLayout();
    QPushButton * choiceButton = new QPushButton(tr("Valider votre menu"));
    choiceLayout->setAlignment(Qt::AlignCenter);
    choiceButton->setFont(model->getButtonFont());
    choiceButton->setStyleSheet("background-color: #FFECB3");
    choiceLayout->addWidget(choiceButton);

    mainLayout->addLayout(choiceLayout);

    connect(flecheD, SIGNAL(clicked()), this, SLOT(nextMenu()));
    connect(flecheG, SIGNAL(clicked()), this, SLOT(previousMenu()));
    connect(choiceButton,SIGNAL(clicked()), this, SLOT(validateMenu()));
}

QGroupBox * Menu::newColonne(std::vector<Plat *> liste, QString nom){
    QGroupBox * newColonne = new QGroupBox(nom);
    QVBoxLayout * colonne = new QVBoxLayout();
    colonne->addStretch(5);
    QButtonGroup * group = new QButtonGroup();
    group->setExclusive(true);

    for(unsigned int i = 0; i < liste.size(); i++){
        Plat * plat = liste[i];
        CatalogueItem * item = new CatalogueItem(temp, plat, true);
        item->setCheckable(true);
        item->setStyleSheet(QString(" QToolButton:checked{background-color: orange;} QToolButton:pressed {background-color: orange;}"));
        group->addButton(item);
        colonne->addWidget(item);
        colonne->addStretch(5);
    }
    colonne->setAlignment(Qt::AlignCenter);
    newColonne->setLayout(colonne);
    return newColonne;
}

void Menu::nextMenu(){
    int nbOfMenus = menuList.size();
    currentIndex = (currentIndex + 1) % nbOfMenus;
    currentMenu = menuList[currentIndex];
    menuLabel->setText(QString("%1 \n %2 euros").arg(currentMenu->getName()).arg(currentMenu->getPrix()));

    columns->removeWidget(entreesColumn);
    entreesColumn->hide();
    entreesColumn = newColonne(currentMenu->getMenuEntrees(), "Entrees");
    columns->addWidget(entreesColumn);

    columns->removeWidget(platsColumn);
    platsColumn->hide();
    platsColumn = newColonne(currentMenu->getMenuPlats(), "Plats");
    columns->addWidget(platsColumn);

    columns->removeWidget(dessertsColumn);
    dessertsColumn->hide();
    dessertsColumn = newColonne(currentMenu->getMenuDesserts(), "Desserts");
    columns->addWidget(dessertsColumn);
}

void Menu::previousMenu(){
    int nbOfMenus = menuList.size();
    if(currentIndex == 0){
        currentIndex = nbOfMenus - 1;
    }
    else{
        currentIndex = (currentIndex - 1) % nbOfMenus;
    }
    currentMenu = menuList[currentIndex];
    menuLabel->setText(QString("%1 \n %2 euros").arg(currentMenu->getName()).arg(currentMenu->getPrix()));

    columns->removeWidget(entreesColumn);
    entreesColumn->hide();
    entreesColumn = newColonne(currentMenu->getMenuEntrees(), "Entrees");
    columns->addWidget(entreesColumn);

    columns->removeWidget(platsColumn);
    platsColumn->hide();
    platsColumn = newColonne(currentMenu->getMenuPlats(), "Plats");
    columns->addWidget(platsColumn);

    columns->removeWidget(dessertsColumn);
    dessertsColumn->hide();
    dessertsColumn = newColonne(currentMenu->getMenuDesserts(), "Desserts");
    columns->addWidget(dessertsColumn);
}

void Menu::validateMenu() {
    model->addCommande(new CommandeModel(currentMenu->getName(), currentMenu->getPrix(), 1));
}
