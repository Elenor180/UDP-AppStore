/* 
 *
 * App-Store + Store Reciever
 *
 *
 * Design strategy
 *
 * Utilized the Software Development Life Cycle (SDLC)
 *
 * The Program is optimal:
 *
 * Handles memeory very well with every child class is properly handled
 * Parent classes are given responisbilty to delete all their child class in a composition relationship
 *
 * Objects declared are carefully monitored for safe handling of memory using (Destructor)
 *
 *
 * Decoupling ensures proper management of individual components and ensures easy debugging as we track the movement
 * of Data through out the program
 *
 *
 * Design Principles
 *
 * Loose coupling: Each component is self conatined.
 * Communication is done via signals and slots
 *
 *
 * Qt Signal Slot Mechanism enhancing decoupling communication
 * between UI and logic layer, making use of the MVC pattern
 *
 * Threading: Broadcaster runs on its own thread as instructed, this makes it avoid blocking the GUI
 *
 *
 * Design Patterns:
 *
 * Singleton
 * Observer Pattern
 * Thread Pattern
 * MVC Pattern
 * Composite Pattern
 * Factory Pattern
 *
 *
 * Major Data structures:
 *
 * QList
 * QHeap
 * QMap
 *
 *
 * For full overview of this program please refer to the Read Me file included in the folder


*/
#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QTimer>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    //Splash Screen Setup
    QPixmap pixmap(":/resources/splash.png");  // Ensures this image is in the .qrc file
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage("Loading Store Application...", Qt::AlignBottom | Qt::AlignCenter, Qt::white);


    MainWindow* window = new MainWindow;

    // Delay showing the main window until splash screen closes
    QTimer::singleShot(2000, &app, [&]() {
        splash.close();
        window->show();
    });


    return app.exec();
}
