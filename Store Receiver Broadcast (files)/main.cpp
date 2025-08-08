// This app is connected in a network, it litsens for broadcasts in this network
//It will then take the data fed to it and translate it in the XML format


#include <QApplication>
#include "ReceiverWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    ReceiverWindow window;
    window.show();

    return app.exec();
}
