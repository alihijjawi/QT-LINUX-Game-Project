#ifndef GAME2MENU_H
#define GAME2MENU_H
#include <QObject>
#include <QtWidgets>
#include <QWidget>

/**
 * \file game2menu.h
 * \brief Game 2 Menu Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class game2menu : public QWidget
{
    Q_OBJECT
public:
    explicit game2menu(QJsonValue user = QJsonValue::Null,QWidget *parent = nullptr);

private:
    QJsonValue loggedInUser;

    int bg;
    QString diff;

    QPushButton *playGame;
    QPushButton *back;

    QLabel *topicLabel;
    QRadioButton *topic1RadioButton;
    QRadioButton *topic2RadioButton;
    QRadioButton *topic3RadioButton;

    QLabel *difficultyLabel;
    QRadioButton *easyRadioButton;
    QRadioButton *mediumRadioButton;
    QRadioButton *hardRadioButton;

    QGroupBox *topicGroupBox;
    QVBoxLayout *topicVBoxLayout;

    QGroupBox *diffGroupBox;
    QVBoxLayout *diffVBoxLayout;

    QGridLayout *internalGridLayout;
    QVBoxLayout *mainLayout;

    /**
    * \brief initializes the grid layout items of the GUI
    */
    void intialize();

    /**
    * \brief sets the items to create the GUI in layout positions
    */
    void setInternalLayout();

    /**
    * \brief adds the internal layouts to the main grid of the GUI
    */
    void setMainLayout();

    /**
    * \brief launches the game when F1 is pressed
    */
    void keyPressEvent(QKeyEvent* event);

    /**
    * \brief checks if all the inputs are selected
    * \return returns a boolean indicating if the topic and difficulty are selected
    */
    bool checkParameters();

private slots:
    /**
    * \brief connected to the button that returns the user back to the login main menu
    */
    void returnToMenu();

    /**
    * \brief connected to the button that moves us the the actual game
    */
    void playGameSlot();
};

#endif // GAME2MENU_H
