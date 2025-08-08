#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Broadcaster;
class TransactionViewWidget;
class TransactionWidget;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private slots:
    void broadcastData();  // New Slot
    void restoreItemBackup();



private:
    Broadcaster* broadcaster; // New member
    TransactionWidget* transactionWidget;
    TransactionViewWidget* transactionView;



};
#endif // MAINWINDOW_H
