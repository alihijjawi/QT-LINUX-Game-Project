#ifndef PREVIOUSCORES_H
#define PREVIOUSCORES_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "qcustomplot.h"
using namespace QtCharts;

class previouscores : public QWidget
{
    Q_OBJECT
public:
    explicit previouscores(QJsonValue user = QJsonValue::Null,QWidget *parent = nullptr);
    QJsonValue loggedInUser;

    QPushButton *backButton;

    QVBoxLayout *boxLayout;
    //QChartView *chartView;
    QLabel *game1label;
    QLabel *game2label;
    QCustomPlot *scorePlot;

private:

    void setInternalLayout();
    void setMainLayout();

    void intialize();
    void getUser();
    void getScores();

signals:

public slots:
    void showPointToolTip(QMouseEvent *event);
    void returnToMenu();
    void makePlot();
};

#endif // PREVIOUSCORES_H
