#include "collectable.h"
#include <QTimer>
#include<QDebug>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QThread>

/**
* \file collectable.cpp
* \brief the implementation of the logic behind
* moving and spawning the cars in the game scene
* \author Ali Hijjawi
* \author Hassan El Khatib
*/

int collectable::missedDiscs = 0;

bool collectable::gameOver = false;

collectable::collectable(int pos, int spd, QObject *parent) :
    QObject(parent)
{
    //player = new QMediaPlayer;
    player.setMedia(QUrl("qrc:/Game2Files/Music/zoom.mpeg"));
    player.setVolume(50);

   // player2 = new QMediaPlayer;
    player2.setMedia(QUrl("qrc:/Game2Files/Music/TINGTING.mpeg"));
    player2.setVolume(7);

    zoomed = false;
    hit = false;

    position = pos;
    speed = spd;
    if (position == 1)
        setPixmap((QPixmap(":/Game2Files/leftCar.png")).scaled(100,100));
    else if (position == 2)
        setPixmap((QPixmap(":/Game2Files/midCar.png")).scaled(100,100));
    else if (position == 3)
        setPixmap((QPixmap(":/Game2Files/rightCar.png")).scaled(100,100));

    setScale(0.1);
    timer= new QTimer(this);

    if (position == 1)
        connect(timer, SIGNAL(timeout()), this, SLOT(updateLeft()));
    else if (position == 2)
        connect(timer, SIGNAL(timeout()), this, SLOT(updateMiddle()));
    else if (position == 3)
        connect(timer, SIGNAL(timeout()), this, SLOT(updateRight()));

    if (speed == 1)
        timer->start(100);
    else if (speed == 2)
        timer->start(50);
    else if (speed == 3)
        timer->start(25);
    else if (speed == 4)
        timer->start(13);
    else if (speed == 5)
        timer->start(7);

}

void collectable::updateLeft()
{
    if (gameOver)
        setPos(900,x());
    this->setScale(this->scale()+0.03);
    if (y()> 600 && !zoomed && !hit &&!gameOver)
        {
            zoomed = true;
            player.play();
            scene()->removeItem(this);

            if (collectable::missedDiscs!=-1||collectable::missedDiscs!=game2scene::totalLives)
                collectable::missedDiscs++;

        }
    else if (y()>800 && !(player.state() == QMediaPlayer::PlayingState)){
        delete timer;
        delete this;
        return;
    }

    setPos(x()-9, y() + 10);

}

void collectable::updateMiddle()
{
    if (gameOver)
        setPos(900,x());
    this->setScale(this->scale()+0.03);
    if (y()> 600 && !zoomed && !hit &&!gameOver)
        {
            zoomed = true;
            player.play();
            scene()->removeItem(this);

            if (collectable::missedDiscs!=-1||collectable::missedDiscs!=game2scene::totalLives)
                collectable::missedDiscs++;

        }
    else if (y()>800 && !(player.state() == QMediaPlayer::PlayingState)){
        delete timer;
        delete this;
        return;
    }
    setPos(x()-2, y() + 10);

}

void collectable::updateRight()
{
    if (gameOver)
        setPos(900,x());
    this->setScale(this->scale()+0.03);
    if (y()> 600 && !zoomed && !hit &&!gameOver)
        {
            zoomed = true;
            player.play();
            scene()->removeItem(this);

            if (collectable::missedDiscs!=-1||collectable::missedDiscs!=game2scene::totalLives)
                collectable::missedDiscs++;

        }
    else if (y()>800 && !(player.state() == QMediaPlayer::PlayingState)){
        delete timer;
        delete this;
        return;
    }
    setPos(x()+5, y() + 10);

}
