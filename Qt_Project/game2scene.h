#ifndef GAME2SCENE_H
#define GAME2SCENE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>

/**
 * \file game2scene.h
 * \brief Game 2 Scene Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class game2scene: public QGraphicsScene
{
    Q_OBJECT
public:
    explicit game2scene(QJsonValue user = QJsonValue::Null,int bg=0, QString diff="easy", QGraphicsScene *parent= 0) ;
    int Cbg;
    QString Cdiff;
    QGraphicsView *view;
    QJsonValue loggedInUser;
    QTimer *timer;
    QTimer *timerScore;
    static int winningScore;
    static int totalLives;
    int hits;
    int leftHits;
    int middleHits;
    int rightHits;
    QGraphicsPixmapItem *disc1;
    QGraphicsPixmapItem *disc2;
    QGraphicsPixmapItem *disc3;
    QMessageBox msgBox;
    QGraphicsSimpleTextItem *hitsDisplay;
    QGraphicsSimpleTextItem *livesDisplay;
    QGraphicsSimpleTextItem *highScoreDisplay;
    QGraphicsSimpleTextItem *leftHitsDisplay;
    QGraphicsSimpleTextItem *midHitsDisplay;
    QGraphicsSimpleTextItem *rightHitsDisplay;
    QString highscoreUser;
    int highscore;
    QMediaPlayer music;
    QPushButton *mute;
    bool muted;
    QMediaPlaylist *playlist;
    /**
    * \brief initializes all the member attributes of the class
    */
    void initialize();

    /**
    * \brief key listener for the left, down, and right arrow key buttons
    */
    void keyPressEvent(QKeyEvent* event);


    /**
    * \brief gets the global highscore across all registered users
    */
    void getGlobalHighscore();


    /**
    * \brief gets the winning score and total lives for the game from the json file
    */
    void getGameRules();

signals:

public slots:
    /**
    * \brief randomly generates cars at different at different speeds and spawn rates
    */
    void update();

    /**
    * \brief updates the score of the current player and checks when the game is over
    */
    void updateScore();


    /**
    * \brief saves the score of the logged in user in the json file
    */
    void saveScore();

    /**
    * \brief mutes all sounds in the game
    */
    void muteSlot();

};


#endif // GAME2SCENE_H
