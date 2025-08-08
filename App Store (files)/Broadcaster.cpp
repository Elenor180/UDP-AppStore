#include "Broadcaster.h"
#include <QUdpSocket>
#include <QXmlStreamWriter>
#include <QHostAddress>
#include <QDebug>

#include "StoreData.h"
#include "Customer.h"
#include "Transactions.h"
#include "Items.h" // Needed for Item*

Broadcaster::Broadcaster(QObject* parent)
    : QThread(parent) {}

void Broadcaster::run() {
    QUdpSocket socket;

    // Bind to any port just in case the OS/network stack requires it
    if (!socket.bind(QHostAddress::AnyIPv4, 0)) {
        qWarning() << "[UDP] Failed to bind socket:" << socket.errorString();
        return;
    }

    QString xmlData = generateXml();
    QByteArray datagram = xmlData.toUtf8();

    qint64 bytesSent = socket.writeDatagram(datagram, QHostAddress::Broadcast, 45454);

    if (bytesSent == -1) {
        qWarning() << "[UDP] Broadcast failed:" << socket.errorString();
    } else {
        qDebug() << "[UDP] Broadcast success. Bytes sent:" << bytesSent;
    }

    // Optional: Sleep briefly to allow the OS to process the packet before thread ends
    msleep(200);
}

QString Broadcaster::generateXml() const {
    QString xml;
    QXmlStreamWriter writer(&xml);
    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("ModelData"); // Required outer tag

    for (Customer* customer : StoreData::instance().getCustomers()) {
        writer.writeStartElement("customer");
        writer.writeAttribute("name", customer->getName());

        for (Transaction* t : customer->getTransactions()) {
            writer.writeStartElement("transaction");
            writer.writeAttribute("date", t->getDate().toString(Qt::ISODate));

            for (const PurchasedItem& pi : t->getItems()) {
                writer.writeStartElement("lineitem");
                writer.writeAttribute("name", pi.item->getName());
                writer.writeAttribute("type", pi.item->getType());
                writer.writeAttribute("quantity", QString::number(pi.quantity));
                writer.writeEndElement(); // lineitem
            }

            writer.writeEndElement(); // transaction
        }

        writer.writeEndElement(); // customer
    }

    writer.writeEndElement(); // ModelData
    writer.writeEndDocument();

    return xml;
}
