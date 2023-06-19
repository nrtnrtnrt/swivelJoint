#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QDebug>
#include <QValueAxis>
#include <QTimer>
#include <QDateTime>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include "thread.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    void connetSignals();

    void UiStyle();
    void CurvePlotting();

private:
    Ui::Widget *ui;

    SerialThread *serial_thread = nullptr;

    QChart *Chart;             // 图表对象
    QLineSeries *LineSeries0;   // 展示在图表对象上面的线对象0
    QLineSeries *LineSeries1;   // 展示在图表对象上面的线对象1
    QLineSeries *LineSeries2;   // 展示在图表对象上面的线对象2
    QLineSeries *LineSeries3;   // 展示在图表对象上面的线对象3

    QVector<QPointF> Pointf0;  // 绘制线对象所需要的数据
    QValueAxis *AxisX0;         // X轴
    QValueAxis *AxisY0;         // Y0轴
    QValueAxis *AxisY1;         // Y1轴
    QValueAxis *AxisY2;         // Y2轴
    QValueAxis *AxisY3;         // Y3轴

    //X轴与Y轴最大值
    const int MAX_X = 60;
    const int MAX_Y0 = 1000;
    const int MAX_Y1 = 200;
    const int MAX_Y2 = 5;
    const int MAX_Y3 = 50;

    //布局
    QHBoxLayout *Tab2_HBoxLay0;
    QHBoxLayout *Tab2_HBoxLay1;
    QHBoxLayout *Tab2_HBoxLay2;


    QVBoxLayout *Tab2_VBoxlay;

    QVBoxLayout *Tab2_VBoxlay1;

    //定时器
    QTimer* m_timer0;

    //计数器
    int PointCount0;



private slots:
    void mTimeout();

   //tab2
    void tab2_start();
    void tab2_pb1();
    void tab2_pb2();
    void tab2_pb3();
    void tab2_pb4();
    void tab2_pb5();

    void serial_signal_0(int);


};

#endif // WIDGET_H
