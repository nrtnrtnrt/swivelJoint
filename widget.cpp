#include "widget.h"
#include "ui_widget.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_timer0 = new QTimer();
    m_timer0->setSingleShot(false);
    m_timer0->start(1000);

/************connect******************/
    connetSignals();
/************设置ui样式******************/
    UiStyle();

/************绘制曲线******************/
    CurvePlotting();

}

Widget::~Widget()
{
    delete ui;
}

void Widget::connetSignals()
{
    //Timer
    connect(m_timer0, SIGNAL(timeout()), this, SLOT(mTimeout()));

    //tab2
    connect(ui->pushButton_0,SIGNAL(clicked()), this, SLOT(tab2_start()));
    connect(ui->pushButton_1,SIGNAL(clicked()), this, SLOT(tab2_pb1()));
    connect(ui->pushButton_2,SIGNAL(clicked()), this, SLOT(tab2_pb2()));
    connect(ui->pushButton_3,SIGNAL(clicked()), this, SLOT(tab2_pb3()));
    connect(ui->pushButton_4,SIGNAL(clicked()), this, SLOT(tab2_pb4()));
}

void Widget::UiStyle()
{
    //第一行
    Tab2_HBoxLay0 = new QHBoxLayout();
    Tab2_HBoxLay0->addWidget(ui->label_0);
    Tab2_HBoxLay0->addWidget(ui->label_1);
    Tab2_HBoxLay0->addWidget(ui->label_2);
    Tab2_HBoxLay0->addWidget(ui->label_3);
    Tab2_HBoxLay0->addWidget(ui->label_4);
    Tab2_HBoxLay0->addWidget(ui->label_5);
    Tab2_HBoxLay0->addWidget(ui->label_6);
    Tab2_HBoxLay0->addWidget(ui->label_7);
    //第二行
    Tab2_HBoxLay1 = new QHBoxLayout();
    Tab2_HBoxLay1->addWidget(ui->label_8);
    Tab2_HBoxLay1->addWidget(ui->label_9);
    Tab2_HBoxLay1->addWidget(ui->label_10);
    Tab2_HBoxLay1->addWidget(ui->label_11);
    Tab2_HBoxLay1->addWidget(ui->label_12);
    Tab2_HBoxLay1->addWidget(ui->label_13);
    //第四行按键
    Tab2_HBoxLay2 = new QHBoxLayout();
    Tab2_HBoxLay2->addWidget(ui->pushButton_0);
    Tab2_HBoxLay2->addWidget(ui->pushButton_1);
    Tab2_HBoxLay2->addWidget(ui->pushButton_2);
    Tab2_HBoxLay2->addWidget(ui->pushButton_3);
    Tab2_HBoxLay2->addWidget(ui->pushButton_4);

    //垂直布局
    Tab2_VBoxlay = new QVBoxLayout();
    Tab2_VBoxlay->addLayout(Tab2_HBoxLay0);
    Tab2_VBoxlay->addLayout(Tab2_HBoxLay1);
    Tab2_VBoxlay->addWidget(ui->graphicsView);
    Tab2_VBoxlay->addLayout(Tab2_HBoxLay2);

    ui->tab_2->setLayout(Tab2_VBoxlay);

    Tab2_VBoxlay1 = new QVBoxLayout();
    Tab2_VBoxlay1->addWidget(ui->tabWidget);
    setLayout(Tab2_VBoxlay1);
}

void Widget::CurvePlotting()
{
/*****************各组件实例化****************************/
    Chart = new QChart();

    AxisX0 = new QValueAxis();

//1
    AxisY0 = new QValueAxis();
    AxisY1 = new QValueAxis();
    AxisY2 = new QValueAxis();

//2
    LineSeries0 = new QSplineSeries();
//    LineSeries0->setPen(QPen(QColor(255, 0, 0), 3));
    LineSeries0->setName("转速");
    LineSeries1 = new QSplineSeries();
    LineSeries1->setName("压力");
    LineSeries2 = new QSplineSeries();

//3
    Chart->setTitle("实时动态曲线示例");
    Chart->addSeries(LineSeries0);
    Chart->addSeries(LineSeries1);
    Chart->addSeries(LineSeries2);

/*****************YO轴设置  转速****************************/
    /* 设置显示格式 */
    AxisY0->setLabelFormat("%i");
    /* y轴标题 */
    AxisY0->setTitleText("转速r/s");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY0, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY0->setRange(0, MAX_Y0);
    /* 将splineSeries附加于y轴上 */
    LineSeries0->attachAxis(AxisY0);

/*****************Y1轴设置   压力****************************/
    /* 设置显示格式 */
    AxisY1->setLabelFormat("%i");
    /* y轴标题 */
    AxisY1->setTitleText("压力/N");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY1, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY1->setRange(0, MAX_Y1);
    /* 将splineSeries附加于y轴上 */
    LineSeries1->attachAxis(AxisY1);

/*****************Y2轴设置   扭矩****************************/
    /* 设置显示格式 */
    AxisY2->setLabelFormat("%i");
    /* y轴标题 */
    AxisY2->setTitleText("扭矩N·m");
    /* y轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisY2, Qt::AlignLeft);
    /* 设置y轴范围 */
    AxisY2->setRange(-1, MAX_Y2);
    /* 将splineSeries附加于y轴上 */
    LineSeries2->attachAxis(AxisY2);
//4 Y?

/*****************X轴设置****************************/
    /* 设置显示格式 */
    AxisX0->setLabelFormat("%i");
    /* x轴标题 */
    AxisX0->setTitleText("时间/s");
    /* x轴标题位置（设置坐标轴的方向） */
    Chart->addAxis(AxisX0, Qt::AlignBottom);
    /* 设置x轴范围 */
    AxisX0->setRange(0, MAX_X);
    /* 将splineSeries附加于x轴上 */
//5
    LineSeries0->attachAxis(AxisX0);
    LineSeries1->attachAxis(AxisX0);
    LineSeries2->attachAxis(AxisX0);



/*****************chart设置****************************/
    /* 将图表的内容设置在图表视图上 */
    ui->graphicsView->setChart(Chart);
    /* 设置抗锯齿 */
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

/*****************LineSeries0设置****************************/
//    QList<int> data;
//    int n[10] = {0,10,2,3,50,60,20,10,40,30};
//    for(int j = 0; j < 9; j++)
//    {
//        data.append(n[j]);
//    }

//    /* 当储存数据的个数大于最大值时，把第一个数据删除 */
//    while (data.size() > 5) {
//        /* 移除data中第一个数据 */
//        data.removeFirst();
//    }

//    /* 先清空 */
//    LineSeries0->clear();

//    /* 计算x轴上的点与点之间显示的间距 */
//    int xSpace = 1;

//    /* 添加点，xSpace * i 表示第i个点的x轴的位置 */
//    for (int i = 0; i < data.size(); ++i) {
//        LineSeries0->append(xSpace * i, data.at(i));
//        if(i > 7)
//        {
//            LineSeries0->remove(0);

//        }
//    }
}

void Widget::mTimeout()
{
    if(PointCount0 > MAX_X)
    {
        LineSeries0->remove(0);
        LineSeries1->remove(0);
        LineSeries2->remove(0);

        Chart->axisX()->setMin(PointCount0 - MAX_X);
        Chart->axisX()->setMax(PointCount0);                    // 更新X轴范围

    }
    LineSeries0->append(QPointF(PointCount0, rand() % MAX_Y0));  // 更新显示（随机生成10以内的一个数）
    LineSeries1->append(QPointF(PointCount0, rand() % MAX_Y1));  // 更新显示（随机生成10以内的一个数）
    LineSeries2->append(QPointF(PointCount0, rand() % MAX_Y2));  // 更新显示（随机生成10以内的一个数）
    PointCount0++;

    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间

    QString str = dateTime.toString("yyyy-MM-dd hh:mm:ss");//格式化时间
    ui->label_7->setText(str);
    ui->label_13->setText("24℃");
}

void Widget::tab2_start()
{
    m_timer0->start(1000);
}

void Widget::tab2_pb1()
{
    LineSeries0->show();
    LineSeries1->hide();
    LineSeries2->hide();

    AxisY0->show();
    AxisY1->hide();
    AxisY2->hide();
}

void Widget::tab2_pb2()
{
    LineSeries1->show();
    LineSeries0->hide();
    LineSeries2->hide();

    AxisY1->show();
    AxisY0->hide();
    AxisY2->hide();
}

void Widget::tab2_pb3()
{
    LineSeries2->show();
    LineSeries1->hide();
    LineSeries0->hide();

    AxisY2->show();
    AxisY1->hide();
    AxisY0->hide();
}

void Widget::tab2_pb4()
{
    LineSeries0->show();
    LineSeries1->show();
    LineSeries2->show();

    AxisY2->show();
    AxisY1->show();
    AxisY0->show();
}
