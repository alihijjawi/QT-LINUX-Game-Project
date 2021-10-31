#include "game1scene.h"
#include "gameMenu.h"

#include <QTimer>


game1scene::game1scene(QJsonValue user,QWidget *parent) : QWidget(parent)
{

    loggedInUser = user;
    listButtons = new QList<QPushButton*>;


    internalGridLayout = new QGridLayout();
    time = new QTime(0,5,0);
    initialize();

    addButtons();
    setShipPictures();
    setInternalLayout();
    setMainLayout();

    QObject::connect(leaveBtn, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));






    show();



    timerCountdown = new QTimer(this);
    connect(timerCountdown, SIGNAL(timeout()), this, SLOT(updateCountdown()));
    timerCountdown->start(1000);

    timerScore = new QTimer(this);
    connect(timerScore, SIGNAL(timeout()), this, SLOT(checkScore()));
    timerScore->start(500);

}

void game1scene::updateCountdown(){
    *time = time->addSecs(-1);
    countdown->setText("Time Left:\n    "+time->toString("m:ss"));
    QTime end(0,0,0);
    if (*time == end) {
        timeUp = true;
        checkScore();
    }
}

void game1scene::initialize(){
    setFixedSize(1114,802);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Game One");
    QPixmap bkgnd(":/Game1Files/game1backround.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    setPalette(palette);

    countdown = new QLabel("Time Left:\n    "+time->toString("m:ss"));
    countdown->setParent(this);
    countdown->move(485,350);
    QFont arielFont("Ariel",20);
    countdown->setFont(arielFont);
    countdown->resize(180,80);
    countdown->raise();

    leaveBtn = new QPushButton("Leave Game!");
    leaveBtn->setParent(this);
    leaveBtn->move(500,700);
    leaveBtn->resize(90,40);
    leaveBtn->raise();

}

void game1scene::returnToMenu(){
    this->close();
    new gameMenu(loggedInUser);
}
void game1scene::styleButton(QPushButton *btn) {
    btn->setContentsMargins(0,0,0,0);
    btn->setContentsMargins(0,0,0,0);
    QSize btnSize = QSize(90,90);
    btn->setFixedSize(btnSize);
    btn->setStyleSheet("QPushButton{background: rgba(255,255,255,0);"
                            "color:white;}");
}


void game1scene::addButtons(){
    randomizeShips();
    shipPositions();
    qInfo()<<locSmallShip1 +"small";
    qInfo()<<locSmallShip2 +"small2";
    qInfo()<<locMediumShip11+"medium";
    qInfo()<<locMediumShip21+"medium2";
    qInfo()<<locBigShip1+"large";


    a11 = new QPushButton("a11");
    a12 = new QPushButton("a12");
    a13 = new QPushButton("a13");
    a14 = new QPushButton("a14");
    a21 = new QPushButton("a21");
    a22 = new QPushButton("a22");
    a23 = new QPushButton("a23");
    a24 = new QPushButton("a24");
    a31 = new QPushButton("a31");
    a32 = new QPushButton("a32");
    a33 = new QPushButton("a33");
    a34 = new QPushButton("a34");
    a41 = new QPushButton("a41");
    a42 = new QPushButton("a42");
    a43 = new QPushButton("a43");
    a44 = new QPushButton("a44");
    listButtons->append(a11);
    listButtons->append(a12);
    listButtons->append(a13);
    listButtons->append(a14);
    listButtons->append(a21);
    listButtons->append(a22);
    listButtons->append(a23);
    listButtons->append(a24);
    listButtons->append(a31);
    listButtons->append(a32);
    listButtons->append(a33);
    listButtons->append(a34);
    listButtons->append(a41);
    listButtons->append(a42);
    listButtons->append(a43);
    listButtons->append(a44);
    for(QPushButton * button: *listButtons) {
        QString btnText = button->text();
        QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(clickButton()));
        styleButton(button);
    }

}


void game1scene::randomizeShips() {
    bool sameRow = false;

    bigShipI = QRandomGenerator::global()->bounded(1,5);


    mediumShip1I = QRandomGenerator::global()->bounded(1,5);
    while(mediumShip1I==bigShipI){
    mediumShip1I = QRandomGenerator::global()->bounded(1,5);
    }
    mediumShip1J = QRandomGenerator::global()->bounded(1,4);


    mediumShip2I = QRandomGenerator::global()->bounded(1,5);
    while(mediumShip2I==bigShipI){
    mediumShip2I = QRandomGenerator::global()->bounded(1,5);
    }
    if (mediumShip1I==mediumShip2I) {
        if (mediumShip1J == 1)
            mediumShip2J = 3;
        if (mediumShip1J == 3)
            mediumShip2J = 1;
        if(mediumShip1J == 2){
            mediumShip2I = QRandomGenerator::global()->bounded(1,5);
            while(mediumShip2I==bigShipI||mediumShip2I==mediumShip1I){
                mediumShip2I = QRandomGenerator::global()->bounded(1,5);
            }
            mediumShip2J = QRandomGenerator::global()->bounded(1,4);
        }
    }
    else if (mediumShip1I!=mediumShip2I)
        mediumShip2J = QRandomGenerator::global()->bounded(1,4);

    if(mediumShip1I==mediumShip2I)
        sameRow = true;
    if (sameRow){
        smallShip1I = QRandomGenerator::global()->bounded(1,5);
        while(smallShip1I==bigShipI || smallShip1I == mediumShip1I){
            smallShip1I = QRandomGenerator::global()->bounded(1,5);
        }
        smallShip1J = QRandomGenerator::global()->bounded(1,5);
    }
    else if(!sameRow){
        smallShip1I = QRandomGenerator::global()->bounded(1,5);
        while(smallShip1I==bigShipI){
            smallShip1I = QRandomGenerator::global()->bounded(1,5);
        }
        smallShip1J = QRandomGenerator::global()->bounded(1,5);
        if (smallShip1I == mediumShip1I){
            while(smallShip1J==mediumShip1J||smallShip1J==mediumShip1J+1){
                smallShip1J = QRandomGenerator::global()->bounded(1,5);
            }

        }
        if (smallShip1I == mediumShip2I){
            while(smallShip1J==mediumShip2J||smallShip1J==mediumShip2J+1){
                smallShip1J = QRandomGenerator::global()->bounded(1,5);
            }

        }

    }

    if (sameRow){
        smallShip2I = QRandomGenerator::global()->bounded(1,5);
        while(smallShip2I==bigShipI || smallShip2I == mediumShip1I){
            smallShip2I = QRandomGenerator::global()->bounded(1,5);
        }
        smallShip2J = QRandomGenerator::global()->bounded(1,5);
        if (smallShip2I==smallShip1I){
            while(smallShip2J==smallShip1J){
                smallShip2J = QRandomGenerator::global()->bounded(1,5);}
        }
        else if (smallShip2I!=smallShip1I){
            smallShip2J = QRandomGenerator::global()->bounded(1,5);
        }
    }

    if (!sameRow){
        smallShip2I = QRandomGenerator::global()->bounded(1,5);
        while(smallShip2I==bigShipI){
            smallShip2I = QRandomGenerator::global()->bounded(1,5);
        }
        smallShip2J = QRandomGenerator::global()->bounded(1,5);
        if (smallShip2I == mediumShip1I){
            if (smallShip2I==smallShip1I) {
                while(smallShip2J==mediumShip1J||smallShip2J==mediumShip1J+1||smallShip2J==smallShip1J){
                    smallShip2J = QRandomGenerator::global()->bounded(1,5);
                }
            }
            else if (smallShip2I!=smallShip1I){
                while(smallShip2J==mediumShip1J||smallShip2J==mediumShip1J+1){
                    smallShip2J = QRandomGenerator::global()->bounded(1,5);
                }
            }
        }
        if (smallShip2I == mediumShip2I){
            if (smallShip2I==smallShip1I) {
                while(smallShip2J==mediumShip2J||smallShip2J==mediumShip2J+1||smallShip2J==smallShip1J){
                    smallShip2J = QRandomGenerator::global()->bounded(1,5);
                }
               }
            else if (smallShip2I!=smallShip1I){
                while(smallShip2J==mediumShip1J||smallShip2J==mediumShip1J+1){
                    smallShip2J = QRandomGenerator::global()->bounded(1,5);
                }
            }

        }

    }



}

void game1scene::shipPositions() {
    QString strSSI = QString::number(smallShip1I);
    QString strSSJ = QString::number(smallShip1J);
    locSmallShip1 = "a" + strSSI+strSSJ;

    QString strSSI2 = QString::number(smallShip2I);
    QString strSSJ2 = QString::number(smallShip2J);
    locSmallShip2 = "a" + strSSI2+strSSJ2;

    QString strMSI1 = QString::number(mediumShip1I);
    QString strMSJ1 = QString::number(mediumShip1J);
    QString strMSJ12 = QString::number(mediumShip1J+1);
    locMediumShip11 = "a" + strMSI1+strMSJ1;
    locMediumShip12 = "a" + strMSI1+strMSJ12;

    QString strMSI2 = QString::number(mediumShip2I);
    QString strMSJ2 = QString::number(mediumShip2J);
    QString strMSJ22 = QString::number(mediumShip2J+1);
    locMediumShip21 = "a" + strMSI2+strMSJ2;
    locMediumShip22 = "a" + strMSI2+strMSJ22;

    QString strBS = QString::number(bigShipI);
    locBigShip1 = "a" + strBS +QString::number(1);
    locBigShip2 = "a" + strBS +QString::number(2);
    locBigShip3 = "a" + strBS +QString::number(3);
    locBigShip4 = "a" + strBS +QString::number(4);
}

void game1scene::clickButton() {
    bool sF = false;
    QPushButton* buttonSender = qobject_cast<QPushButton*>(sender());
    QString btnText = buttonSender->text();
    QStringList ll =btnText.split("");
    QString strRow = ll[2];
    QString strCol = ll[3];
    int btnRow = strRow.toInt();
    int btnCol = strCol.toInt();

    int btnLocX = buttonSender->x();
    int btnLocY = buttonSender->y();
    if (btnText == locSmallShip1) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
            smallShipPic1->move(btnLocX+660,btnLocY+317);
            smallShipPic1->show();
            smallShipPic1->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
            }}}
    if (btnText == locSmallShip2) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
            smallShipPic2->move(btnLocX+660,btnLocY+317);
            smallShipPic2->show();
            smallShipPic2->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
            }}}
    if (btnText == locMediumShip11) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                mediumShipPic11->move(btnLocX+660,btnLocY+317);
                mediumShipPic11->show();
                mediumShipPic11->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locMediumShip12) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                mediumShipPic12->move(btnLocX+660,btnLocY+317);
                mediumShipPic12->show();
                mediumShipPic12->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locMediumShip21) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                mediumShipPic21->move(btnLocX+660,btnLocY+317);
                mediumShipPic21->show();
                mediumShipPic21->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locMediumShip22) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                mediumShipPic22->move(btnLocX+660,btnLocY+317);
                mediumShipPic22->show();
                mediumShipPic22->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locBigShip1) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                largeShipPic1->move(btnLocX+660,btnLocY+317);
                largeShipPic1->show();
                largeShipPic1->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);

                }}}
    if (btnText == locBigShip2) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                largeShipPic2->move(btnLocX+660,btnLocY+317);
                largeShipPic2->show();
                largeShipPic2->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locBigShip3) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                largeShipPic3->move(btnLocX+660,btnLocY+317);
                largeShipPic3->show();
                largeShipPic3->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}
    if (btnText == locBigShip4) {
        sF = true;
        QString ans = openQuestionDialog();
        if (!(ans == "noans")) {
            if (ans == "corr") {
                largeShipPic4->move(btnLocX+660,btnLocY+317);
                largeShipPic4->show();
                largeShipPic4->raise();
            }
            if (ans == "wrong") {
                qInfo() <<"you missed!";

                buttonSender->setText("MISS");
                buttonSender->setStyleSheet("QPushButton{background: rgba(0,0,0,1);"
                                        "color:white;}");
                buttonSender->setEnabled(false);
                }}}




    if(sF == false) {
        tries = tries +1;
        buttonSender->setEnabled(false);
        QPixmap pixmap(":/Game1Files/miss.png");
        QIcon ButtonIcon(pixmap);
        buttonSender->setIcon(ButtonIcon);
        buttonSender->setIconSize(pixmap.rect().size());

    }


}

void game1scene::setInternalLayout() {
    internalGridLayout->addWidget(a11,0,0);
    internalGridLayout->addWidget(a12,0,1);
    internalGridLayout->addWidget(a13,0,2);
    internalGridLayout->addWidget(a14,0,3);
    internalGridLayout->addWidget(a21,1,0);
    internalGridLayout->addWidget(a22,1,1);
    internalGridLayout->addWidget(a23,1,2);
    internalGridLayout->addWidget(a24,1,3);
    internalGridLayout->addWidget(a31,2,0);
    internalGridLayout->addWidget(a32,2,1);
    internalGridLayout->addWidget(a33,2,2);
    internalGridLayout->addWidget(a34,2,3);
    internalGridLayout->addWidget(a41,3,0);
    internalGridLayout->addWidget(a42,3,1);
    internalGridLayout->addWidget(a43,3,2);
    internalGridLayout->addWidget(a44,3,3);
}

void game1scene::setMainLayout() {
    QWidget *w = new QWidget();
    w->setLayout(internalGridLayout);
    w->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    QVBoxLayout* containerLayout = new QVBoxLayout;
    containerLayout->addWidget(w, 0);
    QGridLayout *hboxLayout = new QGridLayout();
    hboxLayout->addItem(new QSpacerItem(605,0),1,0);
    hboxLayout->addItem(new QSpacerItem(0,228),0,1);
    hboxLayout->addItem(containerLayout,1,1);
    setLayout(hboxLayout);

}

void game1scene::setShipPictures() {

    smallShipPic1 = new QLabel();
    QPixmap pm1(":/Game1Files/SmallShip.png");
    smallShipPic1->setPixmap(pm1.scaled(90,90));
    smallShipPic1->setScaledContents(true);
    smallShipPic1->resize(90,90);
    smallShipPic1->setParent(this);
    smallShipPic1->hide();

    smallShipPic2 = new QLabel();
    QPixmap pm11(":/Game1Files/SmallShip.png");
    smallShipPic2->setPixmap(pm1.scaled(90,90));
    smallShipPic2->setScaledContents(true);
    smallShipPic2->resize(90,90);
    smallShipPic2->setParent(this);
    smallShipPic2->hide();

    mediumShipPic11 = new QLabel();
    QPixmap pm2(":/Game1Files/MS/MSL.jpg");
    mediumShipPic11->setPixmap(pm2.scaled(90,90));
    mediumShipPic11->setScaledContents(true);
    mediumShipPic11->resize(90,90);
    mediumShipPic11->setParent(this);
    mediumShipPic11->move(90,200);
    mediumShipPic11->hide();

    mediumShipPic12 = new QLabel();
    QPixmap pm3(":/Game1Files/MS/MSR.jpg");
    mediumShipPic12->setPixmap(pm3.scaled(90,90));
    mediumShipPic12->setScaledContents(true);
    mediumShipPic12->resize(90,90);
    mediumShipPic12->setParent(this);
    mediumShipPic12->move(90,200);
    mediumShipPic12->hide();

    mediumShipPic21 = new QLabel();
    QPixmap pm22(":/Game1Files/MS/MSL.jpg");
    mediumShipPic21->setPixmap(pm2.scaled(90,90));
    mediumShipPic21->setScaledContents(true);
    mediumShipPic21->resize(90,90);
    mediumShipPic21->setParent(this);
    mediumShipPic21->move(90,200);
    mediumShipPic21->hide();

    mediumShipPic22 = new QLabel();
    QPixmap pm33(":/Game1Files/MS/MSR.jpg");
    mediumShipPic22->setPixmap(pm3.scaled(90,90));
    mediumShipPic22->setScaledContents(true);
    mediumShipPic22->resize(90,90);
    mediumShipPic22->setParent(this);
    mediumShipPic22->move(90,200);
    mediumShipPic22->hide();

    largeShipPic1 = new QLabel();
    QPixmap pm4(":/Game1Files/LS/BSL.jpg");
    largeShipPic1->setPixmap(pm4.scaled(90,90));
    largeShipPic1->setScaledContents(true);
    largeShipPic1->resize(90,90);
    largeShipPic1->setParent(this);
    largeShipPic1->hide();

    largeShipPic2 = new QLabel();
    QPixmap pm5(":/Game1Files/LS/BSML.jpg");
    largeShipPic2->setPixmap(pm5.scaled(90,90));
    largeShipPic2->setScaledContents(true);
    largeShipPic2->resize(90,90);
    largeShipPic2->setParent(this);
    largeShipPic2->hide();

    largeShipPic3 = new QLabel();
    QPixmap pm6(":/Game1Files/LS/BSMR.jpg");
    largeShipPic3->setPixmap(pm6.scaled(90,90));
    largeShipPic3->setScaledContents(true);
    largeShipPic3->resize(90,90);
    largeShipPic3->setParent(this);
    largeShipPic3->hide();

    largeShipPic4 = new QLabel();
    QPixmap pm7(":/Game1Files/LS/BSR.jpg");
    largeShipPic4->setPixmap(pm7.scaled(90,90));
    largeShipPic4->setScaledContents(true);
    largeShipPic4->resize(90,90);
    largeShipPic4->setParent(this);
    largeShipPic4->hide();


}

QString game1scene::openQuestionDialog() {
    bool ok = false;
    QStringList items;
    items << tr("Correct Answer") << tr("Wrong Answer");
    QInputDialog *dlg = new QInputDialog();
    dlg->resize(500,500);
    QString ans = dlg->getItem(this, tr("Question:"),
                                         tr("Answer the fucking question:"), items, 0, false, &ok);
    if (ok == false) {
        return "noans";
    }
    tries = tries +1;
    if (ans == "Correct Answer"){
        hits = hits +1;
        return "corr";
    }
    if (ans == "Wrong Answer"){
        misses = misses +1;
        return "wrong";
    }
    return "this function will never reach here :D";
}

void game1scene::checkScore() {
    if (!gameOver) {
        QString missesStr;
        QString hitsStr;
        QMessageBox::StandardButton reply;

        if (tries == 16) {
            gameOver = true;
            missesStr = QString::number(misses)+" time(s)";
            hitsStr = QString::number(hits)+"/10 time(s)";

            if (hits>=7) {
                reply = QMessageBox::question(this, "Game over! You won!", "You uncovered all enemy ships!\nYou hit the enemy ships "+hitsStr+"\nYou got hit "+missesStr+"\nDo you want to play again?",
                                            QMessageBox::Yes|QMessageBox::No);
                }
            else{
                reply = QMessageBox::question(this, "Game over! You lost!", "You uncovered all enemy ships!\nYou hit the enemy ships "+hitsStr+"\nYou got hit "+missesStr+"\nDo you want to play again?",
                                            QMessageBox::Yes|QMessageBox::No);

                }
            timerCountdown->stop();
            timerScore->stop();
            if (loggedInUser!=QJsonValue::Null)
                saveScore();
            if (reply == QMessageBox::No){
                this->close();
                new gameMenu(loggedInUser);}
            else{
                this->close();
                new game1scene(loggedInUser);
                }

        }
        else if (timeUp) {
            missesStr = QString::number(misses)+" time(s)";
            hitsStr = QString::number(hits)+"/10 time(s)";

            reply = QMessageBox::question(this, "Game over! Time is Up!", "You couldn't finish in time!\nYou hit the enemy ships "+hitsStr+"\nYou got hit "+missesStr+"\nDo you want to play again?",
                                            QMessageBox::Yes|QMessageBox::No);

            timerCountdown->stop();
            timerScore->stop();

            if (loggedInUser!=QJsonValue::Null)
                saveScore();
            if (reply == QMessageBox::No) {
                this->close();
                new gameMenu(loggedInUser);
            } else {
                this->close();
                new game1scene(loggedInUser);
                }
        }
    }
}

void game1scene::saveScore() {

    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    file.resize(0);
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    int i = 0;
    QJsonObject currUser;
    foreach (const QJsonValue &v, accountsArray) {
        i = i + 1;
        if (v.toObject().value("A-username") == loggedInUser.toObject().value("A-username").toString()) {
            currUser = v.toObject();
            accountsArray.removeAt(i-1);
            break;
        }
    }
    QJsonArray oldScores = currUser.value("I-Scores").toArray();
    QString aa = QString::number(hits)+"-"+QString::number(misses);
    oldScores.push_back(aa);
    currUser.remove("I-Scores");
    currUser.insert("I-Scores",QJsonValue(oldScores));
    accountsArray.push_back(currUser);

    QJsonObject final_object;
    final_object.insert(QString("accounts"), QJsonValue(accountsArray));
    QJsonDocument updatedDoc;
    updatedDoc.setObject(final_object);
    QByteArray dataPlayer = updatedDoc.toJson();
    file.write(dataPlayer);
    file.close();

}

