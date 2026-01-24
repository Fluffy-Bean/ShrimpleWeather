#pragma once

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QLabel>

#include "search_bar.h"
#include "weather_data.h"

class Window : public QMainWindow
{
    Q_OBJECT

private:
    QNetworkAccessManager* manager         = nullptr;
    QNetworkRequest        locationRequest = {};
    QNetworkRequest        weatherRequest  = {};

    QWidget*               root            = nullptr;
    QVBoxLayout*           rootLayout      = nullptr;
    SearchBar*             searchBar       = nullptr;
    WeatherData*           weatherData     = nullptr;

    // Defaults to Brighton, though this gets reset on the first query anyway...
    double                 longitude       = -0.1395;
    double                 latitude        = 50.8284;

public:
    Window(QWidget* parent = nullptr);
    ~Window();

private:
    void updateLocation(QStringView query);
    void updateWeatherData();

private slots:
    void handleSearch(QStringView query);
    void handleNetworkRequest(QNetworkReply* reply);
};
