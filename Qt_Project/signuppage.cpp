#include "signuppage.h"
#include "mainWidget.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QDir>
#include <QDebug>
#include <QException>

/**
* \file signuppage.cpp
* \brief opens the sign up page for the user to add their credentials and info
*
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
signUpPage::signUpPage(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    userNameLabelSU = new QLabel("Username");
    pwdLabelSU = new QLabel("Password");
    pwdLabelConfirmSU = new QLabel("Confirm Password");
    firstNameSU = new QLabel("First Name");
    lastNameSU = new QLabel("Last Name");
    DOBSU = new QLabel("Date of Birth (mm/dd/yyyy)");
    genderLabelSU = new QLabel("Gender");
    PhoneNumSU= new QLabel("Phone Number (eg. +961-71123456)");


    userNameLineEditSU = new QLineEdit;
    pwdLineEditSU = new QLineEdit;
    pwdLineEditSU->setEchoMode(QLineEdit::Password);
    pwdLineEditConfirmSU = new QLineEdit;
    pwdLineEditConfirmSU->setEchoMode(QLineEdit::Password);
    firstNameLineEditSU = new QLineEdit;
    lastNameLineEditSU = new QLineEdit;
    DOBLineEditSU = new QLineEdit;
    DOBLineEditSU->setMaxLength(10);
    maleRadioButtonSU = new QRadioButton("Male");
    femaleRadioButtonSU = new QRadioButton("Female");
    PhoneNumLineEditSU = new QLineEdit;

    profilePicButtonSU = new QPushButton("Upload Picture");
    SignUpButtonSU = new QPushButton("Sign up");
    BackButtonSU = new QPushButton("Return to Main Menu");

    genderGroupBox = new QGroupBox;
    genderVBoxLayout = new QVBoxLayout;
    mainVBoxLayout = new QVBoxLayout;
    internalGridLayout = new QGridLayout;

    QObject::connect(profilePicButtonSU, SIGNAL(clicked(bool)), this, SLOT(uploadPic()));
    QObject::connect(SignUpButtonSU, SIGNAL(clicked(bool)), this, SLOT(signUp()));
    QObject::connect(BackButtonSU, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));

    this->setFixedSize(600,450);

    styleAll();

    setInternalLayout();
    setMainLayout();

    QPixmap bkgnd(":/Game1Files/signUp.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);

    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Sign Up");
    show();




}

void signUpPage::setInternalLayout(){
    internalGridLayout->addWidget(userNameLabelSU,0,0);
    internalGridLayout->addWidget(userNameLineEditSU,0,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 1, 0);
    internalGridLayout->addWidget(pwdLabelSU,2,0);
    internalGridLayout->addWidget(pwdLineEditSU,2,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 3, 0);
    internalGridLayout->addWidget(pwdLabelConfirmSU,4,0);
    internalGridLayout->addWidget(pwdLineEditConfirmSU,4,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 5, 0);
    internalGridLayout->addWidget(firstNameSU,6,0);
    internalGridLayout->addWidget(firstNameLineEditSU,6,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 7, 0);
    internalGridLayout->addWidget(lastNameSU,8,0);
    internalGridLayout->addWidget(lastNameLineEditSU,8,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 9, 0);
    internalGridLayout->addWidget(DOBSU,10,0);
    internalGridLayout->addWidget(DOBLineEditSU,10,1);
    genderVBoxLayout->addWidget(maleRadioButtonSU);
    genderVBoxLayout->addWidget(femaleRadioButtonSU);
    genderGroupBox->setLayout(genderVBoxLayout);
    internalGridLayout->addItem(new QSpacerItem(0,10), 11, 0);
    internalGridLayout->addWidget(genderLabelSU,12,0);
    internalGridLayout->addWidget(genderGroupBox,12,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 13, 0);
    internalGridLayout->addWidget(PhoneNumSU,14,0);
    internalGridLayout->addWidget(PhoneNumLineEditSU,14,1);
    internalGridLayout->addItem(new QSpacerItem(0,10), 15, 0);
    internalGridLayout->addWidget(profilePicButtonSU,16,0);
    internalGridLayout ->addItem(new QSpacerItem(50,10), 0, 0);

}

void signUpPage::setMainLayout(){
    mainVBoxLayout->addItem(internalGridLayout);
    mainVBoxLayout->addWidget(SignUpButtonSU);
    mainVBoxLayout->addWidget(BackButtonSU);
    setLayout(mainVBoxLayout);
}


void signUpPage::returnToMenu() {
    this->close();
    new mainWidget();
}

void signUpPage::uploadPic(){
    QString filter = "Image Files (*.png *.jpeg *.jpg)";
    filePath = QFileDialog::getOpenFileName(this,"Profile Picture",QDir::homePath(),filter);
    fileName = filePath.split("/").last();
    profilePicButtonSU->setText("Upload Picture ("+fileName+")");

}


void signUpPage::signUp() {
    if(!checkEmpty()){
        return;
    }

    if(!checkUsername()) {
        return;
    }

    if (pwdLineEditSU->text()!=(pwdLineEditConfirmSU->text())) {
        QMessageBox::critical(this,"Error","Passwords Do Not Match");
        return;
    }

    if(!(pwdCheck(pwdLineEditConfirmSU->text())))
        return;


    if(!(dateCheck(DOBLineEditSU->text())))
        return;


    if(checkGender()=="error")
        return;
    QString inputGender = checkGender();

    if(!(phoneNumCheck(PhoneNumLineEditSU->text())))
        return;



    QFile file("/home/eece435l/HassanAliData/accounts.json");

    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.resize(0);
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();


    QJsonArray scores = {};

    QJsonObject data = QJsonObject(
    {
        qMakePair(QString("A-username"), QJsonValue(userNameLineEditSU->text())),
        qMakePair(QString("B-password"), QJsonValue(pwdLineEditSU->text())),
        qMakePair(QString("C-firstName"), QJsonValue(firstNameLineEditSU->text())),
        qMakePair(QString("D-lastName"), QJsonValue(lastNameLineEditSU->text())),
        qMakePair(QString("E-DoB"), QJsonValue(DOBLineEditSU->text())),
        qMakePair(QString("F-Gender"), QJsonValue(inputGender)),
        qMakePair(QString("G-PhoneNum"), QJsonValue(PhoneNumLineEditSU->text())),
        qMakePair(QString("H-Country"), QJsonValue(country)),
        qMakePair(QString("I-Scores"),scores),
        qMakePair(QString("J-Scores"),scores)
    });


    accountsArray.push_back(QJsonValue(data));

    QJsonObject final_object;

    final_object.insert(QString("accounts"), QJsonValue(accountsArray));


    QJsonDocument updatedDoc;
    updatedDoc.setObject(final_object);
    QByteArray dataPlayer = updatedDoc.toJson();
    file.write(dataPlayer);
    file.close();

    QString path = "/home/eece435l/HassanAliData/ProfilePics/";
    path = path + userNameLineEditSU->text();
    QFile::copy(filePath,path);


    hide();
    new mainWidget();

    QMessageBox::information(this,"Succes","Sign up successful, please try logging in!");



}


bool signUpPage::checkEmpty(){
    if (userNameLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your username");
        return false;
    }
    if (pwdLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your password");
        return false;
    }
    if (pwdLineEditConfirmSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please confirm your password");
        return false;
    }
    if (firstNameLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your First Name");
        return false;
    }
    if (lastNameLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your Last Name");
        return false;
    }
    if (DOBLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your Date of Birth");
        return false;
    }
    if (!(maleRadioButtonSU->isChecked()) && !(femaleRadioButtonSU->isChecked())){
        QMessageBox::critical(this,"Error","Please fill in your Gender");
        return false;
    }
    if (PhoneNumLineEditSU->text() ==  nullptr) {
        QMessageBox::critical(this,"Error","Please fill in your Phone Number");
        return false;
    }

    if (filePath == nullptr) {
        QMessageBox::critical(this,"Error","Please upload a profile picture");
        return false;
    }
    return true;
}
bool signUpPage::pwdCheck(QString pwd) {
    if (pwd.length() < 8) {
        QMessageBox::critical(this,"Error","Password is Too Short!");
        return false;
    }


    bool major = false;
    bool minor = false;
    bool number = false;

    for (int i=0; i < pwd.length(); i++) {
        if ((pwd.at(i) <= 90)  && (pwd.at(i) >= 64 )) {
            major = true;
        }
        if ((pwd.at(i) <= 122) && (pwd.at(i) >= 97 )) {
            minor = true;
        }
        if ((pwd.at(i) <= 57) && (pwd.at(i) >= 48 )) {
            number = true;
        }
    }
    if (!major || !minor || !number) {
        QMessageBox::critical(this,"Error","Password must contain atleast one Number, Uppercase letter, and Lowercase Letter !");
        return false;
    }

    return true;
}

bool signUpPage::dateCheck(QString date) {
    if (date.length() >10) {
        QMessageBox::critical(this,"Error","Date Format is Incorrect");
        return false;
    }
    if (date[2] != "/" || date[5] != "/") {
        QMessageBox::critical(this,"Error","Date Format is Incorrect");
        return false;
    }

      bool good = false;
      QString m = date.split("/")[0];
      QString d = date.split("/")[1];
      QString y = date.split("/")[2];

      if (m.toInt() <= 12 && m.toInt() >= 1 && d.toInt() <= 31 && d.toInt() >= 1 && y.toInt() <= 2017 && y.toInt() >= 1920) {
                    good = true;
              }
       if (!good) {
           QMessageBox::critical(this,"Error","Date Format is Incorrect");
           return false;
    }


    return true;
}

bool signUpPage::phoneNumCheck(QString phoneNum) {

    if (!(phoneNum.at(0) == "+")) {
        QMessageBox::critical(this,"Error","Phone Number Format is Incorrect");
        return false;
    }
    if (!(phoneNum.contains("-"))) {
        QMessageBox::critical(this,"Error","Phone Number Format is Incorrect");
        return false;
    }
    QString countryCode = phoneNum.split("-")[0];
    QString number = phoneNum.split("-")[1];
    if (countryCode.length()>4 || countryCode.length() < 2) {
        QMessageBox::critical(this,"Error","Phone Number Format is Incorrect");
        return false;
    }
    QString countryCodeNum = countryCode.split("+")[1];
    if (countryCodeNum == "961")
        country = "Lebanon";
    if (countryCodeNum == "43")
        country = "Austria";
    if (countryCodeNum == "963")
        country = "Syria";
    if (countryCodeNum == "81")
        country = "Japan";
    if (countryCodeNum == "7")
        country = "Russia";
    if (countryCodeNum == "672")
        country = "Antarctica";
    return true;
}

QString signUpPage::checkGender() {
    QString inputGender = "";
    if (maleRadioButtonSU->isChecked()) {
        inputGender = "male";
        return inputGender;
    }
    if (femaleRadioButtonSU->isChecked()) {
        inputGender = "female";
        return inputGender;
    }
    return "";
}

bool signUpPage::checkUsername() {
    QString currUsername = userNameLineEditSU->text();
    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    foreach (const QJsonValue &v, accountsArray) {
        if (v.toObject().value("A-username") == currUsername) {
            QMessageBox::critical(this,"Error","Username already exists!");
            return false;
        }
    }
    return true;
}

void signUpPage::styling(QLineEdit *txt) {
    txt->setProperty("mandatoryField", true);
    txt->setStyleSheet(
                "QLineEdit{"
                "background-color: rgb(200,200,200);"
                "border: 2px solid gray;"
                "border-radius: 10px;"
                "padding: 0 8px;"
                "selection-background-color: darkgray;"
                "font-size: 15px;}"
                "QLineEdit:focus{background-color: rgb(190,190,190);}");
}

void signUpPage::labelStyle(QLabel *lbl) {
    lbl->setStyleSheet("font: 15px;");
}

void signUpPage::styleAll() {
    styling(userNameLineEditSU);
    labelStyle(userNameLabelSU);
    styling(pwdLineEditSU);
    labelStyle(pwdLabelSU);
    styling(pwdLineEditConfirmSU);
    labelStyle(pwdLabelConfirmSU);
    styling(firstNameLineEditSU);
    labelStyle(firstNameSU);
    styling(lastNameLineEditSU);
    labelStyle(lastNameSU);
    labelStyle(genderLabelSU);
    styling(DOBLineEditSU);
    labelStyle(DOBSU);
    styling(PhoneNumLineEditSU);
    labelStyle(PhoneNumSU);
}
