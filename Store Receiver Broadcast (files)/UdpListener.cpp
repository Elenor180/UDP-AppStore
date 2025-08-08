#include "UdpListener.h"
#include <QUdpSocket>

UdpListener::UdpListener(QObject* parent)
    : QObject(parent) {
    socket = new QUdpSocket(this);
    socket->bind(45454, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(socket, &QUdpSocket::readyRead, this, &UdpListener::processPendingDatagrams);
}

void UdpListener::processPendingDatagrams() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(int(socket->pendingDatagramSize()));
        socket->readDatagram(datagram.data(), datagram.size());

        emit messageReceived(QString::fromUtf8(datagram));
    }
}
