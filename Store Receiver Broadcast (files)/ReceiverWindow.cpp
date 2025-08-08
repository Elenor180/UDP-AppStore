#include "ReceiverWindow.h"
#include "UdpListener.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QStatusBar>

ReceiverWindow::ReceiverWindow(QWidget* parent)
    : QMainWindow(parent) {
    setWindowTitle("UDP XML Receiver");
    resize(600, 400);

    textArea = new QTextEdit(this);
    textArea->setReadOnly(true);
    setCentralWidget(textArea);

    statusBar()->showMessage("Listening for UDP broadcast...");

    listener = new UdpListener(this);
    connect(listener, &UdpListener::messageReceived,
            this, &ReceiverWindow::displayMessage);
}

ReceiverWindow::~ReceiverWindow() = default;

void ReceiverWindow::displayMessage(const QString& message) {
    textArea->setPlainText(message);
    statusBar()->showMessage("Message received", 3000);
}
