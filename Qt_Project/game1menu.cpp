#include "game1menu.h"
#include "gameMenu.h"
#include "game1scene.h"


/**
* \file game1menu.cpp
* \brief creates the pre-menu game that allows the user to configure difficulty and topic ideas
*
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
game1menu::game1menu(QJsonValue user,QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    loggedInUser = user;
    intialize();
    setInternalLayout();
    setMainLayout();
    this->setFixedSize(600,450);

    QObject::connect(back, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));
    QObject::connect(playGame, SIGNAL(clicked(bool)), this, SLOT(playGameSlot()));



    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Battleships Menu");
    show();



}

void game1menu::intialize(){
    QPixmap bkgnd(":/Game1Files/menu1.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);

    topicLabel = new QLabel("Pick Topic:");
    topicLabel->setStyleSheet("font-weight: bold");
    topic1RadioButton = new QRadioButton("Good vs Bad Coding Practices");
    topic2RadioButton = new QRadioButton("Pop Culture");
    topic3RadioButton = new QRadioButton("Health");

    difficultyLabel = new QLabel("Pick Difficulty:");
    difficultyLabel->setStyleSheet("font-weight: bold");
    easyRadioButton = new QRadioButton("Easy (10min Time Limit)");
    mediumRadioButton = new QRadioButton("Medium (5min Time Limit)");
    hardRadioButton = new QRadioButton("Hard (2min Time Limit)");

    playGame = new QPushButton("Play!");
    back = new QPushButton("Back");
    topicGroupBox = new QGroupBox();
    topicVBoxLayout = new QVBoxLayout();

    diffGroupBox = new QGroupBox();
    diffVBoxLayout = new QVBoxLayout();

    internalGridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();

}

void game1menu::setInternalLayout(){
    topicVBoxLayout->addWidget(topic1RadioButton);
    topicVBoxLayout->addWidget(topic2RadioButton);
    topicVBoxLayout->addWidget(topic3RadioButton);
    topicGroupBox->setLayout(topicVBoxLayout);

    diffVBoxLayout->addWidget(easyRadioButton);
    diffVBoxLayout->addWidget(mediumRadioButton);
    diffVBoxLayout->addWidget(hardRadioButton);
    diffGroupBox->setLayout(diffVBoxLayout);

    internalGridLayout->addWidget(topicLabel,0,0);
    internalGridLayout->addWidget(topicGroupBox,0,1);

    internalGridLayout->addWidget(difficultyLabel,1,0);
    internalGridLayout->addWidget(diffGroupBox,1,1);
}

void game1menu::setMainLayout(){
    mainLayout->addItem(internalGridLayout);
    mainLayout->addWidget(playGame);
    mainLayout->addWidget(back);
    setLayout(mainLayout);
}

void game1menu::returnToMenu() {
    this->close();
    new gameMenu(loggedInUser);

}

void game1menu::playGameSlot() {
    bool go = checkParameters();
    if (go){
    this->close();
    new game1scene(loggedInUser,topic,diff);
    }

}

void game1menu::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_F1){
        bool go = checkParameters();
        if (go){
            this->close();
            new game1scene(loggedInUser,topic,diff);
        }
    }
}

bool game1menu::checkParameters(){
    if (topic1RadioButton->isChecked()||topic2RadioButton->isChecked()||topic3RadioButton->isChecked()){}
    else {
        QMessageBox::critical(this,"Error","Please choose a topic");
        return false;
    }
    if(easyRadioButton->isChecked()||mediumRadioButton->isChecked()||hardRadioButton->isChecked()){}
    else {
        QMessageBox::critical(this,"Error","Please choose a difficulty");
        return false;
    }
    if (topic1RadioButton->isChecked())
            topic = "1";
    if (topic2RadioButton->isChecked())
            topic = "2";
    if (topic3RadioButton->isChecked())
            topic = "3";

    if (easyRadioButton->isChecked())
            diff = "easy";
    if (mediumRadioButton->isChecked())
            diff = "medium";
    if (hardRadioButton->isChecked())
            diff = "hard";
    return true;
}
