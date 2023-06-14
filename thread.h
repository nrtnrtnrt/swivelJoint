#ifndef THREAD_H
#define THREAD_H

#include <QObject>

class thread : public QObject
{
    Q_OBJECT
public:
    explicit thread(QObject *parent = nullptr);

signals:

public slots:
};

#endif // THREAD_H