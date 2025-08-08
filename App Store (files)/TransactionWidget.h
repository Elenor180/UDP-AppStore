#ifndef TRANSACTIONWIDGET_H
#define TRANSACTIONWIDGET_H

#include <QWidget>
#include <QMap>

class QComboBox;
class QSpinBox;
class QPushButton;

class TransactionWidget : public QWidget {
    Q_OBJECT

public:
    explicit TransactionWidget(QWidget* parent = nullptr);

signals:
    void transactionRecorded();

public slots:
    void refreshCustomerList();
    void refreshItems();

private slots:
    void recordTransaction();

private:
    void setupUI();

    QComboBox* customerCombo;
    QMap<QString, QSpinBox*> itemInputs;
    QPushButton* recordButton;
};

#endif // TRANSACTIONWIDGET_H
