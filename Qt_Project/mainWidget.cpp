#include "mainWidget.h"
#include "signuppage.h"
#include "gameMenu.h"

/**
* \file mainWidget.cpp
* \brief contains mainWidget class definition
* \author Hassan El Khatib
* \author Ali Hijjawi
*/
mainWidget::mainWidget(QWidget *parent) : QWidget(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    userNameLabel = new QLabel("Username");
    pwdLabel = new QLabel("Password");
    userNameLineEdit = new QLineEdit;
    pwdLineEdit = new QLineEdit;
    pwdLineEdit->setEchoMode(QLineEdit::Password);




    SignInButton = new QPushButton("Sign in");
    SignUpButton = new QPushButton("Sign up");
    GuestButton = new QPushButton("Play As Guest");

    mainVBoxLayout = new QVBoxLayout;
    internalGridLayout = new QGridLayout;


    QObject::connect(SignUpButton, SIGNAL(clicked(bool)), this, SLOT(openSignUp()));
    QObject::connect(SignInButton, SIGNAL(clicked(bool)), this, SLOT(signIn()));
    QObject::connect(GuestButton, SIGNAL(clicked(bool)), this, SLOT(playAsGuest()));

    this->setFixedSize(600,450);

    styleAll();
    setInternalLayout();
    setMainLayout();
    QPixmap bkgnd(":/Game1Files/mainMenu.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Main Menu");
    show();

}

void mainWidget::setInternalLayout(){
    internalGridLayout->addWidget(userNameLabel,0,0);
    internalGridLayout->addWidget(userNameLineEdit,0,1);
    internalGridLayout ->addItem(new QSpacerItem(0,10), 1, 0);
    internalGridLayout->addWidget(pwdLabel,2,0);
    internalGridLayout->addWidget(pwdLineEdit,2,1);

}

void mainWidget::setMainLayout(){
    mainVBoxLayout->addItem(internalGridLayout);
    mainVBoxLayout->addWidget(SignInButton);
    mainVBoxLayout->addWidget(SignUpButton);
    mainVBoxLayout->addWidget(GuestButton);
    setLayout(mainVBoxLayout);
}

void mainWidget::openSignUp(){
    this->close();
    new signUpPage();

}

bool mainWidget::signIn(){
    QString currUsername = userNameLineEdit->text();
    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.close();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    bool exists = false;

    foreach (const QJsonValue &v, accountsArray) {
        if (v.toObject().value("A-username") == currUsername) {
            exists = true;
            user = v;
            break;
        }

    }
    if (exists == false) {
    QMessageBox::critical(this,"Error","Username does not exist!");
    return false;
    }

    else {
        QString userPwd = user.toObject().value("B-password").toString();
        if (pwdLineEdit->text() != userPwd) {
            QMessageBox::critical(this,"Error","Password is incorrect!");
        }
        else {
            this->close();
            new gameMenu(user);


        }

    }



    return true;
}

void mainWidget::playAsGuest(){
    this->close();
    new gameMenu();
}



void mainWidget::styling(QLineEdit *txt) {
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

void mainWidget::labelStyle(QLabel *lbl) {
    lbl->setStyleSheet("font: 15px;");
}


void mainWidget::styleAll() {
    styling(userNameLineEdit);
    labelStyle(userNameLabel);
    styling(pwdLineEdit);
    labelStyle(pwdLabel);

}
