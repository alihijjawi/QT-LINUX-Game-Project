#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QObject>
#include <QtWidgets>
#include <QWidget>

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

    void setInternalLayout();
    void setMainLayout();
    void styling(QLineEdit *txt);
    void labelStyle(QLabel *lbl);
    void styleAll();
    bool pwdCheck(QString pwd);
    bool dateCheck(QString date);
    bool phoneNumCheck(QString phoneNum);
    bool checkEmpty();
    bool checkUsername();
    QString checkGender();

signals:

public slots:
    void uploadPic();
    void returnToMenu();
    void signUp();


};

#endif // SIGNUPPAGE_H
