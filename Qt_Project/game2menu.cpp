#include "game2menu.h"
#include "gameMenu.h"
#include "game2scene.h"


/**
* \file game2menu.cpp
* \brief creates the pre-menu game that allows the user to configure difficulty and topic ideas
*
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
game2menu::game2menu(QJsonValue user,QWidget *parent) : QWidget(parent)
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
    setWindowTitle("Shooting Discs Menu");
    show();



}

void game2menu::intialize(){
    QPixmap bkgnd(":/Game2Files/menu2.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);

    topicLabel = new QLabel("Pick Background:");
    topicLabel->setStyleSheet("font-weight: bold");
    topic1RadioButton = new QRadioButton("Hell");
    topic2RadioButton = new QRadioButton("Desert");
    topic3RadioButton = new QRadioButton("City");

    difficultyLabel = new QLabel("Pick Difficulty:");
    difficultyLabel->setStyleSheet("font-weight: bold");
    easyRadioButton = new QRadioButton("Easy (Slow spawn rate)");
    mediumRadioButton = new QRadioButton("Medium (Moderate spawn rate)");
    hardRadioButton = new QRadioButton("Hard (Fast spawn rate)");

    playGame = new QPushButton("Play!");
    back = new QPushButton("Back");
    topicGroupBox = new QGroupBox();
    topicVBoxLayout = new QVBoxLayout();

    diffGroupBox = new QGroupBox();
    diffVBoxLayout = new QVBoxLayout();

    internalGridLayout = new QGridLayout();
    mainLayout = new QVBoxLayout();

}

void game2menu::setInternalLayout(){
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

void game2menu::setMainLayout(){
    mainLayout->addItem(internalGridLayout);
    mainLayout->addWidget(playGame);
    mainLayout->addWidget(back);
    setLayout(mainLayout);
}

void game2menu::returnToMenu() {
    this->close();
    new gameMenu(loggedInUser);

}

void game2menu::playGameSlot() {
    bool go = checkParameters();
    if (go){
    this->close();
    new game2scene(loggedInUser,bg,diff);
    }

}

void game2menu::keyPressEvent(QKeyEvent* event){
    if (event->key() == Qt::Key_F1){
        bool go = checkParameters();
        if (go){
            this->close();
            new game2scene(loggedInUser);
        }
    }
}

bool game2menu::checkParameters(){
    if (topic1RadioButton->isChecked()||topic2RadioButton->isChecked()||topic3RadioButton->isChecked()){}
    else {
        QMessageBox::critical(this,"Error","Please choose a background");
        return false;
    }
    if(easyRadioButton->isChecked()||mediumRadioButton->isChecked()||hardRadioButton->isChecked()){}
    else {
        QMessageBox::critical(this,"Error","Please choose a difficulty");
        return false;
    }
    if (topic1RadioButton->isChecked())
            bg = 0;
    if (topic2RadioButton->isChecked())
            bg = 1;
    if (topic3RadioButton->isChecked())
            bg = 2;

    if (easyRadioButton->isChecked())
            diff = "easy";
    if (mediumRadioButton->isChecked())
            diff = "medium";
    if (hardRadioButton->isChecked())
            diff = "hard";
    return true;
}
