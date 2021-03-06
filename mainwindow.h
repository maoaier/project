#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtAlgorithms>
#include <QVector>
#include "qcustomplot.h"
#include <qmath.h>
#define TICKSTEPX 2
#define TICKSTEPY 2


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void exhibition(double coordinate);

    void on_pushButton_clicked();

private:
   void tirgonmetry(QCustomPlot *customPlot, double x);
   void setupRealtimeDataDemo(QCustomPlot *customPlot);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
