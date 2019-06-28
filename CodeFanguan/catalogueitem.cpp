#include "catalogueitem.h"

CatalogueItem::CatalogueItem(Template * temp, Plat * p, bool _inMenu) : QToolButton(){
    plat = p;
    inMenu = _inMenu;
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIcon(QIcon(plat->getImageFile()));
    setIconSize(QSize(150, 120));
    if (inMenu) {
        setText(plat->getLabel());
    }
    else {
        setText(QString("%1 \n %2 euros").arg(plat->getLabel()).arg(plat->getPrix()));
    }

    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
    setStyleSheet("color : black; background-color : #FFECB3  ;");
    connect(this, SIGNAL(clicked()), this, SLOT(sendDetailSignal()));
    connect(this, SIGNAL(detailRequis(Plat*)), temp, SLOT(displayDetail(Plat*)));
}



void CatalogueItem::sendDetailSignal() {
    if (!inMenu) emit detailRequis(plat);
}
