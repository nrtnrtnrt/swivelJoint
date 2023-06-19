#include "thread.h"

modbus_t* pl;

SerialThread::SerialThread(QObject *parent) : QThread(parent)
{

}



void SerialThread::run()
{

    serial->setPortName("USB");
    serial->open(QIODevice::ReadWrite);
    serial->setBaudRate(QSerialPort::Baud57600, QSerialPort::AllDirections);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    //连接信号槽
    connect(serial, &QSerialPort::readyRead, this, &SerialThread::ReadData);

    while(1)
    {
        serial->waitForReadyRead(2000);
    }

}

void SerialThread::ReadData()
{
    QByteArray buf;
    buf = serial->readAll();
    if(!buf.isEmpty())
    {
//        QString str = ui->textEdit->toPlainText();
//        str += tr(buf);
        //定义一个存放数据的东西
        QString necessary = buf.mid(0,3);
        qDebug() << "necessary:" << necessary;
        int b = necessary.toInt();
        qDebug() << "b:" << b;

        emit serial_signal(b);

    }

    buf.clear();
}

ModbusThread::ModbusThread(QObject *parent) : QThread(parent)
{

}

void ModbusThread::run()
{
    int status = -1;
    LowMachine = modbus_new_rtu("COM7", 115200, 'N', 8, 1);
    modbus_set_slave(LowMachine, 1); //设置modbus从机地址
    status = modbus_connect(LowMachine);
    if(status == -1)
    {
        qDebug() << "modbus connect failed";
    }
    modbus_set_response_timeout(LowMachine, 0, 1000000);
    qDebug() << "status" << status;
    qDebug() << "connect plc success";
}


RecvThread::RecvThread(QObject *parent) : QThread(parent)
{

}

void RecvThread::run()
{
    bool is_timeout;
    char buf[1100] = {0};
    int len = 0;
    recv_server = new QTcpServer();
    recv_server->listen(QHostAddress::Any, 21123);
    qDebug() << "recvthread waiting connect.....";

    recv_server->waitForNewConnection(50000, &is_timeout);
    if(is_timeout == true)
    {
        qDebug() << "recvthread time out";
        return;
    }
    recv_socket = recv_server->nextPendingConnection();
    qDebug() << "recvthread new connection";
    while(1)
    {

        memset(buf, 0, 10);
        recv_socket->waitForReadyRead(-1); //没有东西就阻塞
        len = recv_socket->read(buf, 10);

//        emit read_plc();

        if(len < 0)
        {
            qDebug() << "receive data error";
        }
        else
        {
            qDebug() << "receive :" << len;
            FILE* fp;
            fp = fopen("C:/Users/USER/Desktop/1.txt", "a+");
            fwrite(buf, 1, 1, fp);
            fclose(fp);
        }

//        emit send_sortingResult(buf);
    }

}

