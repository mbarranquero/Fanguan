#include "carte.h"
#include <QApplication>

#include "template.h"
#include "detail.h"
#include "connexion.h"
#include "mainwindow.h"
#include "connexion.h"
#include "inscription.h"
#include "espaceabo.h"
#include "accueil.h"
#include "gerercompte.h"
#include "catalogue.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}
