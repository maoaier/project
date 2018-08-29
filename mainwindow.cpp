#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupRealtimeDataDemo(ui->customPlot);
    connect(ui->customPlot,SIGNAL(triangleClick(double)),this,SLOT(exhibition(double)));
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
    //清除所有的线
    ui->customPlot->clearGraphs();
    //ui->customPlot->mousePressEvent();
    //ui->customPlot->close();
    //QCustomPlot *customPlot=ui->customPlot;
    //自适应宽度与移动与
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    customPlot->addGraph();//真加一条线
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph//设置蓝色的比
    //customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
//    customPlot->addGraph();
//    customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    double key = 1.53378e+09;//QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

   // customPlot->xAxis->addTickTriangle(key+2);
    customPlot->xAxis->addTickTriangle(key+20);
    customPlot->xAxis->addTickTriangle(key+50);
    customPlot->xAxis->addTickTriangle(key+8);
    customPlot->xAxis->addTickTriangle(key+3);
    customPlot->xAxis->addTickTriangle(key+3.5);
    customPlot->xAxis->addTickTriangle(key+6);//增加一条小三角
//    customPlot->xAxis->addTickTriangle(key+8);
    customPlot->xAxis->addTickTriangle(key+10);
    qDebug()<<"key ="<<key;
    QVector<double> x(251), y0(251);// y1(251);
    for (int i=0; i<251; ++i)
    {
      x[i] = key+i/20.0;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0)*50; // exponentially decaying cosine
     // y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    customPlot->xAxis->setDateTimeFormat("hh:mm:ss");//设置的时间的格式
    customPlot->xAxis->setAutoTickStep(false);//设置自适应刻度为false
    customPlot->xAxis->setTickStep(TICKSTEPX);
    customPlot->yAxis->setTickStep(TICKSTEPY);//刻度的宽度
    customPlot->axisRect()->setupFullAxesBox();

    customPlot->xAxis2->setVisible(true);//设置是否可见
    customPlot->xAxis2->setTickLabels(false);//设置标签
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
//    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
//    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    tirgonmetry(customPlot,key+2);
    tirgonmetry(customPlot,key+4);
    tirgonmetry(customPlot,key+6);
    tirgonmetry(customPlot,key+8);
    tirgonmetry(customPlot,key+10);
    //customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();//自适应图片
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    //customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:

    customPlot->replot();//显示
}





MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exhibition(double coordinate)
{
    qDebug("coordinate=%f",coordinate);
}

void MainWindow::tirgonmetry(QCustomPlot *customPlot,double x)
{
    customPlot->addGraph();
    int count=customPlot->graphCount();
    qDebug()<<"count="<<count;
    customPlot->graph(count-1)->setPen(QPen(Qt::black)); // line color blue for first graph
    customPlot->graph(count-1)->setBrush(QBrush(Qt::black)); // first gra
    QVector<double> x0(3), y0(3);
    for(int i=0;i<3;i++)
    {
        x0[i]=x+0.1*TICKSTEPX*i-0.1*TICKSTEPX;
        y0[i]=i%2*TICKSTEPY*2;
    }
     customPlot->graph(count-1)->setData(x0, y0);
}





void MainWindow::on_pushButton_clicked()
{
    double key = 1.53378e+09;
    QCustomPlot *customPlot=ui->customPlot;
    bool bo;
    bo=customPlot->xAxis->deleteTickTriangle(key+50);
    qDebug()<<"\nbo="<<bo;
    bo=customPlot->xAxis->deleteTickTriangle(key+8);
    qDebug()<<"\nbo="<<bo;
    bo=customPlot->xAxis->deleteTickTriangle(key+6);
    customPlot->replot();
    qDebug()<<"\nbo="<<bo;
}
