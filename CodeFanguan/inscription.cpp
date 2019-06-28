#include "inscription.h"

Inscription::Inscription(QWidget *parent, Model * m) : QWidget(parent)
{
    model = m;
    QVBoxLayout * layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setMargin(100);
    QFormLayout * formLayout = new QFormLayout();
    nomCompteLineEdit = new QLineEdit();
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QSpinBox * nombrePersonnesSpinBox = new QSpinBox();
    scrollArea = new QScrollArea();


    membresFormLayout = new QFormLayout();
    membresVector = new std::vector<QLineEdit*>();
    scrollArea->setLayout(membresFormLayout);
    QPushButton * validerButton = new QPushButton("Valider le compte");

    validerButton->setFont(model->getButtonFont());
    noMembreErrorLabel = new QLabel();

    formLayout->addRow(tr("&Nom du compte"),nomCompteLineEdit);
    formLayout->addRow(tr("&Mot de passe"),passwordLineEdit);
    formLayout->addRow(tr("&Nombre de personnes associees:"),nombrePersonnesSpinBox);
    layout->addLayout(formLayout);
    layout->addWidget(scrollArea);
    layout->addWidget(validerButton);
    layout->addWidget(noMembreErrorLabel);

    connect(nombrePersonnesSpinBox,SIGNAL(valueChanged(int)),this,SLOT(displayMembres(int)));
    connect(validerButton,SIGNAL(clicked()),this,SLOT(addFamille()));
    connect(this,SIGNAL(compteCree()),parent,SLOT(displayEspaceAbo()));

}

void Inscription::displayMembres(int n){
    for(unsigned int j =0; j<=membresVector->size(); j++){
        if(membresFormLayout->rowCount()>0){
         membresFormLayout->removeRow(0);
        }
    }
    membresVector->clear();
    for(int i = 1; i<=n; i++){
        QLineEdit * membreLineEdit = new QLineEdit();

        membresVector->push_back(membreLineEdit);
        membresFormLayout->addRow("&Membre "+QString::number(i)+" :",membreLineEdit);

    }
    QWidget * contentWidget = new QWidget();
    contentWidget->setLayout(membresFormLayout);
    scrollArea->setWidget(contentWidget);
}

void Inscription::addFamille(){
    if(membresVector->size()==0){
        noMembreErrorLabel->setText("Il n'y a aucun membre dans votre famille!");
    }
    else{
        Famille * newFamille = new Famille(nomCompteLineEdit->text(),passwordLineEdit->text());
        int nextId = 0;
        for(unsigned int i = 0; i<model->getClients().size();i++){       //on calcule nombre de membres
            nextId+=model->getClients()[i]->getSize();
        }
        for(unsigned int i = 0; i<membresVector->size();i++){
            Membre * newMembre = new Membre(membresVector->at(i)->text(),nextId);
            newFamille->addMembre(newMembre);
            nextId+=1;
        }
        model->addFamille(newFamille);
        model->setIndiceFamilleCourante(model->getClients().size()-1);
        model->setConnected(true);
        emit(compteCree());
    }
}
