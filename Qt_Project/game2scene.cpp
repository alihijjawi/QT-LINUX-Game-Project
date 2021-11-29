#include "game2scene.h"
#include "collectable.h"
#include <QApplication>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "gameMenu.h"

/**
* \file game2scene.cpp
* \brief the graphics scene for the shooting cars
* game
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
int game2scene::winningScore = 0;

int game2scene::totalLives = 0;

game2scene::game2scene(QJsonValue user,int bg, QString diff, QGraphicsScene *parent) :
    QGraphicsScene(parent)
{
    getGameRules();

    Cbg = bg;
    Cdiff = diff;

    initialize();

    collectable::missedDiscs=0;
    collectable::gameOver=false;
    view = new QGraphicsView(this);
    view->setWindowTitle("game2");
    view->setFixedSize(1005, 670);

    playlist = new QMediaPlaylist();




    if (Cbg==0) {
        view->setBackgroundBrush((QImage(":/Game2Files/game2background1.jpeg")).scaled(1005,670));
        playlist->addMedia(QUrl("qrc:/Game2Files/Music/HELL.mpeg"));
    }
    if (Cbg==1) {
        view->setBackgroundBrush((QImage(":/Game2Files/game2background2.jpeg")).scaled(1005,670));
        playlist->addMedia(QUrl("qrc:/Game2Files/Music/DESERT.mpeg"));
    }
    if (Cbg==2) {
        view->setBackgroundBrush((QImage(":/Game2Files/game2background3.jpeg")).scaled(1005,670));
        playlist->addMedia(QUrl("qrc:/Game2Files/Music/CITY.mpeg"));
    }
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    music.setPlaylist(playlist);
    music.setVolume(20);
    music.play();


    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    this->setSceneRect(0, 0, 1000, 670);
    view->adjustSize();
    view->move(QApplication::desktop()->screen()->rect().center() - view->rect().center());
    view->show();

    loggedInUser = user;
    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    if (Cdiff == "easy")
        timer->start(1500);
    if (Cdiff == "medium")
        timer->start(1000);
    if (Cdiff == "hard")
        timer->start(500);


    timerScore= new QTimer(this);
    connect(timerScore, SIGNAL(timeout()), this, SLOT(updateScore()));
    timerScore->start(200);


}
void game2scene::initialize() {
    hits = 0;
    leftHits = 0;
    middleHits = 0;
    rightHits = 0;
    getGlobalHighscore();

    mute = new QPushButton("");
    QGraphicsProxyWidget *proxy = this->addWidget(mute);
    mute->setGeometry(960,5,40,40);
    QBrush tb(Qt::transparent);
    mute->setFlat(true);
    mute->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    QObject::connect(mute, SIGNAL(clicked(bool)), this, SLOT(muteSlot()));

    muted = false;

    QFont arielFont("Ariel",16);
    QFont arielFont2("Ariel",14);
    arielFont.setBold(true);
    arielFont2.setBold(true);
    hitsDisplay = new QGraphicsSimpleTextItem("Total Score\n      0");
    livesDisplay = new QGraphicsSimpleTextItem("Lives Left\n       "+QString::number(totalLives));
    highScoreDisplay = new QGraphicsSimpleTextItem("High Score ("+highscoreUser+")\n       "+QString::number(highscore));
    leftHitsDisplay = new QGraphicsSimpleTextItem("Black Cars Hit: 0\n    0 points");
    midHitsDisplay = new QGraphicsSimpleTextItem("White Cars Hit: 0\n    0 points");
    rightHitsDisplay = new QGraphicsSimpleTextItem("Red Cars Hit: 0\n    0 points");

    addItem(hitsDisplay);
    addItem(livesDisplay);
    addItem(highScoreDisplay);
    addItem(leftHitsDisplay);
    addItem(midHitsDisplay);
    addItem(rightHitsDisplay);

    hitsDisplay->setPos(360,10);
    livesDisplay->setPos(360,70);
    highScoreDisplay->setPos(550,40);
    leftHitsDisplay->setPos(70,10);
    midHitsDisplay->setPos(70,60);
    rightHitsDisplay->setPos(70,110);

    hitsDisplay->setPen(QPen(QColor(Qt::white)));
    livesDisplay->setPen(QPen(QColor(Qt::white)));
    highScoreDisplay->setPen(QPen(QColor(Qt::white)));
    leftHitsDisplay->setPen(QPen(QColor(Qt::white)));
    midHitsDisplay->setPen(QPen(QColor(Qt::white)));
    rightHitsDisplay->setPen(QPen(QColor(Qt::white)));

    hitsDisplay->setFont(arielFont);
    livesDisplay->setFont(arielFont);
    highScoreDisplay->setFont(arielFont);
    leftHitsDisplay->setFont(arielFont2);
    midHitsDisplay->setFont(arielFont2);
    rightHitsDisplay->setFont(arielFont2);



    disc1 = new QGraphicsPixmapItem();
    disc1->setPixmap(QPixmap(":/Game2Files/collector.png").scaled(100,100));
    addItem(disc1);
    disc1->setPos(250,450);

    disc2 = new QGraphicsPixmapItem();
    disc2->setPixmap(QPixmap(":/Game2Files/collector.png").scaled(100,100));
    addItem(disc2);
    disc2->setPos(445,450);

    disc3 = new QGraphicsPixmapItem();
    disc3->setPixmap(QPixmap(":/Game2Files/collector.png").scaled(100,100));
    addItem(disc3);
    disc3->setPos(650,450);


}
void game2scene::update() {
    int carPos = QRandomGenerator::global()->bounded(1,4);
    collectable *col;
    if (hits < 30)
        col = new collectable(carPos,1);
    else if (hits < 60)
        col = new collectable(carPos,2);
    else if (hits < 90)
        col = new collectable(carPos,3);
    else if (hits < 120)
        col = new collectable(carPos,4);
    //else
        //col = new collectable(carPos,5);
    /*
     *This is 16x speed but its unplayable
     *To play on 16x uncomment this else statement
     *and comment the below else statement
    */
    else
       col = new collectable(carPos,4);

    addItem(col);
    col->setPos(497, 165);
}

void game2scene::keyPressEvent(QKeyEvent* event) {

    if (event->key() == Qt::Key_Left) {
        QList<QGraphicsItem *> listCollisionsDiscLeft = collidingItems(disc1);
        collectable * carLeft;
        if (!listCollisionsDiscLeft.isEmpty())
            carLeft= dynamic_cast<collectable *>(listCollisionsDiscLeft.at(0));
        if (listCollisionsDiscLeft.empty()) {
            if (collectable::missedDiscs!=totalLives)
                collectable::missedDiscs++;
            return;
        }
        else {
            hits+=3;
            leftHits+=1;
            removeItem(listCollisionsDiscLeft.at(0));
            carLeft->hit = true;
            carLeft->player2.play();
            return;
        }
    }
    if (event->key() == Qt::Key_Down) {

        QList<QGraphicsItem *> listCollisionsDiscMiddle = collidingItems(disc2);
        collectable * carMid;
        if (!listCollisionsDiscMiddle.isEmpty())
            carMid= dynamic_cast<collectable *>(listCollisionsDiscMiddle.at(0));
        if (listCollisionsDiscMiddle.empty()) {
            if (collectable::missedDiscs!=totalLives)
                collectable::missedDiscs++;
            return;
        }
        else {
            hits+=5;
            middleHits+=1;
            removeItem(listCollisionsDiscMiddle.at(0));
            carMid->hit = true;
            carMid->player2.play();
            return;
        }

    }
    if (event->key() == Qt::Key_Right) {
        QList<QGraphicsItem *> listCollisionsDiscRight = collidingItems(disc3);
        collectable * carRight;
        if (!listCollisionsDiscRight.isEmpty())
            carRight= dynamic_cast<collectable *>(listCollisionsDiscRight.at(0));
        if (listCollisionsDiscRight.empty()) {
            if (collectable::missedDiscs!=totalLives)
                collectable::missedDiscs++;
            return;
        }
        else {
            hits+=7;
            rightHits+=1;
            removeItem(listCollisionsDiscRight.at(0));
            //delete listCollisionsDiscRight.at(0);
            carRight->hit = true;
            carRight->player2.play();
            return;
        }
    }
}


void game2scene::updateScore() {
    hitsDisplay->setText("Total Score\n      "+QString::number(hits));
    leftHitsDisplay->setText("Black Cars Hit: "+QString::number(leftHits)+"\n    "+QString::number(leftHits*3)+" points");
    midHitsDisplay->setText("White Cars Hit: "+QString::number(middleHits)+"\n    "+QString::number(middleHits*5)+" points");
    rightHitsDisplay->setText("Red Cars Hit: "+QString::number(rightHits)+"\n    "+QString::number(rightHits*7)+" points");
    if (collectable::missedDiscs<totalLives)
        livesDisplay->setText("Lives Left\n       "+QString::number(totalLives-collectable::missedDiscs));
    else
        livesDisplay->setText("Lives Left\n       "+QString::number(0));

    if (collectable::missedDiscs >= totalLives) {
        collectable::missedDiscs = -1;
        timer->stop();
        timerScore->stop();
        QString hitsStr = QString::number(hits);
        msgBox.setWindowTitle("Game Over!");
        msgBox.setFixedSize(500,200);
        if (hits >winningScore){
            msgBox.setText("Game Over! No more lives! You won!");
            msgBox.setInformativeText("You got a score of: "+hitsStr+"\nWith a bonus of: "+QString::number(hits-winningScore)+"\nDo you want to play again?");
       }
        else{
            msgBox.setText("Game Over! No more lives! You lost!");
            msgBox.setInformativeText("You got a score of: "+hitsStr+"\nDo you want to play again?");
        }
        msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        int ret = msgBox.exec();
        music.stop();
        playlist->clear();
        delete playlist;
        if (loggedInUser!=QJsonValue::Null)
          saveScore();
        collectable::gameOver = true;
        switch (ret) {
        case QMessageBox::Yes:
            this->view->hide();
            delete hitsDisplay;
            delete livesDisplay;
            delete highScoreDisplay;
            delete disc1;
            delete disc2;
            delete disc3;
            delete timer;
            delete timerScore;
            this->view->close();
            new game2menu(loggedInUser);
            delete this->view;
            break;
        case QMessageBox::No:
            this->view->hide();
            delete hitsDisplay;
            delete livesDisplay;
            delete highScoreDisplay;
            delete disc1;
            delete disc2;
            delete disc3;
            delete timer;
            delete timerScore;
            this->view->close();
            new gameMenu(loggedInUser);
            delete this->view;
            break;
        }
    }

}

void game2scene::saveScore() {

    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.resize(0);
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    int i = 0;
    QJsonObject currUser;
    foreach (const QJsonValue &v, accountsArray) {
        i = i + 1;
        if (v.toObject().value("A-username") == loggedInUser.toObject().value("A-username").toString()) {
            currUser = v.toObject();
            accountsArray.removeAt(i-1);
            break;
        }
    }
    QJsonArray oldScores = currUser.value("J-Scores").toArray();
    QString aa;
    if (hits <=winningScore)
        aa = QString::number(hits)+"-0";

    else
        aa = QString::number(winningScore)+"-"+QString::number(hits-winningScore);
    oldScores.push_back(aa);
    currUser.remove("J-Scores");
    currUser.insert("J-Scores",QJsonValue(oldScores));
    accountsArray.push_back(currUser);

    QJsonObject final_object;
    final_object.insert(QString("accounts"), QJsonValue(accountsArray));
    QJsonDocument updatedDoc;
    updatedDoc.setObject(final_object);
    QByteArray dataPlayer = updatedDoc.toJson();
    file.write(dataPlayer);
    file.close();

}
void game2scene::getGlobalHighscore() {
    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    QJsonObject currUser;
    if (!accountsArray.isEmpty()) {
    QJsonArray scores = accountsArray.at(0).toObject().value("J-Scores").toArray();
    QStringList splitScore;
    if (!scores.isEmpty()) {
        splitScore = scores.at(0).toString().split("-");
        highscore = splitScore[0].toInt() + splitScore[1].toInt();
        highscoreUser = accountsArray.at(0).toObject().value("A-username").toString();
        for (const auto &el:scores) {
           splitScore = el.toString().split("-");
           int currScore = splitScore[0].toInt() + splitScore[1].toInt();
           if (currScore > highscore){
               highscore = currScore;

           }
        }
    }
    else
    {
        highscore = -1;
        highscoreUser = "No Highscore Yet";
    }
    foreach (const QJsonValue &v, accountsArray) {
        QString currUser = v.toObject().value("A-username").toString();
        scores = v.toObject().value("J-Scores").toArray();
        if (!scores.isEmpty())
        {
            splitScore = scores.at(0).toString().split("-");
            int maxUserScore = splitScore[0].toInt() + splitScore[1].toInt();
            for (const auto &el:scores) {
               splitScore = el.toString().split("-");
               int currScore = splitScore[0].toInt() + splitScore[1].toInt();
               if (currScore > maxUserScore){
                   maxUserScore = currScore;
               }
            }
            if(maxUserScore>highscore) {
                highscore = maxUserScore;
                highscoreUser = currUser;
                }
            }
        }

    }
    else
    {
        highscore = -1;
        highscoreUser = "No Highscore Yet";
    }
    file.close();
}

void game2scene::muteSlot(){
    if (muted) {
        music.setVolume(20);
        muted = false;
    }
    else {
        music.setVolume(0);
        muted = true;
    }
}

void game2scene::getGameRules() {

    QFile file(":/Game2Files/game2rules.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("rules");
    QJsonArray rules = value.toArray();
    QString a = rules.at(0).toObject().value("A-winningScore").toString();
    QString b = rules.at(0).toObject().value("B-totalLives").toString();
    winningScore = a.toInt();
    totalLives = b.toInt();
    file.close();
}
