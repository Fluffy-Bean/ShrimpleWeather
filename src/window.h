#pragma once

#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPushButton>
#include <QPointer>

#include "api.h"
#include "side_bar.h"
#include "weather_display.h"
#include "window.h"

class Window : public QMainWindow
{
    Q_OBJECT

private:
    API::Location                   currentLocation = {};

    QPointer<QNetworkAccessManager> manager         = nullptr;
    QNetworkRequest                 weatherReq      = {};

    QPointer<QWidget>               root            = nullptr;
    QPointer<QHBoxLayout>           layout      = nullptr;
    QPointer<SideBar>               sideBar         = nullptr;
    QPointer<WeatherDisplay>        weatherDisplay  = nullptr;

public:
    Window(QWidget* parent = nullptr);
    ~Window();

private slots:
    void handleLocationSelection(API::Location& location);
    void handleNetworkReply(QNetworkReply* reply);
};
