#include <QApplication>
#include "mainWidget.h"
#include <QDir>

/**
* \mainpage Project Group 1
* \author Hassan El Khatib
* \author Ali Hijjawi
* \date 11-28-2021
*/
int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    if (!(QDir("/home/eece435l/HassanAliData/").exists())) {
        QDir().mkdir("/home/eece435l/HassanAliData/");
    }

    if (!(QDir("/home/eece435l/HassanAliData/ProfilePics").exists())) {
        QDir().mkdir("/home/eece435l/HassanAliData/ProfilePics");
    }
    QFile file("/home/eece435l/HassanAliData/accounts.json");
    if (!file.exists()) {
        file.open(QIODevice::NewOnly);
    }



    mainWidget *m1 = new mainWidget();
    m1->adjustSize();
    m1->move(QApplication::desktop()->screen()->rect().center() - m1->rect().center());
    m1->show();
    return app.exec();
}


