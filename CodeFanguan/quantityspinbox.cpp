#include "quantityspinbox.h"
#include <QBoxLayout>
#include "commandemodel.h"
#include <iostream>

QuantitySpinBox::QuantitySpinBox(Model * m, Membre * memb, Plat * p, QLineEdit* infos) : QWidget()
{
       model = m;
       membre = memb;
       plat = p;
       infosLineEdit = infos;
       QHBoxLayout * layout = new QHBoxLayout(this);
       quantity =  new QSpinBox();
       quantity->setValue(1);
       if (model->getConnected()) {
           QLabel * name = new QLabel(membre->getName());
           layout->addWidget(name);
           quantity->setValue(0);
       }
       quantity->setMinimumHeight(50);
       quantity->setRange(0, 20);
       quantity->setSuffix(tr(" unite(s)"));
       layout->addWidget(quantity);
}

void QuantitySpinBox::validateQuantity() {
    int nbUnite = quantity->value();
    if (nbUnite > 0) {
        CommandeModel * cm = new CommandeModel(plat->getLabel(), plat->getPrix(), nbUnite);
        if (model->getConnected()) {
            membre->addCommande(cm);
            cm->setInfos(infosLineEdit->text());
        } else {
            model->addCommande(cm);
            cm->setInfos(infosLineEdit->text());
        }
    }
}
