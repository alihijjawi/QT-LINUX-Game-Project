#include "gameMenu.h"
#include "mainWidget.h"
#include "game1menu.h"
#include "previouscores.h"
#include "collectable.h"
#include "game2menu.h"
/**
* \file gameMenu.cpp
* \brief creates the UI for entering the different games and check history scores
*
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
gameMenu::gameMenu(QJsonValue user,QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    loggedInUser = user;
    if (user == QJsonValue::Null) {
        guest = true;
    }
    else
        guest = false;

    playGame1 = new QPushButton("BattleShips Menu");
    playGame2 = new QPushButton("Shooting Discs Menu");
    signOut = new QPushButton("Sign Out");
    checkPrevScores = new QPushButton("Check Previous Scores");
    editText1 = new QTextEdit;
    editText1->setReadOnly(true);
    editText1->setMaximumHeight(150);
    editText1->setMaximumWidth(250);
    mainVBoxLayout = new QVBoxLayout;
    internalGridLayout = new QGridLayout;
    internalGridLayout2 = new QGridLayout;

    this->setFixedSize(600,450);

    if (!guest) {
        getPic();
        setInternalLayout2();
    }

    setInternalLayout();
    setMainLayout();

    QString currDate = QDate::currentDate().toString();
    QString fName = user.toObject().value("C-firstName").toString();
    QString lName = user.toObject().value("D-lastName").toString();
    QString Name = "";
    if (guest == false)
         Name = fName+" "+lName;
    else
        Name = "Guest";

    QString s1 = "Welcome "+Name+"!\n"+
                "Current date: "+currDate+"\n"+"\n"+
                "Please choose a game to play!";

    editText1->setText(s1);

    QObject::connect(signOut, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));
    QObject::connect(playGame1, SIGNAL(clicked(bool)), this, SLOT(playGame1slot()));
    QObject::connect(playGame2, SIGNAL(clicked(bool)), this, SLOT(playGame2slot()));
    QObject::connect(checkPrevScores, SIGNAL(clicked(bool)), this,SLOT(checkPreviousScores()));

    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Game Menu");
    QPixmap bkgnd(":/Game1Files/gameMenu.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
    show();
}

void gameMenu::setInternalLayout2(){
    internalGridLayout2->addWidget(ppLabel,0,0);
    getCountryPic();
    QPixmap pp(pathC);
    cpLabel = new QLabel("Country Picture");
    cpLabel->setPixmap(pp.scaled(38,23));
    internalGridLayout2->addWidget(cpLabel,1,1);

}


void gameMenu::setInternalLayout(){
    internalGridLayout->addWidget(editText1,0,0);
    internalGridLayout ->addItem(new QSpacerItem(120,0), 0, 1);
    internalGridLayout->addItem(internalGridLayout2,0,2);
    internalGridLayout ->addItem(new QSpacerItem(0,30), 1, 0);


}


void gameMenu::setMainLayout(){
    mainVBoxLayout->addItem(internalGridLayout);
    if (!guest)
        mainVBoxLayout->addWidget(checkPrevScores,2,0);
    mainVBoxLayout ->addItem(new QSpacerItem(0,10));
    mainVBoxLayout->addWidget(playGame1,4,0);
    mainVBoxLayout ->addItem(new QSpacerItem(0,10));
    mainVBoxLayout->addWidget(playGame2,6,0);
    mainVBoxLayout ->addItem(new QSpacerItem(0,10));
    mainVBoxLayout->addWidget(signOut,8,0);
    setLayout(mainVBoxLayout);
}

void gameMenu::returnToMenu() {
    this->close();
    new mainWidget();

}

void gameMenu::playGame1slot() {
    this->close();
    new game1menu(loggedInUser);
}

void gameMenu::playGame2slot() {


   this->close();
   new game2menu(loggedInUser);


}

void gameMenu::checkPreviousScores() {
    this->close();
    new previouscores(loggedInUser);
}



void gameMenu::getCountryPic(){

    QLabel *countryName = new QLabel(country);
    internalGridLayout2->addWidget(countryName,1,0);
    QString path = ":/FlagImages/";
    pathC = path + country+"F";

}
void gameMenu::getPic(){
    userName = loggedInUser.toObject().value("A-username").toString();
    QString path = "/home/eece435l/HassanAliData/ProfilePics/";
    path = path + userName;
    QPixmap pp(path);
    ppLabel = new QLabel("Profile Picture");
    ppLabel->setPixmap(pp.scaled(130,95));
    country = loggedInUser.toObject().value("H-Country").toString();

}
