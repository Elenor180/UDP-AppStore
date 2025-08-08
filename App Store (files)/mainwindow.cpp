#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>

#include "Broadcaster.h"           // UDP broadcaster
#include "AddItemWidget.h"
#include "TransactionWidget.h"
#include "TransactionViewWidget.h"
#include "StoreData.h"
#include "BackupManager.h"
#include "CustomerWidget.h"


/*Interesting enough this needs investigation
 *
 * My backup manager seems to have an error of static declaration, this is declared globally
 *
 * Soon as remove static to because of Qt's complain, program fails to build, no idea why
 */

static BackupManager backupManager;  // Global backup manager

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setWindowTitle("Store Tracker");
    resize(800, 600);


    // Menu Bar
    QMenu* fileMenu = menuBar()->addMenu("File");
    QAction* exitAction = new QAction("Exit", this);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);

    QMenu* helpMenu = menuBar()->addMenu("Help");
    QAction* aboutAction = helpMenu->addAction("About");
    connect(aboutAction, &QAction::triggered, this, [] {
        QMessageBox::about(nullptr, "About StoreApp","StoreApp v1.0\n\nDeveloped using Qt 6\nby Randy Kubheka.");
    });

    QAction* helpAction = helpMenu->addAction("Help");
    connect(helpAction, &QAction::triggered, this, [] {
        QMessageBox::information(nullptr, "Help", "Instructions:\n\n""1. Use the toolbar to add items and customers.\n""2. Record transactions for each customer.\n"
                                 "3. Broadcast transaction data via the Broadcast button.\n"
                                 "4. Restore item list using Restore Backup.");
    });

    // Toolbar
    QToolBar* mainToolBar = addToolBar("Main Toolbar");

    // Add Customer action - opens CustomerWidget dialog or widget
    QAction* addCustomerAction = mainToolBar->addAction("Add Customer");

    AddItemWidget* addItemWidget = new AddItemWidget(this);
    transactionWidget = new TransactionWidget(this);
    transactionWidget->refreshCustomerList();

    transactionView = new TransactionViewWidget(this);

    CustomerWidget* customerWidget = new CustomerWidget(this);

    // Show CustomerWidget on toolbar action
    connect(addCustomerAction, &QAction::triggered, this, [customerWidget]() {
        customerWidget->show();
    });

    // Refresh customer list in TransactionWidget when a new customer is added
    connect(customerWidget, &CustomerWidget::customerAdded,
            transactionWidget, &TransactionWidget::refreshCustomerList);

    // Restore backup action
    QAction* restoreAction = mainToolBar->addAction("Restore Backup");
    connect(restoreAction, &QAction::triggered, this, &MainWindow::restoreItemBackup);

    // Broadcast action
    QAction* broadcastAction = mainToolBar->addAction("Broadcast");
    connect(broadcastAction, &QAction::triggered, this, &MainWindow::broadcastData);


    // Status Bar
    statusBar()->showMessage("Welcome to Store Tracker");


    // Central Layout for Widgets
    QVBoxLayout* centralLayout = new QVBoxLayout;

    centralLayout->addWidget(customerWidget);
    centralLayout->addWidget(addItemWidget);
    centralLayout->addWidget(transactionWidget);
    centralLayout->addWidget(transactionView);

    QWidget* container = new QWidget(this);
    container->setLayout(centralLayout);
    setCentralWidget(container);


    // Signal Connections

    // IMPORTANT: Refresh item inputs when a new item is added
    connect(addItemWidget, &AddItemWidget::itemAdded, this, [this]() {
        transactionWidget->refreshItems();  // Refresh items UI safely
        statusBar()->showMessage("Item successfully added.", 3000);
    });

    // Update transaction view when a transaction is recorded
    connect(transactionWidget, &TransactionWidget::transactionRecorded,
            transactionView, &TransactionViewWidget::updateModel);
}

MainWindow::~MainWindow() = default;


// Broadcast Transactions via UDP
void MainWindow::broadcastData() {
    Broadcaster* broadcaster = new Broadcaster(this);  // Auto-managed by Qt parent system
    broadcaster->start();
    statusBar()->showMessage("Broadcasting data over UDP...", 3000);
}

// Restore Item List from In Memory Backup

void MainWindow::restoreItemBackup() {
    auto restored = backupManager.restoreBackup();

    // Replace the items list in StoreData singleton
    auto& store = StoreData::instance();
    store.replaceItems(restored);

    statusBar()->showMessage("Item list restored from backup.");
}
