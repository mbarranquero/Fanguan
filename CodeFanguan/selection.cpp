#include "selection.h"
#include "catalogue.h"
#include <QBoxLayout>
#include <QTimer>
#include <QScrollBar>
#include<QLabel>
#include<QGroupBox>

Selection::Selection(Template *parent, Model * m, std::vector<Plat *> listePlat) : QWidget(parent)
{
    model = m;
    QLabel * image = new QLabel();
    QPixmap pix = QPixmap(":/images/selectionchef2.png");
    image->setPixmap(pix);
    image->setScaledContents(true);
    image->setObjectName("tito");
    image->setStyleSheet("QWidget#tito{border-image: url(:/images/fondFanguan.png) 0 0 0 0 stretch stretch;} ");
    mainLayout->addWidget(image);

    QLabel * imageTapis = new QLabel();
    QPixmap pix2 = QPixmap(":/images/tapis.png");
    imageTapis->setPixmap(pix2);
    imageTapis->setScaledContents(true);

    QWidget * ligneContentWidget = new QWidget();
    scrollArea->setAlignment(Qt::AlignCenter);
    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff);
    scrollArea->setMinimumHeight(210);
    scrollArea->setMaximumHeight(250);
    QHBoxLayout * ligneLayout = new QHBoxLayout();

    ligneContentWidget->setObjectName(QObject::tr("toto"));

    ligneContentWidget->setStyleSheet("QWidget#toto{background-image: url(:/images/tapis.png)} ");
    ligneLayout->setSpacing(50);

    for(unsigned int i = 0; i<listePlat.size();i++){
        Plat * plat = listePlat[i];
        CatalogueItem * item = new CatalogueItem(parent, plat);
        ligneLayout->addWidget(item);
    }

    QTimer * timerH = new QTimer();

    timerH->start(100);

    ligneContentWidget->setLayout(ligneLayout);
    scrollArea->setWidget(ligneContentWidget);

    mainLayout->addWidget(scrollArea);
    connect(timerH, SIGNAL(timeout()), this, SLOT(moveBar()));
    setLayout(mainLayout);
}

void Selection::moveBar(){
    QScrollBar* sb = scrollArea->horizontalScrollBar();
    position = sb->value();
    int max = scrollArea->horizontalScrollBar()->maximum();
    int min = scrollArea->horizontalScrollBar()->minimum();
    if((position < max - 3) && (mode ==0)){
        position += 3;
    }
    if (position >= max - 3){
        mode = 1;
    }
    if((mode == 1) && (position > min)){
        position -= 3;
    }
    if (position <= min + 3){
        mode = 0;
    }
    if(min < position && position < max){
        sb->setValue(position);
    }
}
