//.h file for store reciever that will explicityly listen to a dedicated network
//This file is vital

#ifndef RECEIVERWINDOW_H
#define RECEIVERWINDOW_H

#include <QMainWindow>

class QTextEdit;
class UdpListener; // Allows us to use Qt networking capabilities

//Declaring RecieverWindow as child of mainWindow for auto clean up
class ReceiverWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ReceiverWindow(QWidget* parent = nullptr);
    ~ReceiverWindow() override;

private slots:
    void displayMessage(const QString& message);

private:
    QTextEdit* textArea;
    UdpListener* listener;
};

#endif // RECEIVERWINDOW_H
