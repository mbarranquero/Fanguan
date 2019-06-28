#ifndef FAMILLE_H
#define FAMILLE_H
#include <QString>
#include "membre.h"

class Famille
{
private:
    QString name;
    QString password;
    std::vector<Membre*> * membres;

public:
    Famille();
    Famille(QString name, QString password);
    QString getName();
    QString getPassword();
    int getSize();
    void setPassword(QString password);
    std::vector<Membre*> * getMembres();
    void addMembre(Membre * membre);
};

#endif // FAMILLE_H
