#ifndef COLLECTABLE_H
#define COLLECTABLE_H
#include "game2scene.h"
#include<QDebug>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
/**
 * \file collectable.h
 * \brief Collectable Class Decleration
 * This header file includes all fields and functions
 * for a car in the game scene including setting position
 * and speed
 */
class collectable : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit collectable(int pos, int spd, QObject *parent = 0);
    int position;
    int speed;
    static int missedDiscs;
    QTimer* timer;
    QMediaPlayer player;
    QMediaPlayer player2;
    bool zoomed;
    bool hit;
    static bool gameOver;
signals:

public slots:

    /**
    * \brief updates the position of the left car
    */
    void updateLeft();

    /**
    * \brief updates the position of the middle car
    */
    void updateMiddle();

    /**
    * \brief updates the position of the right car
    */
    void updateRight();
};

#endif // COLLECTABLE_H
