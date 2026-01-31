#pragma once

#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QString>
#include <QWidget>

#include "../api/open_meteo.h"

class Humidity : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout> layout           = nullptr;
    QPointer<QLabel>      measurementLabel = nullptr;

public:
    Humidity(QWidget* parent = nullptr);
    ~Humidity();

public slots:
    void handleRefresh(API::Response& response);
};
