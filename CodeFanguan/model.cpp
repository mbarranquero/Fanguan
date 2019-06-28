#include "model.h"
#include <QtSql>

Model::Model(){
    //Création d'une famille
    Membre * farida = new Membre("Farida", 1);
    farida->setProgress(56);
    farida->addAvantage("Dessert à moitié prix");
    Membre * samy = new Membre("Samy", 2);
    samy->setProgress(89);
    samy->addAvantage("-10% sur les nems");
    Membre * clara = new Membre("Clara", 3);
    clara->setProgress(63);
    clara->addAvantage("Saqué offert");
    Membre * ines = new Membre("Ines", 4);
    ines->setProgress(58);
    ines->addAvantage("Riz à volonté");
    Famille * safi = new Famille("Safi", "password");
    safi->addMembre(farida);
    safi->addMembre(samy);
    safi->addMembre(clara);
    safi->addMembre(ines);
    clients.push_back(safi);
    indiceFamilleCourante = 0;

    //Elaboration de la carte

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath().append("/fanguan_bdd.sqlite"));

    bool ok = db.open();

    //Entrées
    if (ok) {

        QString nom, fichierImage, description;
        int id;
        float prix;
        Plat * e1 = nullptr;

        //Entrées
        QSqlQuery query(db);
        std::cout << "## chargement entree" << std::endl;
        query.exec("SELECT id, nom, fichierImage, prix, description FROM PLATS WHERE categorie = 'entree' ");
        while (query.next()) {
            id = query.value(0).toInt();
            nom = query.value(1).toString();
            fichierImage = query.value(2).toString();
            prix = query.value(3).toFloat();
            description = query.value(4).toString();
            e1 = new Plat(id);
            e1->setLabel(nom);
            e1->setImageFile(fichierImage);
            e1->setPrix(prix);
            e1->setDescription(description);
            addEntree(e1);
            carteEntiere.push_back(e1);
        }

        //Plats
        std::cout << "## chargement plat" << std::endl;
        QSqlQuery query2(db);
        query2.exec("SELECT id, nom, fichierImage, prix, description FROM PLATS WHERE categorie = 'plat' ");
        while (query2.next()) {
            id = query2.value(0).toInt();
            nom = query2.value(1).toString();
            fichierImage = query2.value(2).toString();
            prix = query2.value(3).toFloat();
            description = query2.value(4).toString();
            e1 = new Plat(id);
            e1->setLabel(nom);
            e1->setImageFile(fichierImage);
            e1->setPrix(prix);
            e1->setDescription(description);
            addPlat(e1);
            carteEntiere.push_back(e1);
        }

        //Dessert
        std::cout << "## chargement desserts" << std::endl;
        QSqlQuery query3(db);
        query3.exec("SELECT id, nom, fichierImage, prix, description FROM PLATS WHERE categorie = 'dessert' ");
        while (query3.next()) {
            id = query3.value(0).toInt();
            nom = query3.value(1).toString();
            fichierImage = query3.value(2).toString();
            prix = query3.value(3).toFloat();
            description = query3.value(4).toString();
            e1 = new Plat(id);
            e1->setLabel(nom);
            e1->setImageFile(fichierImage);
            e1->setPrix(prix);
            e1->setDescription(description);
            addDessert(e1);
            carteEntiere.push_back(e1);
        }

        //Dessert

        QSqlQuery query4(db);
        query4.exec("SELECT id, nom, fichierImage, prix, description FROM PLATS WHERE categorie = 'boisson' ");
        while (query4.next()) {
            id = query4.value(0).toInt();
            nom = query4.value(1).toString();
            fichierImage = query4.value(2).toString();
            prix = query4.value(3).toFloat();
            description = query4.value(4).toString();
            e1 = new Plat(id);
            e1->setLabel(nom);
            e1->setImageFile(fichierImage);
            e1->setPrix(prix);
            e1->setDescription(description);
            addBoisson(e1);

        }
    }

    else {
        std::cout << db.lastError().text().toStdString() << std::endl;
        std::cout << "fail" << std::endl;
    }


    //Menus
    MenuModel * m1 = new MenuModel("Cantonais", 16);
    m1->addMenuEntree(carteEntrees[0]);
    m1->addMenuEntree(carteEntrees[3]);

    m1->addMenuPlat(cartePlats[3]);
    m1->addMenuDessert(carteDesserts[0]);
    m1->addMenuDessert(carteDesserts[1]);
    addMenu(m1);

    MenuModel * m2 = new MenuModel("Japonais", 21);
    m2->addMenuEntree(carteEntrees[1]);
    m2->addMenuEntree(carteEntrees[2]);
    m2->addMenuPlat(cartePlats[1]);
    m2->addMenuPlat(cartePlats[2]);
    m2->addMenuDessert(carteDesserts[0]);
    m2->addMenuDessert(carteDesserts[1]);
    addMenu(m2);



    //Ajout plats favoris et recommandations à famille Safi
    for(unsigned int i = 0; i+3<carteEntiere.size(); i+=4){
        farida->addFavori(carteEntiere[i]);
        farida->addRecommendation(carteEntiere[i]);
        samy->addFavori(carteEntiere[i+1]);
        samy->addRecommendation(carteEntiere[i+1]);
        clara->addFavori(carteEntiere[i+2]);
        clara->addRecommendation(carteEntiere[i+2]);
        ines->addFavori(carteEntiere[i+3]);
        ines->addRecommendation(carteEntiere[i+3]);
    }
}

void Model::addDessert(Plat *dessert){
    carteDesserts.push_back(dessert);
}

void Model::addPlat(Plat * plat){
    cartePlats.push_back(plat);
}

void Model::addEntree(Plat *entree){
    carteEntrees.push_back(entree);
}

void Model::addBoisson(Plat *boisson){
    carteBoissons.push_back(boisson);
}


void Model::addMenu(MenuModel *menu){
    carteMenus.push_back(menu);
}

std::vector<Plat*> Model::getEntrees(){
    return carteEntrees;
}

std::vector<Plat*> Model::getBoissons(){
    return carteBoissons;
}

std::vector<Plat*> Model::getPlats(){
    return cartePlats;
}

std::vector<Plat*> Model::getDesserts(){
    return carteDesserts;
}

std::vector<MenuModel*> Model::getMenus(){
    return carteMenus;
}

std::vector<Plat*>  Model::getCarteEntiere() {
    return carteEntiere;
}

QFont Model::getTitleFont(){
    return QFont("Helvetica", 30, QFont::Bold);
}

QFont Model::getAccueilButtonFont(){
    return QFont("Helvetica", 15, QFont::Bold);
}

QFont Model::getButtonFont(){
    return QFont("Helvetica", 20, QFont::Bold);
}

QFont Model::getTextFont(){
    return QFont("Helvetica", 15);
}

QFont Model::getPlatFont(){
    return QFont("Helvetica", 12);
}

std::vector<Famille*> Model::getClients(){
    return clients;
}

void Model::addFamille(Famille * famille){
    clients.push_back(famille);
}

int Model::getIndiceFamilleCourante(){
    return indiceFamilleCourante;
}

void Model::setIndiceFamilleCourante(int indice){
    indiceFamilleCourante = indice;
}

void Model::addCommande(CommandeModel * cm){
    listeCommandes.push_back(cm);
}

void Model::setTotal(float t){
    total = t;
}

void Model::calculateTotal(){
    total = 0;
    if(connected){
        Famille * famille = clients[indiceFamilleCourante];
        for(int i = 0; i < famille->getSize(); i++){
            Membre * membre = famille->getMembres()->at(i);
            total += membre->getSousTotal();
        }
    }
    else{
        for(unsigned int i = 0; i < listeCommandes.size(); i++){
            CommandeModel * cm = listeCommandes[i];
            int quantity = cm->getNbUnites();
            total += cm->getItemPrice()*quantity;
        }
    }
}

void Model::clear() {

    Famille * familleCourante = clients[indiceFamilleCourante];
    std::vector<Membre*> * membresCourants = familleCourante->getMembres();
    std::vector<Membre*> * membres = familleCourante->getMembres();
    for(unsigned int i = 0; i < membres->size(); i++){
        Membre * membreCourant = membresCourants->at(i);
        membreCourant->clearCommande();
    }
    listeCommandes.clear();

}
