#pragma once

#include <QLabel>
#include <QLayout>
#include <QList>
#include <QPointer>
#include <QScrollArea>
#include <QString>
#include <QWidget>

#include "../api/open_meteo.h"

class Hourly : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout>   layout   = nullptr;
    QList<QPointer<QLabel>> labels = {};

public:
    Hourly(QWidget* parent = nullptr);
    ~Hourly();

public slots:
    void handleRefresh(API::Response& response);
};
