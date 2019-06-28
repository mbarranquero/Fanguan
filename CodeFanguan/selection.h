//Plus tard
#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include"model.h"
#include "template.h"

/*Cette classe correspond a la vue du tapis roulant*/
class Selection : public QWidget
{
    Q_OBJECT
public:
    explicit Selection(Template *parent = nullptr, Model * m = nullptr, std::vector<Plat *> listePlat = std::vector<Plat *>());

signals:

public slots:
    void moveBar();

private:
    QWidget * centralWidget = nullptr;
    QLayout * centralLayout = nullptr;
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    Model * model = nullptr;
    QScrollArea * scrollArea = new QScrollArea();
    int mode = 0;
    int position =0;
};

#endif // SELECTION_H
