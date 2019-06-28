#ifndef COMMANDEITEM_H
#define COMMANDEITEM_H

#include <QObject>
#include <QLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QFrame>
#include <QLineEdit>
#include "commandemodel.h"
#include "commande.h"

/*Vue correspondant a un item de commande (objet CommandeItem)*/
class CommandeItem : public QFrame
{
    Q_OBJECT
private:
    /*Objet contenant les donnees necessaires d'un item de commande*/
    CommandeModel * commandeModel;

    /*Label afficahnt le prix*/
    QLabel * priceLabel;


public:
    CommandeItem(Commande * com, CommandeModel * commandeModel): QFrame() {
        //Données de la commande
        this->commandeModel = commandeModel;
        int nbUnites = commandeModel->getNbUnites();

        //Création de la vue
        QVBoxLayout * layout = new QVBoxLayout(this);
        QString nomPlat = commandeModel->getItemName();
        QPushButton * itemName = new QPushButton(nomPlat);
        itemName->setIcon(QIcon(":/images/cross.png"));
        itemName->setFont(QFont("Arial", 12));
        QHBoxLayout * bottomLayout = new QHBoxLayout();
        float itemPrice =commandeModel->getItemPrice();
        QSpinBox * quantity =  new QSpinBox();
        quantity->setMinimumHeight(50);
        quantity->setValue(nbUnites);
        quantity->setRange(1, 20);
        quantity->setSuffix(tr(" unite(s)"));
        priceLabel = new QLabel(QString("%1 euros").arg(itemPrice*nbUnites));
        priceLabel->setFont(QFont("Arial", 12));
        bottomLayout->addWidget(quantity);
        bottomLayout->addStretch(5);
        bottomLayout->addWidget(priceLabel);
        QLineEdit * infos = new QLineEdit(commandeModel->getInfos());
        infos->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        layout->addWidget(itemName);
        layout->addLayout(bottomLayout);
        layout->addWidget(infos);
        setLayout(layout);
        setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
        setLineWidth(2);
        layout->setSizeConstraint(QLayout::SetMinimumSize);
        setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        setStyleSheet("background-color : #FFECB3 ");

        connect(quantity, SIGNAL(valueChanged(int)), this, SLOT(changeUnity(int)));
        connect(this, SIGNAL(unityChanged(int)), com, SLOT(displayTotal()));
        connect(itemName, SIGNAL(pressed()), this, SLOT(remove()));
        connect(this, SIGNAL(removed()), com, SLOT(refresh()));
    }

    virtual ~CommandeItem() {}

public slots:
    /*Ce slot est appele lorsque la quantite de l'article commande est modifie par l'utilisateur*/
    void changeUnity(int i){
        float itemPrice = commandeModel->getItemPrice();
        priceLabel->setText(QString("%1 euros").arg(itemPrice*i));
        commandeModel->setNbUnites(i);
        emit unityChanged(i);}

    /*Ce slot est appele lorsque l'utilisateur retire l'objet de sa commande. On passe donc la
    quantite commandee a 0, en effet la vue Commande n'affiche que les commandes dont la quantite
    est superieure a zero.*/
    void remove(){
        commandeModel->setNbUnites(0);
        //this->close();
        emit removed();
        emit unityChanged(0);}

signals:
    /*Ce signal est en envoye quand la quantite commandee est modifier*/
    void unityChanged(int);

    /*Ce signal est en envoye quand l'item doit etre enleve de la commande. La vue commande doit etre rafraichit*/
    void removed();
};

#endif // COMMANDEITEM_H
