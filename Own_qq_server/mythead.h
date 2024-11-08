#ifndef MYTHEAD_H
#define MYTHEAD_H

#include <QWidget>
#include <QThread>
#include <QTcpSocket>

class myThead : public QThread
{
    Q_OBJECT
public:
    explicit myThead(QTcpSocket * s);
    void run();

signals:

public slots:
    void clientInfoSlot();

private:
    QTcpSocket *socket;

};

#endif // MYTHEAD_H
