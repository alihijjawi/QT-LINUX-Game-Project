#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H
#include <QObject>
#include <QtWidgets>
#include <QWidget>

/**
 * \file signuppage.h
 * \brief SIgn Up Page Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class signUpPage : public QWidget
{
    Q_OBJECT
public:
    explicit signUpPage(QWidget *parent = nullptr);
private:
    QLabel *userNameLabelSU;
    QLabel *pwdLabelSU;
    QLabel *pwdLabelConfirmSU;
    QLabel *firstNameSU;
    QLabel *lastNameSU;
    QLabel *DOBSU;
    QLabel *genderLabelSU;
    QLabel *PhoneNumSU;
    QString country;



    QLineEdit *userNameLineEditSU;
    QLineEdit *pwdLineEditSU;
    QLineEdit *pwdLineEditConfirmSU;
    QLineEdit *firstNameLineEditSU;
    QLineEdit *lastNameLineEditSU;
    QLineEdit *DOBLineEditSU;
    QRadioButton *maleRadioButtonSU;
    QRadioButton *femaleRadioButtonSU;
    QLineEdit *PhoneNumLineEditSU;
    QString filePath;
    QString fileName;

    QPushButton *profilePicButtonSU;
    QPushButton *SignUpButtonSU;
    QPushButton *BackButtonSU;


    QGroupBox *genderGroupBox;
    QVBoxLayout *genderVBoxLayout;
    QVBoxLayout *mainVBoxLayout;
    QGridLayout *internalGridLayout;

    /**
    * \brief sets the layout for the GUI items
    */
    void setInternalLayout();

    /**
    * \brief sets the layout of the main window
    */
    void setMainLayout();

    /**
    * \brief styles the line edit
    * \param a QLineEdit that will be styled
    */
    void styling(QLineEdit *txt);

    /**
    * \brief styles the text labels
    * \param a QLabel that will be styled
    */
    void labelStyle(QLabel *lbl);

    /**
    * \brief iterates over the widgets and items, styles them according to their types using labelStyle and styling funtions
    */
    void styleAll();

    /**
    * \brief checks if the string password matches the password requirements
    * \param a QString which is the user password to be checked
    */
    bool pwdCheck(QString pwd);

    /**
    * \brief checks if the date is in the correct format mm/dd/yyyy
    * \param a QString representing the input date
    */
    bool dateCheck(QString date);

    /**
    * \brief checks if the phone number is in the correct format +XXX-XXXXXX
    * \param a QString representing the input phone number
    */
    bool phoneNumCheck(QString phoneNum);

    /**
    * \brief checks if any of the sign up text boxes/parameters are empty
    */
    bool checkEmpty();

    /**
    * \brief checks if the chosen username already exists in the JSON file
    */
    bool checkUsername();

    /**
    * \brief checks the selected gender of the user
    *
    * \return returns a QString representing the selected gender
    */
    QString checkGender();

signals:

public slots:

    /**
    * \brief opens a file dialogue so the user uploads their profile picture from their local files
    */
    void uploadPic();

    /**
    * \brief returns back to the sign in menu
    */
    void returnToMenu();

    /**
    * \brief stores all the credential and info of the signed up user in the JSON file
    */
    void signUp();


};

#endif // SIGNUPPAGE_H
