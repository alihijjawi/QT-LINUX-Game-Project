#include "previouscores.h"
#include "gameMenu.h"
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
using namespace QtCharts;
previouscores::previouscores(QJsonValue user,QWidget *parent) : QWidget(parent)
{
    loggedInUser = user;
    getUser();


    backButton = new QPushButton("Back To Menu!");
    game1label = new QLabel("Previous Battleship Scores:");
    game2label = new QLabel("Previous Shooting Discs Scores:");
    boxLayout = new QVBoxLayout();
    scorePlot = new QCustomPlot();


    //getScores();
    makePlot();
    setMainLayout();


    QObject::connect(scorePlot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    intialize();


}

void previouscores::showPointToolTip(QMouseEvent *event)
{
    int x = scorePlot->xAxis->pixelToCoord(event->pos().x());
    int y = scorePlot->yAxis->pixelToCoord(event->pos().y());
    setToolTip(QString("%1 , %2").arg(x).arg(y));

}
void previouscores::setInternalLayout(){
}


void previouscores::setMainLayout(){
    game1label->setFont(QFont(font().family(),12));
    boxLayout->addWidget(game1label);
    boxLayout->addWidget(scorePlot);
    game2label->setFont(QFont(font().family(),12));
    boxLayout->addWidget(game2label);
    boxLayout->addWidget(backButton);
    setLayout(boxLayout);
}

void previouscores::returnToMenu(){
    this->close();
    new gameMenu(loggedInUser);
}

void previouscores::intialize(){
    this->setFixedSize(600,450);
    adjustSize();
    move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    setWindowTitle("Previous Scores");
    setInternalLayout();
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

void previouscores::makePlot() {
    // generate some data:
    QJsonArray scores = loggedInUser.toObject().value("I-Scores").toArray();
    QVector<double> hits(10), misses(10), games(10); // initialize with entries 0..100
    int i = 0;
    for (const auto &el:scores) {
       QStringList splitScore = el.toString().split("-");
       hits[i]=splitScore[0].toInt();
       misses[i]=splitScore[1].toInt();
       games[i]=i+1;
       i+=1;
    }
    qInfo()<<hits;
    qInfo()<<misses;
    qInfo()<<games;
    scorePlot->addGraph();
    scorePlot->graph(0)->setData(games, hits);
    scorePlot->xAxis->setLabel("Past Plays");
    scorePlot->yAxis->setLabel("Past Scores");
    scorePlot->xAxis->setRange(1, 10);
    scorePlot->yAxis->setRange(0, 10);
    QPen pen;
    pen.setColor(Qt::red);
    pen.setStyle(Qt::DotLine);
    pen.setWidthF(0.5);
    scorePlot->graph()->setPen(pen);
    scorePlot->graph()->setLineStyle(QCPGraph::LineStyle::lsLine);
    QCPScatterStyle style;
    style.setSize(8);
    style.setShape(QCPScatterStyle::ssDisc);
    QPen pen2;
    pen.setColor(Qt::blue);
    style.setPen(pen2);
    scorePlot->graph()->setScatterStyle(style);
    for (int i=0;i<scores.size();i++){
    QCPItemText *textLabel = new QCPItemText(scorePlot);
    textLabel->setPositionAlignment( Qt::AlignLeft | Qt::AlignBottom);
    textLabel->position->setCoords(i+1.2, hits[i]-0.5); // place position at center/top of axis rect
    textLabel->setText("Game "+QString::number(i+1)+":\nHits: "+QString::number(hits[i])+"\nMisses: "+QString::number(10-hits[i]));
    textLabel->setFont(QFont(font().family(), 8.5));
    }
    scorePlot->replot();
    scorePlot->setFixedSize(600,375);
}