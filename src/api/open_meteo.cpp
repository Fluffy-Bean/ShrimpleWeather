#include "open_meteo.h"

using namespace API;

OpenMeteo::OpenMeteo()
{
    manager = new QNetworkAccessManager();

    assert(connect(manager, &QNetworkAccessManager::finished, this, &OpenMeteo::handleNetworkReply));
}

OpenMeteo::~OpenMeteo()
{
    requests.clear();
    delete manager;
}

void OpenMeteo::getCurrentWeather(const Location& location, CurrentWeatherCallback callback, void* data)
{
    QList<QString> fields = {
        "is_day",
        "rain",
        "temperature_2m",
        "apparent_temperature",
        "relative_humidity_2m",
        "wind_direction_10m",
        "wind_speed_10m",
    };

    QString url = QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&current=%3")
        .arg(location.latitude)
        .arg(location.longitude)
        .arg(fields.join(","));

    QNetworkRequest request = {};
    request.setUrl(QUrl(url));

    ResponseContainer response        = {};
    response.request                  = request;
    response.kind                     = ResponseKind::CurrentWeather;
    response.callbacks.currentWeather = callback;
    response.data                     = data;

    requests.emplace_back(response);

    manager->get(request);
}

void OpenMeteo::getHourlyWeather(const Location& location, HourlyWeatherCallback callback, void* data)
{
    QList<QString> fields = {
        "rain",
        "temperature_2m",
        "apparent_temperature",
    };

    QString url = QString("https://api.open-meteo.com/v1/forecast?latitude=%1&longitude=%2&hourly=%3")
        .arg(location.latitude)
        .arg(location.longitude)
        .arg(fields.join(","));

    QNetworkRequest request = {};
    request.setUrl(QUrl(url));

    ResponseContainer response       = {};
    response.request                 = request;
    response.kind                    = ResponseKind::HourlyWeather;
    response.callbacks.hourlyWeather = callback;
    response.data                    = data;

    requests.emplace_back(response);

    manager->get(request);
}

void OpenMeteo::getLocationsByName(const QStringView query, const int count, LocationsCallback callback, void* data)
{
    QString url = QString("https://geocoding-api.open-meteo.com/v1/search?name=%1&count=%2")
        .arg(query)
        .arg(count);

    QNetworkRequest request = {};
    request.setUrl(QUrl(url));

    ResponseContainer response   = {};
    response.request             = request;
    response.kind                = ResponseKind::LocationsSearch;
    response.callbacks.locations = callback;
    response.data                = data;

    requests.emplace_back(response);

    manager->get(request);
}

void OpenMeteo::handleNetworkReply(QNetworkReply* reply)
{
    reply->deleteLater();

    ResponseContainer response = {};
    for (int i = 0; i < requests.size(); ++i)
    {
        if (requests.at(i).request == reply->request())
        {
            response = requests.takeAt(i);

            break;
        }
    }
    if (response.request != reply->request())
    {
        return;
    }

    if (reply->error())
    {
        qDebug() << reply->errorString();

        return;
    }

    const QString     replyString = reply->readAll();
    const QJsonObject replyObject = QJsonDocument::fromJson(replyString.toUtf8()).object();

    switch (response.kind) {
    case ResponseKind::CurrentWeather: {
        if (response.callbacks.currentWeather == nullptr)
        {
            return;
        }

        const QJsonObject currentObject = replyObject.value("current").toObject();

        Weather current             = {};
        current.time                = currentObject.value("time").toString();
        current.isDay               = currentObject.value("is_day").toInt() == 1;
        current.rain                = currentObject.value("rain").toDouble();
        current.humidity            = currentObject.value("relative_humidity_2m").toDouble();
        current.temperature         = currentObject.value("temperature_2m").toDouble();
        current.apparentTemperature = currentObject.value("apparent_temperature").toDouble();
        current.windDirection       = currentObject.value("wind_direction_10m").toDouble();
        current.windSpeed           = currentObject.value("wind_speed_10m").toDouble();

        (*response.callbacks.currentWeather)(current, response.data);
    } break;

    case ResponseKind::HourlyWeather: {
        if (response.callbacks.hourlyWeather == nullptr)
        {
            return;
        }

        const QJsonObject hourlyObject                    = replyObject.value("hourly").toObject();
        const QJsonArray  hourlyObjectTime                = hourlyObject.value("time").toArray();
        const QJsonArray  hourlyObjectTemperature         = hourlyObject.value("temperature_2m").toArray();
        const QJsonArray  hourlyObjectApparentTemperature = hourlyObject.value("apparent_temperature").toArray();
        const QJsonArray  hourlyObjectRain                = hourlyObject.value("rain").toArray();

        QList<Weather> hourly = {};
        for (int i = 0; i < hourlyObjectTime.size(); ++i)
        {
            Weather current = {};

            current.time                = hourlyObjectTime.at(i).toString();
            current.rain                = hourlyObjectRain.at(i).toDouble();
            current.temperature         = hourlyObjectTemperature.at(i).toDouble();
            current.apparentTemperature = hourlyObjectApparentTemperature.at(i).toDouble();

            hourly.append(current);
        }

        (*response.callbacks.hourlyWeather)(hourly, response.data);
    } break;

    case ResponseKind::LocationsSearch: {
        if (response.callbacks.locations == nullptr)
        {
            return;
        }

        QJsonArray results = replyObject.value("results").toArray();

        QList<Location> locations = {};
        for (int i = 0; i < results.size(); ++i)
        {
            Location location = {};

            QJsonObject result = results.at(i).toObject();
            location.name      = result.value("name").toString();
            location.longitude = result.value("longitude").toDouble();
            location.latitude  = result.value("latitude").toDouble();

            locations.append(location);
        }

        (*response.callbacks.locations)(locations, response.data);
    } break;
    }
}
