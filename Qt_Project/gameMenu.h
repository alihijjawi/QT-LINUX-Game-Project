#ifndef GAMEMENU_H
#define GAMEMENU_H
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include "game2menu.h"
/**
 * \file gameMenu.h
 * \brief Game Menu Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class gameMenu : public QWidget
{
    Q_OBJECT
public:
    explicit gameMenu(QJsonValue user = QJsonValue::Null,QWidget *parent = nullptr);
    QJsonValue loggedInUser;
    QString userName;
    QLabel * ppLabel;
    QLabel * cpLabel;
    QString country;
    bool guest;
private:
    QPushButton *playGame1;
    QPushButton *playGame2;
    QPushButton *signOut;
    QPushButton *checkPrevScores;

    QString pathC;

    QTextEdit *editText1;

    QVBoxLayout *mainVBoxLayout;
    QGridLayout *internalGridLayout;
    QGridLayout *internalGridLayout2;

    /**
    * \brief loads the flag of the country according to phone number code
    */
    void getCountryPic();

    /**
    * \brief loads the user profile picture
    */
    void getPic();

    /**
    * \brief sets the layout of each part of the GUI
    */
    void setInternalLayout();

    /**
    * \brief sets the layout of each part of the GUI
    */
    void setInternalLayout2();

    /**
    * \brief sets the layout of the main window
    */
    void setMainLayout();

signals:


public slots:
    /**
    * \brief returns to the sign in menu
    */
    void returnToMenu();

    /**
    * \brief takes the user to the Battleship game 1 pre-game menu
    */
    void playGame1slot();

    /**
    * \brief takes the user to the Shooting Discs game 2 pre-game menu
    */
    void playGame2slot();

    /**
    * \brief takes the user to a window with graphs displaying their previous scores for each game
    */
    void checkPreviousScores();
};

#endif // GAMEMENU_H
