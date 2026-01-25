#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setObjectName("Window");

    manager = new QNetworkAccessManager();

    {
        const int     fontID     = QFontDatabase::addApplicationFont(":/assets/fonts/MaterialSymbolsOutlined.ttf");
        const QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
    }

    {
        const int fontID         = QFontDatabase::addApplicationFont(":/assets/fonts/Inter.ttf");
        const QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
        QFont font(fontFamily);
        font.setPixelSize(13);

        setFont(font);
    }

    QFile file(":/assets/styles/stylesheet.qss");
    file.open(QFile::ReadOnly);

    QString style_sheet = QString(file.readAll());
    setStyleSheet(style_sheet);

    root = new QWidget(this);
    this->setCentralWidget(root);

    layout = new QHBoxLayout(root);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    sideBar        = new SideBar(root);
    weatherDisplay = new WeatherDisplay(root);

    layout->addWidget(sideBar);
    layout->addWidget(weatherDisplay);

    connect(sideBar, &SideBar::onLocationSelection, this, &Window::handleLocationSelection);
    connect(manager, &QNetworkAccessManager::finished, this, &Window::handleNetworkReply);
}

Window::~Window()
{
    delete manager;
}

void Window::handleLocationSelection(API::Location& location)
{
    currentLocation = location;

    QString url = QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&hourly=temperature_2m,apparent_temperature,rain&current=temperature_2m,rain,apparent_temperature,is_day")
        .arg(location.latitude)
        .arg(location.longitude);

    weatherReq.setUrl(QUrl(url));

    manager->get(weatherReq);
}

void Window::handleNetworkReply(QNetworkReply* reply)
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

    if (source == weatherReq)
    {
        API::Response response = {};

        response.location = currentLocation;

        QJsonObject units                  = jsonObject.take("current_units").toObject();
        response.units.temperature         = units.take("temperature_2m").toString();
        response.units.apparentTemperature = units.take("apparent_temperature").toString();
        response.units.rain                = units.take("rain").toString();

        QJsonObject current                  = jsonObject.take("current").toObject();
        response.current.time                = current.take("time").toString();
        response.current.isDay               = current.take("is_day").toInt() == 1;
        response.current.temperature         = current.take("temperature_2m").toDouble();
        response.current.apparentTemperature = current.take("apparent_temperature").toDouble();
        response.current.rain                = current.take("rain").toDouble();

        QJsonObject hourly                    = jsonObject.take("hourly").toObject();
        QJsonArray  hourlyTime                = hourly.take("time").toArray();
        QJsonArray  hourlyTemperature         = hourly.take("temperature_2m").toArray();
        QJsonArray  hourlyApparentTemperature = hourly.take("apparent_temperature").toArray();
        QJsonArray  hourlyRain                = hourly.take("rain").toArray();

        for (int i = 0; i < hourlyTime.size(); ++i)
        {
            API::Weather weather = {};

            weather.time                = hourlyTime.at(i).toString();
            weather.temperature         = hourlyTemperature.at(i).toDouble();
            weather.apparentTemperature = hourlyApparentTemperature.at(i).toDouble();
            weather.rain                = hourlyRain.at(i).toDouble();

            response.hourly.append(weather);
        }

        weatherDisplay->handleRefresh(response);
    }
    else
    {
        qInfo() << "Unknown source of request";
    }
}
