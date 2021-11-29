#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>


/**
 * \file mainWidget.h
 * \brief Main Widget Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = nullptr);
    //~mainWidget();

private:
    QLabel *userNameLabel;
    QLabel *pwdLabel;
    QLineEdit *userNameLineEdit;
    QLineEdit *pwdLineEdit;

    QPushButton *SignInButton;
    QPushButton *SignUpButton;
    QPushButton *GuestButton;

    QVBoxLayout *mainVBoxLayout;
    QGridLayout *internalGridLayout;

    QJsonValue user;

    /**
    * \brief Function that styles our text boxes
    * \param *txt first argument, pointer to the text box that we intend to style
    */
    void styling(QLineEdit *txt);
    /**
    * \brief Function that styles our text labels
    * \param *lbl first argument, pointer to the label that we intend to style
    */
    void labelStyle(QLabel *lbl);
    /**
    * \brief Function that styles our buttons
    * \param *btn first argument, pointer to the button that we intend to style
    */
    void buttonStyle(QPushButton *btn);
    /**
    * \brief Function that calls all the styling functions above
    */
    void styleAll();

    /**
    * \brief Function that adds items/widgets to the internal layout
    */
    void setInternalLayout();
    /**
    * \brief Function that adds items/widgets/layouts to the main layout
    */
    void setMainLayout();

signals:

public slots:
    /**
    * \brief Function that opens the Sign Up window, called when SignUp Button is pushed
    */
    void openSignUp();
    /**
    * \brief Function that opens the game window, called when Signin Button is pushed with correct credentials
    * \return boolean value true if sign in was succefull, and false otherwise
    */
    bool signIn();
    /**
    * \brief Function that opens the game window as a guest, called when GuestButton is pushed
    */
    void playAsGuest();
};

#endif // MAINWIDGET_H
