#include "previouscores.h"
#include "gameMenu.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
using namespace QtCharts;

/**
* \file previouscores.cpp
* \brief creates the history graph of the user scores
*
* \author Ali Hijjawi
* \author Hassan El Khatib
*/
previouscores::previouscores(QJsonValue user,QWidget *parent) : QWidget(parent)
{
    loggedInUser = user;
    getUser();


    backButton = new QPushButton("Back To Menu!");
    game1label = new QLabel("Previous Battleship Scores:");
    game2label = new QLabel("Previous Shooting Discs Scores:");
    boxLayout = new QVBoxLayout();
    gridLayout = new QGridLayout();
    scorePlot1 = new QCustomPlot();
    scorePlot2 = new QCustomPlot();

    makePlot1();
    makePlot2();
    setMainLayout();

    intialize();


}

void previouscores::setMainLayout(){
    game1label->setFont(QFont(font().family(),12));
    gridLayout->addWidget(game1label,0,0,Qt::AlignCenter);
    gridLayout->addWidget(scorePlot1,1,0);
    game2label->setFont(QFont(font().family(),12));
    gridLayout->addWidget(game2label,0,1,Qt::AlignCenter);
    gridLayout->addWidget(scorePlot2,1,1);
    boxLayout->addItem(gridLayout);
    boxLayout->addWidget(backButton,Qt::AlignCenter);
    setLayout(boxLayout);
}
void previouscores::returnToMenu(){
    this->hide();
    delete scorePlot1;
    delete scorePlot2;
    delete backButton;
    delete game1label;
    delete game2label;
    this->close();
    new gameMenu(loggedInUser);
}

void previouscores::intialize(){
    this->setFixedSize(1050,450);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Previous Scores");
    setMainLayout();
    show();
    QObject::connect(backButton, SIGNAL(clicked(bool)), this, SLOT(returnToMenu()));
}

void previouscores::getUser(){
    QFile file("/home/eece435l/HassanAliData/accounts.json");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray jsonData = file.readAll();
    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonObject object = document.object();
    QJsonValue value = object.value("accounts");
    QJsonArray accountsArray = value.toArray();
    QJsonObject currUser;
    foreach (const QJsonValue &v, accountsArray) {
        if (v.toObject().value("A-username") == loggedInUser.toObject().value("A-username").toString()) {
            loggedInUser=v;
            break;
        }
    }
}

void previouscores::makePlot1() {
    QJsonArray scores = loggedInUser.toObject().value("I-Scores").toArray();
    QVector<double> hits, misses, games; // initialize with entries 0..100
    int i = 0;
    for (const auto &el:scores) {
       QStringList splitScore = el.toString().split("-");
       hits.push_back(splitScore[0].toInt());
       misses.push_back(splitScore[1].toInt());
       games.push_back(i+1);
       i+=1;
    }
    scorePlot1->addGraph();
    scorePlot1->graph(0)->setData(games, hits);
    scorePlot1->xAxis->setLabel("Past Plays");
    scorePlot1->yAxis->setLabel("Past Scores");
    scorePlot1->xAxis->setRange(0, games.length()+1);
    scorePlot1->yAxis->setRange(0, 11);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DotLine);
    pen.setWidthF(0.5);
    scorePlot1->graph()->setPen(pen);
    scorePlot1->graph()->setLineStyle(QCPGraph::LineStyle::lsLine);
    QCPScatterStyle style;
    style.setSize(8);
    style.setShape(QCPScatterStyle::ssDisc);
    QPen pen2;
    pen.setColor(Qt::blue);
    style.setPen(pen2);
    scorePlot1->graph()->setScatterStyle(style);
    for (int i=0;i<scores.size();i++){
    QCPItemText *textLabel = new QCPItemText(scorePlot1);
    textLabel->setPositionAlignment( Qt::AlignLeft | Qt::AlignBottom);
    textLabel->position->setCoords(i+1.05, hits[i]-0.5); // place position at center/top of axis rect
    textLabel->setText("Hits: "+QString::number(hits[i])+"\nMisses: "+QString::number(10-hits[i]));
    textLabel->setFont(QFont(font().family(), 7));
    }
    scorePlot1->replot();
    scorePlot1->setFixedSize(525,380);
}

void previouscores::makePlot2() {
    QJsonArray scores = loggedInUser.toObject().value("J-Scores").toArray();
    QVector<double> hits, bonus, games;
    int i = 0;
    for (const auto &el:scores) {
       QStringList splitScore = el.toString().split("-");
       hits.push_back(splitScore[0].toInt());
       bonus.push_back(splitScore[1].toInt());
       games.push_back(i+1);
       i+=1;
    }
    scorePlot2->addGraph();
    scorePlot2->graph(0)->setData(games, hits);
    scorePlot2->xAxis->setLabel("Past Plays");
    scorePlot2->yAxis->setLabel("Past Scores");
    scorePlot2->xAxis->setRange(0, games.length()+1);
    scorePlot2->yAxis->setRange(0, 300);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DotLine);
    pen.setWidthF(0.5);
    scorePlot2->graph()->setPen(pen);
    scorePlot2->graph()->setLineStyle(QCPGraph::LineStyle::lsLine);
    QCPScatterStyle style;
    style.setSize(8);
    style.setShape(QCPScatterStyle::ssDisc);
    QPen pen2;
    pen.setColor(Qt::blue);
    style.setPen(pen2);
    scorePlot2->graph()->setScatterStyle(style);
    for (int i=0;i<scores.size();i++){
    QCPItemText *textLabel = new QCPItemText(scorePlot2);
    textLabel->setPositionAlignment( Qt::AlignLeft | Qt::AlignBottom);
    textLabel->position->setCoords(i+1.2, hits[i]-1.5);
    textLabel->setText("Score: "+QString::number(hits.at(i))+"\nBonus: "+QString::number(bonus.at(i)));
    textLabel->setFont(QFont(font().family(), 7));
    }
    scorePlot2->replot();
    scorePlot2->setFixedSize(525,380);
}
