#pragma once

#include <QLayout>
#include <QLineEdit>
#include <QList>
#include <QPointer>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>

class SavedLocations : public QScrollArea
{
    Q_OBJECT

public:
    SavedLocations(QWidget* parent = nullptr);
    ~SavedLocations();

private:
    QList<QPointer<QPushButton>> locationButtons = {};

private slots:
    void handleClick();

signals:
    void onSearch(QStringView query);
};
