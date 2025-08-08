#ifndef UDPLISTENER_H
#define UDPLISTENER_H

#include <QObject>

class QUdpSocket;

class UdpListener : public QObject {
    Q_OBJECT

public:
    explicit UdpListener(QObject* parent = nullptr);

signals:
    void messageReceived(const QString& message);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket* socket;
};

#endif // UDPLISTENER_H
