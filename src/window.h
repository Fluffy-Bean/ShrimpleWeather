#pragma once

#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QPointer>

#include "side_bar.h"
#include "weather_display.h"
#include "window.h"
#include "api/open_meteo.h"

class Window : public QMainWindow
{
    Q_OBJECT

private:
    API::Response            currentWeather  = {};

    QPointer<QWidget>        root            = nullptr;
    QPointer<QHBoxLayout>    layout          = nullptr;
    QPointer<SideBar>        sideBar         = nullptr;
    QPointer<WeatherDisplay> weatherDisplay  = nullptr;

public:
    Window(QWidget* parent = nullptr);
    ~Window();

private slots:
    void handleLocationSelection(API::Location& location);
};
