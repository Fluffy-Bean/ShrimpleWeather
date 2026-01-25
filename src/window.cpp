#include "window.h"
#include "side_bar.h"
#include "weather_display.h"

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

    rootLayout = new QHBoxLayout(root);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    sideBar        = new SideBar(root);
    weatherDisplay = new WeatherDisplay(root);

    rootLayout->addWidget(sideBar);
    rootLayout->addWidget(weatherDisplay);

    connect(sideBar, &SideBar::onLocationSelection, this, &Window::handleLocationSelection);
    connect(manager, &QNetworkAccessManager::finished, this, &Window::handleNetworkReply);
}

Window::~Window()
{
    delete manager;
}

void Window::handleLocationSelection(Location& location)
{
    currentLocation = location;

    QString url = QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&current=temperature_2m,rain&forecast_days=%3")
        .arg(location.latitude)
        .arg(location.longitude)
        .arg(1);

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
        Weather data = {};

        data.location        = currentLocation;
        data.temperature     = jsonObject.take("current").toObject().take("temperature_2m").toDouble();
        data.temperatureUnit = jsonObject.take("current_units").toObject().take("temperature_2m").toString();

        weatherDisplay->handleRefresh(data);
    }
    else
    {
        qInfo() << "Unknown source of request";
    }
}
