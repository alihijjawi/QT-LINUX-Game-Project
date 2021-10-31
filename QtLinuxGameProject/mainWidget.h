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
    explicit mainWidget(QWidget *parent = nullptr); //!<Contructor for mainWidget


private:
    QLabel *userNameLabel; //!<Visual Label for Username field
    QLabel *pwdLabel; //!<Visual Label for Password field
    QLineEdit *userNameLineEdit; //!<Visual text box for Username field
    QLineEdit *pwdLineEdit; //!<Visual text box for Password field

    QPushButton *SignInButton; //!<Visual button for signing in
    QPushButton *SignUpButton; //!<Visual button for signing up
    QPushButton *GuestButton; //!<Visual button for signing in as guest

    QVBoxLayout *mainVBoxLayout; //!<Declaration of the main layout
    QGridLayout *internalGridLayout; //!<Declaration of the internal layout

    QJsonValue user; //!<Declaration of the Json Value that the signed in user will be stored in

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
