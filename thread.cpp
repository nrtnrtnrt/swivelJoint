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

}

