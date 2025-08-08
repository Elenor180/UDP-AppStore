#ifndef CUSTOMERWIDGET_H
#define CUSTOMERWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
class QListWidget;

class CustomerWidget : public QWidget {
    Q_OBJECT
public:
    explicit CustomerWidget(QWidget* parent = nullptr);

signals:
    void customerAdded();

private slots:
    void handleAddCustomer();

private:
    QLineEdit* nameEdit;
    QPushButton* addButton;
    QListWidget* customerList;

    void refreshCustomerList();
};

#endif // CUSTOMERWIDGET_H
