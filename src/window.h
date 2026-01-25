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

class Window : public QMainWindow
{
    Q_OBJECT

private:
    Location                        currentLocation = {};

    QPointer<QNetworkAccessManager> manager         = nullptr;
    QNetworkRequest                 weatherReq      = {};

    QPointer<QWidget>               root            = nullptr;
    QPointer<QHBoxLayout>           rootLayout      = nullptr;
    QPointer<SideBar>               sideBar         = nullptr;
    QPointer<WeatherDisplay>        weatherDisplay  = nullptr;

public:
    Window(QWidget* parent = nullptr);
    ~Window();

private slots:
    void handleLocationSelection(Location& location);
    void handleNetworkReply(QNetworkReply* reply);
};
