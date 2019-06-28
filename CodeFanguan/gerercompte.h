//Gérer Compte
#ifndef GERERCOMPTE_H
#define GERERCOMPTE_H

#include <QWidget>
#include <QLayout>
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QIcon>
#include <QToolButton>
#include <QPushButton>
#include <QIcon>
#include <iostream>
#include <math.h>
#include "model.h"

/*Correspond a la vue de la gestion de compte*/
class GererCompte : public QWidget
{
    Q_OBJECT
private:
    Model * model;
    QGridLayout * progressGridLayout;
    QToolButton * plusButton;
    QProgressBar * familleProgressBar;
    QLineEdit * newMembreLineEdit = new QLineEdit();
    QPushButton * addMembreButton = new QPushButton("Ajouter");
    std::vector<QToolButton *> * deleteButtonsVector = new std::vector<QToolButton*>;
    std::vector <QLabel*> * labelsVector = new std::vector<QLabel*>;
    std::vector <QProgressBar*> * progressBarsVector = new std::vector<QProgressBar*>;
    QLineEdit * passwordLineEdit;
    QLabel * changePasswordLabel;

    QWidget * centralWidget;
    QLayout * centralLayout;
    QVBoxLayout * mainLayout;

public:
    explicit GererCompte(QWidget *parent = nullptr, Model * m = nullptr);
    void addDeleteButton(int row, int column);
    void addLabel(int row, int column, QString name);
    void addProgressBar(int row, int column, int progress);
    void updateFamilyProgressBar();

signals:

public slots:
    void addMembreLineEdit();
    void addMembre();
    void deleteMembre();
    void changePassword();
};

#endif // GERERCOMPTE_H
