#pragma once

#include <QFile>
#include <QFontDatabase>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QScrollArea>
#include <QPointer>
#include <QWidget>

#include "api.h"
#include "modules/hourly.h"
#include "modules/overview.h"

class WeatherDisplay : public QScrollArea
{
    Q_OBJECT

private:
    API::Response         currentWeather = {};

    QPointer<QWidget>     container      = nullptr;
    QPointer<QVBoxLayout> layout         = nullptr;
    QPointer<Overview>    overview       = nullptr;
    QPointer<Hourly>      hourly         = nullptr;

public:
    WeatherDisplay(QWidget* parent = nullptr);
    ~WeatherDisplay();

public slots:
    void handleRefresh(API::Response& response);
};
