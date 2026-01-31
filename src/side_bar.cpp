#include "side_bar.h"

SideBar::SideBar(QWidget* parent) : QWidget(parent)
{
    setObjectName("SideBar");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setFixedWidth(320);

    manager = new QNetworkAccessManager();

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    searchBar = new SearchBar(this);
    savedLocations = new SavedLocations(this);

    layout->addWidget(searchBar);
    layout->addWidget(savedLocations);

    connect(searchBar, &SearchBar::onSearch, this, &SideBar::handleSearch);
    connect(manager, &QNetworkAccessManager::finished, this, &SideBar::handleNetworkReply);

    setLayout(layout);
}

SideBar::~SideBar()
{
}

void SideBar::handleSearch(QStringView query)
{
    qDebug() << "Search query:" << query;

    QString url = QString("https://geocoding-api.open-meteo.com/v1/search?name=%1&count=%2")
        .arg(query)
        .arg(1);

    locationReq.setUrl(QUrl(url));

    manager->get(locationReq);
}

void SideBar::handleNetworkReply(QNetworkReply* reply)
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

    if (source == locationReq)
    {
        QJsonObject result = jsonObject.take("results").toArray().at(0).toObject();

        API::Location location = {};

        location.name      = result.take("name").toString();
        location.longitude = result.take("longitude").toDouble();
        location.latitude  = result.take("latitude").toDouble();

        emit onLocationSelection(location);
    }
    else
    {
        qInfo() << "Unknown source of request";
    }
}
