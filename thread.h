#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>

#include <QSerialPort>
#include "src/modbus.h"

#include <QTcpServer>
#include <QTcpSocket>


class SerialThread : public QThread
{
    Q_OBJECT
public:
    explicit SerialThread(QObject *parent = nullptr);
    void ReadData();

protected:
    void run();

signals:

public slots:

private:
    QSerialPort *serial = new  QSerialPort();
};

class ModbusThread : public QThread
{
    Q_OBJECT
public:
    explicit ModbusThread(QObject *parent = nullptr);

protected:
    void run();

signals:

public slots:

private:
    modbus_t* LowMachine;
};

class RecvThread : public QThread
{
    Q_OBJECT
public:
    explicit RecvThread(QObject *parent = nullptr);
    QTcpServer *recv_server;
    QTcpSocket *recv_socket;

protected:
    void run();

signals:

public slots:
};



#endif // THREAD_H
