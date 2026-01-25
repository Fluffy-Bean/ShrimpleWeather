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
#include <QPointer>
#include <QWidget>

#include "overview.h"
#include "weather.h"

class WeatherDisplay : public QWidget
{
    Q_OBJECT

private:
    Weather               currentWeather = {};

    QPointer<QVBoxLayout> layout         = nullptr;
    QPointer<Overview>    overview       = nullptr;

public:
    WeatherDisplay(QWidget* parent = nullptr);
    ~WeatherDisplay();

public slots:
    void handleRefresh(Weather& data);
};
