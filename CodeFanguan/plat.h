#ifndef PLAT_H
#define PLAT_H

#include<QLabel>
#include<QIcon>

class Plat
{
public:
    Plat(int);

    QString getLabel();
    QString getDescription();
    QString getImageFile();
    float getPrix();
    int getId();
    std::vector<QString> getIngredients();

    void setLabel(QString);
    void setDescription(QString);
    void setImageFile(QString);
    void setPrix(float);
    void setId(int);
    void setIngredients(std::vector<QString>);


private:
    int id = 0;
    QString label = "defaut";
    float prix = 0.0;
    QString description = "";
    QString imageFile = "path";
    std::vector<QString> ingredients = std::vector<QString>();
};

#endif // PLAT_H
