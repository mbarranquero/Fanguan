#include "gerercompte.h"
#include "template.h"

GererCompte::GererCompte(QWidget *parent, Model * m) : QWidget(parent)
{
    model = m;
    Famille * famille = model->getClients()[m->getIndiceFamilleCourante()];
    std::vector<Membre*>* membres = famille->getMembres();
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setSpacing(20);
    layout->setMargin(100);

    QHBoxLayout * headerVerticalLayout = new QHBoxLayout();
    QLabel * familyLabel = new QLabel(QString("Famille ")+famille->getName());
    QToolButton * backButton = new QToolButton();
    backButton->setIcon(QIcon(":/images/back.png"));
    headerVerticalLayout->addWidget(familyLabel);
    headerVerticalLayout->addWidget(backButton);

    familleProgressBar = new QProgressBar();
    updateFamilyProgressBar();

    progressGridLayout = new QGridLayout();
    progressGridLayout->setAlignment(Qt::AlignCenter);

    plusButton = new QToolButton();
    plusButton->setIcon(QIcon(":images/plus.png"));
    plusButton->setIconSize(QSize(25,25));
    plusButton->setStyleSheet("QToolButton{border-radius: 0px;}");
    progressGridLayout->addWidget(plusButton,5,1);

    for(unsigned int i = 0; i<membres->size();i++){
        addDeleteButton(i,0);
        addLabel(i,1,membres->at(i)->getName());
        addProgressBar(i,2,membres->at(i)->getProgress());
    }

    QLabel * passwordLabel = new QLabel("Mot de passe: ");
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setText(famille->getPassword());

    QHBoxLayout * passwordLayout = new QHBoxLayout();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QPushButton * changePasswordButton = new QPushButton("Valider le changement de mot de passe");
    changePasswordLabel = new QLabel();
    passwordLayout->addWidget(passwordLineEdit);
    passwordLayout->addWidget(changePasswordButton);
    passwordLayout->addWidget(changePasswordLabel);

    layout->addLayout(headerVerticalLayout);
    layout->addWidget(familleProgressBar);
    layout->addStretch(10);
    layout->addLayout(progressGridLayout);
    layout->addStretch(10);
    layout->addWidget(passwordLabel);
    layout->addLayout(passwordLayout);

    connect(plusButton,SIGNAL(clicked()),this,SLOT(addMembreLineEdit()));
    connect(addMembreButton,SIGNAL(clicked()),this,SLOT(addMembre()));
    connect(backButton,SIGNAL(clicked()),parent,SLOT(displayEspaceAbo()));
    connect(changePasswordButton,SIGNAL(clicked()),this,SLOT(changePassword()));

}

void GererCompte::addMembreLineEdit(){
    int n = progressGridLayout->rowCount();
    progressGridLayout->removeWidget(plusButton);
    newMembreLineEdit = new QLineEdit;
    progressGridLayout->addWidget(newMembreLineEdit,n,1);
    progressGridLayout->addWidget(addMembreButton,n,2);
    addMembreButton->setVisible(true);
}

void GererCompte::addMembre(){
    int n = progressGridLayout->rowCount();
    QString newMembreName = newMembreLineEdit->text();
    newMembreLineEdit->clear();
    addDeleteButton(n,0);
    addLabel(n,1,newMembreName);
    addProgressBar(n,2,0);
    progressGridLayout->removeWidget(newMembreLineEdit);
    newMembreLineEdit->hide();
    progressGridLayout->removeWidget(addMembreButton);
    addMembreButton->hide();
    progressGridLayout->addWidget(plusButton,n+1,1);
    Membre * newMembre = new Membre(newMembreName,45);
    std::vector<Membre*>* membres = model->getClients()[model->getIndiceFamilleCourante()]->getMembres();
    membres->push_back(newMembre);
    updateFamilyProgressBar();
}

void GererCompte::deleteMembre(){
    QObject * buttonClicked = sender();
    unsigned int i = 0;
    while((deleteButtonsVector->at(i) != buttonClicked) & (i<deleteButtonsVector->size())){
      i+=1;
    }
    progressGridLayout->removeWidget(deleteButtonsVector->at(i));
    progressGridLayout->removeWidget(labelsVector->at(i));
    progressGridLayout->removeWidget(progressBarsVector->at(i));
    deleteButtonsVector->at(i)->hide();
    labelsVector->at(i)->hide();
    progressBarsVector->at(i)->hide();
    deleteButtonsVector->erase(deleteButtonsVector->begin()+i);
    labelsVector->erase(labelsVector->begin()+i);
    progressBarsVector->erase(progressBarsVector->begin()+i);
    std::vector<Membre*>* membres = model->getClients()[model->getIndiceFamilleCourante()]->getMembres();
    membres->erase(membres->begin()+i);
    updateFamilyProgressBar();
}

void GererCompte::addDeleteButton(int row, int column){
    QToolButton * deleteButton = new QToolButton();
    deleteButton->setIcon(QIcon(":images/poubelle.png"));
    deleteButton->setIconSize(QSize(25,25));
    deleteButton->setStyleSheet("QToolButton{border-radius: 0px;}");
    deleteButtonsVector->push_back(deleteButton);
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteMembre()));
    progressGridLayout->addWidget(deleteButton,row,column);
}

void GererCompte::addLabel(int row, int column, QString name){
    QLabel * newMembreLabel = new QLabel(name);
    progressGridLayout->addWidget(newMembreLabel,row,column);
    labelsVector->push_back(newMembreLabel);
}

void GererCompte::addProgressBar(int row, int column, int progress){
    QProgressBar * newMembreProgressBar = new QProgressBar();
    newMembreProgressBar->setValue(progress);
    progressBarsVector->push_back(newMembreProgressBar);
    progressGridLayout->addWidget(newMembreProgressBar,row,column);
}

void GererCompte::updateFamilyProgressBar(){
    std::vector<Membre*>* membres = model->getClients()[model->getIndiceFamilleCourante()]->getMembres();
    float progressBarValue = 0;
    int n = membres->size();
    for(int i=0;i<n;i++){
        progressBarValue+=membres->at(i)->getProgress();
    }
    if(n!=0){
        progressBarValue = (float) (progressBarValue/membres->size());
    }
    familleProgressBar->setValue(floor(progressBarValue));
    if(progressBarValue<33){
        familleProgressBar->setFormat("Nouveaux");
    }
    else if(progressBarValue<66){
        familleProgressBar->setFormat("Réguliers");
    }
    else if(progressBarValue<99){
        familleProgressBar->setFormat("Habitués");
    }
    else{
        familleProgressBar->setFormat("VIP");
    }
}

void GererCompte::changePassword(){
    Famille * famille = model->getClients()[model->getIndiceFamilleCourante()];
    famille->setPassword(passwordLineEdit->text());
    changePasswordLabel->setText("Mot de passe mis à jour");
}
