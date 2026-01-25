#pragma once

#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QPointer>
#include <QPushButton>
#include <QWidget>

class SavedLocations : public QWidget
{
    Q_OBJECT

public:
    SavedLocations(QWidget* parent = nullptr);
    ~SavedLocations();

private:
    QPointer<QVBoxLayout>        list            = nullptr;
    QList<QPointer<QPushButton>> locationButtons = {};

private slots:
    void handleClick();

signals:
    void onSearch(QStringView query);
};
