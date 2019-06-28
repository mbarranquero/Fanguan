#include "accueil.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>

Accueil::Accueil(QWidget *parent, Model * m) : QWidget(parent)
{
    model = m ;

    QVBoxLayout * mainLayout = new QVBoxLayout();

    QHBoxLayout * topLayout = new QHBoxLayout();
    topLayout->setSpacing(0);

    QPushButton * frButton = new QPushButton("Fr");
    frButton->setIcon(QIcon(":/images/france.jpg"));
    frButton->setMinimumSize(QSize(50, 40));
    QPushButton * engButton = new QPushButton("Eng");
    engButton->setIcon(QIcon(":/images/angleterre.jpg"));
    engButton->setMinimumSize(QSize(50, 40));
    QPushButton * chButton = new QPushButton("Ch");
    chButton->setIcon(QIcon(":/images/chine.png"));
    chButton->setMinimumSize(QSize(50, 40));

    QSizePolicy langSizePolicy = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    frButton->setSizePolicy(langSizePolicy);
    engButton->setSizePolicy(langSizePolicy);
    chButton->setSizePolicy(langSizePolicy);

    topLayout->addWidget(frButton);
    topLayout->addWidget(engButton);
    topLayout->addWidget(chButton);
    topLayout->addStretch();

    welcomeSentence->setPixmap(pix.scaled(QSize(500, 500), Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation));

    welcomeSentence->setAlignment(Qt::AlignHCenter);
    welcomeSentence->setFont(model->getTitleFont());
    welcomeSentence->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum));

    mainWidget->setMinimumSize(QSize(600, 400));
    mainWidget->setObjectName(QObject::tr("tata"));
    mainWidget->setStyleSheet("QWidget#tata{border-image: url(:/images/fondFanguan.png) 0 0 0 0 stretch stretch;} ");

    class AccueilButton : public QPushButton
    {
    public:
        AccueilButton(QString label, QString imageFile) : QPushButton() {
            Model * model = new Model();
            setMinimumSize(QSize(200, 150));
            setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum));
            setFont(model->getAccueilButtonFont());
            setStyleSheet("color : black; background-color : #FFCB60;");
            QVBoxLayout * layout = new QVBoxLayout(this);
            QLabel * image = new QLabel();
            image->setAlignment(Qt::AlignHCenter);
            QPixmap pix(imageFile);
            image->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            image->setPixmap(pix.scaled(QSize(150, 100), Qt::IgnoreAspectRatio,
                                        Qt::SmoothTransformation));
            layout->addWidget(image);

            QLabel* title = new QLabel(label);
            title->setAlignment(Qt::AlignHCenter);
            title->setFont(model->getAccueilButtonFont());
            layout->addWidget(title);
        }
        virtual ~AccueilButton() {}
    };
    QPushButton * carteButton = new AccueilButton("Carte",":/images/menu.png");
    QPushButton * aboButton = new AccueilButton("Espace Habitue", ":/images/smileymaison.png");
    QPushButton * rechercheButton = new AccueilButton("Recherche",":/images/loupe.png");
    QPushButton * selectionButton = new AccueilButton("Notre Selection",":/images/toque.png");

    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(5);
    buttonLayout->addWidget(aboButton);
    buttonLayout->addWidget(carteButton);
    buttonLayout->addWidget(rechercheButton);
    buttonLayout->addWidget(selectionButton);
    buttonLayout->addStretch(5);
    buttonLayout->setSpacing(25);

    QHBoxLayout * serveurLayout = new QHBoxLayout();
    serveurButton = new AccueilButton("Serveur", ":/images/bell.png");
    serveurLayout->addStretch(5);
    serveurLayout->addWidget(serveurButton);
    serveurLayout->addStretch(5);

    mainLayout->addLayout(topLayout);
    mainLayout->addStretch(3);
    mainLayout->addWidget(welcomeSentence);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch(1);
    mainLayout->addLayout(serveurLayout);
    mainLayout->addStretch(5);

    mainWidget->setLayout(mainLayout);

    QVBoxLayout * centralLayout = new QVBoxLayout();
    centralLayout->addWidget(mainWidget);
    setLayout(centralLayout);

    connect(aboButton, SIGNAL(clicked()), parent, SLOT(displayEspaceAbo()));
    connect(rechercheButton, SIGNAL(clicked()), parent, SLOT(displayRecherche()));
    connect(carteButton, SIGNAL(clicked()), parent, SLOT(displayCarte()));
    connect(selectionButton, SIGNAL(clicked()), parent, SLOT(displaySelection()));
    connect(serveurButton, SIGNAL(clicked()), this, SLOT(appelServeur()));

    connect(engButton, SIGNAL(clicked()), this, SLOT(changeLangueEN()));
    connect(frButton, SIGNAL(clicked()), this, SLOT(changeLangueFR()));
    connect(chButton, SIGNAL(clicked()), this, SLOT(changeLangueCH()));
}

void Accueil::changeLangueFR(){
    pix = QPixmap(":/images/titreFanguan.png" );
    welcomeSentence->setPixmap(pix.scaled(QSize(500, 500), Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation));
}

void Accueil::changeLangueEN(){
    pix = QPixmap(":/images/titreFanguan_EN.png" );
    welcomeSentence->setPixmap(pix.scaled(QSize(500, 500), Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation));
}

void Accueil::changeLangueCH(){
    pix = QPixmap(":/images/titreFanguan_CH.png" );
    welcomeSentence->setPixmap(pix.scaled(QSize(500, 500), Qt::KeepAspectRatio,
                                          Qt::SmoothTransformation));
}
void Accueil::appelServeur() {
    serveurButton->setText("Un serveur arrive !");
    serveurButton->setDisabled(true);
    QTimer * serveurTimer = new QTimer();
    serveurTimer->setSingleShot(true);
    serveurTimer->start(10000);
    connect(serveurTimer, SIGNAL(timeout()), this, SLOT(leServeurEstArrive()));
}

void Accueil::leServeurEstArrive() {
    serveurButton->setText("Appeler serveur");
    serveurButton->setDisabled(false);
}
