#pragma once

#include <QLabel>
#include <QLayout>
#include <QList>
#include <QPointer>
#include <QScrollArea>
#include <QString>
#include <QWidget>

#include "../api.h"

class Hourly : public QWidget
{
    Q_OBJECT

private:
    QPointer<QScrollArea>   scroll = nullptr;
    QPointer<QVBoxLayout>   list   = nullptr;
    QList<QPointer<QLabel>> labels = {};

public:
    Hourly(QWidget* parent = nullptr);
    ~Hourly();

public slots:
    void handleRefresh(API::Response& response);
};
