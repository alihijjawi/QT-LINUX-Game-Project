#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>


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

    void setText();
    void getCountryPic();
    void getPic();
    void setInternalLayout();
    void setInternalLayout2();
    void setMainLayout();

signals:


public slots:
    void returnToMenu();
    void playGame1slot();
    void checkPreviousScores();
};

#endif // GAMEMENU_H
