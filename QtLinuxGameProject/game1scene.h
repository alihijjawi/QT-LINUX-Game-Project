#ifndef GAME1SCENE_H
#define GAME1SCENE_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>


class game1scene : public QWidget
{
    Q_OBJECT
public:
    explicit game1scene(QJsonValue user = QJsonValue::Null,QWidget *parent = nullptr);
    QJsonValue loggedInUser;


    int bigShipI;
    int smallShip1I;
    int smallShip1J;
    int smallShip2I;
    int smallShip2J;
    int mediumShip1I;
    int mediumShip1J;
    int mediumShip2I;
    int mediumShip2J;
    QString locBigShip1;
    QString locBigShip2;
    QString locBigShip3;
    QString locBigShip4;
    QString locMediumShip11;
    QString locMediumShip12;
    QString locMediumShip21;
    QString locMediumShip22;
    QString locSmallShip1;
    QString locSmallShip2;

    QLabel *smallShipPic1;
    QLabel *smallShipPic2;
    QLabel *mediumShipPic11;
    QLabel *mediumShipPic12;
    QLabel *mediumShipPic21;
    QLabel *mediumShipPic22;
    QLabel *largeShipPic1;
    QLabel *largeShipPic2;
    QLabel *largeShipPic3;
    QLabel *largeShipPic4;
    QLabel *targetPic;

    QLabel *countdown;

    QTimer *timerScore;

    QTime *time;
    QTimer *timerCountdown;

    bool gameOver = false;
    bool timeUp = false;

    int tries = 0;
    int hits = 0;
    int misses = 0;

private:
    void initialize();
    void addButtons();
    void styleButton(QPushButton *btn);
    void styleButtons();
    void randomizeShips();
    void shipPositions();

    void setShipPictures();


    void setInternalLayout();
    void setMainLayout();

    void saveScore();

    QString openQuestionDialog();
    void spawnVisual();

    QPushButton *a11,*a12,*a13,*a14,*a21,*a22,*a23,*a24,*a31,*a32,*a33,*a34,*a41,*a42,*a43,*a44;

    QList<QPushButton*> *listButtons;

    QPushButton *leaveBtn;

    QGridLayout *internalGridLayout;
signals:


public slots:
    void clickButton();
    void checkScore();
    void returnToMenu();
    void updateCountdown();

};

#endif // GAME1SCENE_H
