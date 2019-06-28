//Julien
#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QWidget>
#include <QLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QToolButton>
#include <QPushButton>
#include <QScrollArea>
#include <iostream>

#include "model.h"
#include "template.h"

class Inscription : public QWidget
{
    Q_OBJECT
private:
    Model* model;
    QFormLayout * membresFormLayout;
    QScrollArea * scrollArea;
    std::vector<QLineEdit*> * membresVector;
    QLineEdit * nomCompteLineEdit;
    QLineEdit * passwordLineEdit;
    QLabel * noMembreErrorLabel;

public:
    explicit Inscription(QWidget *parent = nullptr, Model * m = nullptr);

signals:
    void compteCree();

public slots:
    void displayMembres(int n);
    void addFamille();
};

#endif // INSCRIPTION_H
