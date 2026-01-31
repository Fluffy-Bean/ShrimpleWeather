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
#include "modules/hourly_graph.h"
#include "modules/humidity.h"
#include "modules/overview.h"
#include "modules/wind.h"

class WeatherDisplay : public QScrollArea
{
    Q_OBJECT

private:
    API::Response         currentWeather = {};

    QPointer<Overview>    overview       = nullptr;
    QPointer<HourlyGraph> hourlyGraph    = nullptr;
    QPointer<Humidity>    humidity       = nullptr;
    QPointer<Wind>        wind           = nullptr;
    QPointer<Hourly>      hourly         = nullptr;

public:
    WeatherDisplay(QWidget* parent = nullptr);
    ~WeatherDisplay();

public slots:
    void handleRefresh(API::Response& response);
};
