#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "accueil.h"
#include "template.h"
#include "carte.h"
#include "catalogue.h"
#include "gerercompte.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    model = new Model();
    Accueil* acc = new Accueil(this);
//    acc->setObjectName(QObject::tr("tata"));
//    acc->setStyleSheet("QWidget#tata {border-image: url(:/images/fondFanguan.png) 0 0 0 0 stretch stretch;}");
    setCentralWidget(acc);
    setMinimumSize(1024, 740);
    setStyleSheet(" QMainWindow {background-color : white};QPushButton {color black; background-color :#FFCB60;}");

    //setStyleSheet(" QWidget#tata {border-image: url(:/images/fondFanguan.png) 0 0 0 0 stretch stretch;} QPushButton {color black; background-color :#FFCB60;} ");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayCarte() {
    setCentralWidget(new Template(this, model, Template::CARTE));
}

void MainWindow::displayRecherche() {
    setCentralWidget(new Template(this, model, Template::RECHERCHE));
}

void MainWindow::displayEspaceAbo() {
    setCentralWidget(new Template(this, model, Template::CONNEXION));
}

void MainWindow::displaySelection() {
    setCentralWidget(new Template(this, model, Template::SELECTION));
}


