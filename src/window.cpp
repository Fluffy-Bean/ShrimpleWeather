#include <QFontDatabase>
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QPushButton>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "window.h"
#include "search_bar.h"
#include "weather_data.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setObjectName("Window");

    manager = new QNetworkAccessManager();

    const int fontID         = QFontDatabase::addApplicationFont(":/assets/fonts/Inter.ttf");
    const QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
    QFont font(fontFamily);
    font.setPixelSize(13);

    setFont(font);

    QFile file(":/assets/styles/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QString style_sheet = QString(file.readAll());
    setStyleSheet(style_sheet);

    root = new QWidget(this);
    this->setCentralWidget(root);

    rootLayout = new QVBoxLayout(root);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    searchBar = new SearchBar(root);

    weatherData = new WeatherData(root);

    rootLayout->addWidget(searchBar);
    rootLayout->addWidget(weatherData);

    connect(searchBar, &SearchBar::onSearch, this, &Window::handleSearch);
    connect(manager, &QNetworkAccessManager::finished, this, &Window::handleNetworkRequest);
}

Window::~Window()
{
    delete manager;
}

void Window::updateLocation(QStringView query)
{
    QString url = QString("https://geocoding-api.open-meteo.com/v1/search?name=%1&count=%2")
        .arg(query)
        .arg(1);

    locationRequest.setUrl(QUrl(url));

    manager->get(locationRequest);
}

void Window::updateWeatherData()
{
    QString url = QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&current=temperature_2m,rain&forecast_days=1")
        .arg(latitude)
        .arg(longitude);

    weatherRequest.setUrl(QUrl(url));

    manager->get(weatherRequest);
}

void Window::handleSearch(QStringView query)
{
    qDebug() << "Got search:" << query;

    updateLocation(query);
}

void Window::handleNetworkRequest(QNetworkReply* reply)
{
    if (reply == nullptr)
    {
        return;
    }

    if (reply->error())
    {
        qDebug() << reply->errorString();

        return;
    }

    QNetworkRequest source         = reply->request();
    QString         responseString = reply->readAll();
    QJsonDocument   jsonResponse   = QJsonDocument::fromJson(responseString.toUtf8());
    QJsonObject     jsonObject     = jsonResponse.object();

    qDebug() << jsonObject;

    if (source == weatherRequest)
    {
        WeatherData::Data data = {};

        data.temperatureUnit = jsonObject
            .take("current_units").toObject()
            .take("temperature_2m").toString();

        data.temperatureValue = jsonObject
            .take("current").toObject()
            .take("temperature_2m").toDouble();

        weatherData->handleRefresh(data);
    }
    else if (source == locationRequest)
    {
        QJsonObject result = jsonObject
            .take("results").toArray()
            .at(0).toObject();

        qDebug() << result;

        longitude = result
            .take("longitude").toDouble();

        latitude = result
            .take("latitude").toDouble();

        qDebug() << longitude << latitude;

        updateWeatherData();
    }
    else
    {
        qInfo() << "Unknown source of request";
    }
}
