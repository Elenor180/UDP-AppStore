#ifndef ADDITEMWIDGET_H
#define ADDITEMWIDGET_H

#include <QWidget>


class QLineEdit;
class QRadioButton;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;


class AddItemWidget : public QWidget {
    Q_OBJECT


public:
    explicit AddItemWidget(QWidget* parent = nullptr);

signals:
    void itemAdded(); // Emitted after a successful item addition

private slots:
    void handleAddItem();

private:
    QLineEdit* nameEdit;
    QRadioButton* bookRadio;
    QRadioButton* magazineRadio;
    QPushButton* addButton;


    void setupUI();
};

#endif // ADDITEMWIDGET_H
