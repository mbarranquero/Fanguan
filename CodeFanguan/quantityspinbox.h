#ifndef QUANTITYSPINBOX_H
#define QUANTITYSPINBOX_H

#include <QWidget>
#include "membre.h"
#include "model.h"
#include <QSpinBox>
#include "plat.h"
#include <QLineEdit>

/*Correspond au spin box permettant d'attribuer l'article commande dans la vue detail*/
class QuantitySpinBox : public QWidget
{
    Q_OBJECT
private:
    Membre * membre = nullptr;
    Model * model = nullptr;
    QSpinBox * quantity =nullptr;
    Plat * plat = nullptr;
    /*line edit de la vue detail, contient les requetes particulieres renseignees par
    l'utilisateur*/
    QLineEdit *infosLineEdit = nullptr;

public:
    QuantitySpinBox(Model * m, Membre * memb, Plat * p, QLineEdit* infosLineEdit = nullptr);
    virtual ~QuantitySpinBox() {}

signals:

public slots:
    void validateQuantity();
};

#endif // QUANTITYSPINBOX_H
