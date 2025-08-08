//Very important class that will communicate with an external app via a network

//It is very important that you run both these apps on one machine or else the ports might not match


#ifndef BROADCASTER_H
#define BROADCASTER_H


#include <QThread>

class Broadcaster : public QThread {
    Q_OBJECT
public:
    explicit Broadcaster(QObject* parent = nullptr);

protected:
    void run() override;

private:
    QString generateXml() const;
};

#endif // BROADCASTER_H
