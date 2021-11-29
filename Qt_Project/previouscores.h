#ifndef PREVIOUSCORES_H
#define PREVIOUSCORES_H
#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "GraphingFiles/qcustomplot.h"
using namespace QtCharts;


/**
 * \file previouscores.h
 * \brief Previous Scores Class Decleration
 * This header file includes all the
 * visual elements in addition to the declerations
 * of all fields used in the class implementation
 */
class previouscores : public QWidget
{
    Q_OBJECT
public:
    explicit previouscores(QJsonValue user = QJsonValue::Null,QWidget *parent = nullptr);
    QJsonValue loggedInUser;

    QPushButton *backButton;

    QVBoxLayout *boxLayout;
    QGridLayout *gridLayout;
    //QChartView *chartView;
    QLabel *game1label;
    QLabel *game2label;
    QCustomPlot *scorePlot1;
    QCustomPlot *scorePlot2;

private:
    /**
    * \brief sets the layout of the main window
    */
    void setMainLayout();

    /**
    * \brief initializes all the member fields of the class
    */
    void intialize();

    /**
    * \brief retrieves the username of the current player form JSON file
    */
    void getUser();

    /**
    * \brief plots and displays the scores of the user for game1
    */
    void makePlot1();

    /**
    * \brief plots and displays the scores of the user for game2
    */
    void makePlot2();

signals:

public slots:
    /**
    * \brief returns to the game menu with the logged in user
    */
    void returnToMenu();

};

#endif // PREVIOUSCORES_H
