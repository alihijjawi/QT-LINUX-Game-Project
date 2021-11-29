#ifndef GAME1SCENE_H
#define GAME1SCENE_H
#include <QObject>
#include <QWidget>
#include <QtWidgets>

/**
 * \file game1scene.h
 * \brief Game 1 Scene Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class game1scene : public QWidget
{
    Q_OBJECT
public:
    explicit game1scene(QJsonValue user = QJsonValue::Null,QString topic="1", QString diff="easy",QWidget *parent = nullptr);
    QJsonValue loggedInUser;

    QString CTopic;
    QString CDiff;

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

    QLabel *ourSmallShip1;
    QLabel *ourSmallShip2;
    QLabel *ourMediumShip11;
    QLabel *ourMediumShip12;

    QLabel *countdown;
    QLabel *hitsD;
    QLabel *missesD;

    QTime time;
    QTimer *timerCountdown;

    bool gameOver = false;
    bool timeUp = false;

    bool noMoresShips = false;

    int tries = 0;
    int hits = 0;
    int misses = 0;
    int index=0;

private:
    /**
    * \brief initializes all the member attributes of the class
    */
    void initialize();

    /**
    * \brief adds the 16 grid buttons of the game
    */
    void addButtons();

    /**
    * \brief fixes the buttons that we used, display wise
    * \param the button pointer to which we want to style
    */
    void styleButton(QPushButton *btn);

    /**
    * \brief randomizes the coordinates of the ships that are spawned at the enemy's grid
    */
    void randomizeShips();

    /**
    * \brief assigning the ship to the buttons according to the random number coordinate they got
    */
    void shipPositions();

    /**
    * \brief extracts the questions and their answers from the JSON file
    */
    void getQuestions();

    /**
    * \brief puts the pictures of the ships in the right place, and hides them from the player
    */
    void setShipPictures();

    /**
    * \brief sets the layout of each part of the grid
    */
    void setInternalLayout();

    /**
    * \brief sets the layouts of the main grid through internal ones
    */
    void setMainLayout();

    /**
    * \brief updates our grid's ships to become hit ships
    */
    void getHit();

    /**
    * \brief updates the text labels in the middle of the screen after every hit trial
    */
    void updateScore();

    /**
    * \brief saves the scores into an array of scores in the JSON file in the part of the specific user
    */
    void saveScore();

    /**
    * \brief checks if all 16 tries are consumed, and shows a game over dialogue accordingly
    */
    void checkScore();

    /**
    * \brief opens a question dialogue with a question from the JSON files. prompts the user to answer out of different choices
    *
    * \return returns the answer chosen as QString
    */
    QString openQuestionDialog();

    /**
    * \brief checks the button we clicked, opens a question dialogue, and shows the corresponding picture when the player answers correctly or incorrectly
    * \param the button that was clicked
    */
    void clickButton(QPushButton * buttonSender);

    QPushButton *a11,*a12,*a13,*a14,*a21,*a22,*a23,*a24,*a31,*a32,*a33,*a34,*a41,*a42,*a43,*a44;
    QPushButton *leaveBtn;

    QList<QPushButton*> *listButtons;
    QList<QLabel*> *listTargets;
    QList<QLabel*> *listOurShips;
    QList<QList<QString>> *questions;
    QList<QList<bool>> buttonsPushed;
    QGridLayout *internalGridLayout;

signals:


public slots:

    /**
    * \brief asserts that no button is clicked twice
    */
    void mutexButton();


    /**
    * \brief goes back to menu into the game menu of the currently logged in user/guest
    */
    void returnToMenu();

    /**
    * \brief updates the countdown timer on the label, as well as ends the game when it finishes
    */
    void updateCountdown();

};

#endif // GAME1SCENE_H
