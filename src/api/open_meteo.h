#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPointer>
#include <QString>

namespace API
{
    struct Location
    {
        QString name      = "";
        double  latitude  = 0;
        double  longitude = 0;
    };

    struct Units
    {
        QString rain                = "mm";
        QString humidity            = "%";
        QString temperature         = "°C";
        QString apparentTemperature = "°C";
        QString windDirection       = "°";
        QString windSpeed           = "km/h";
    };

    struct Weather
    {
        QString time                = "";
        bool    isDay               = true;
        double  rain                = 0;
        double  humidity            = 0;
        double  temperature         = 0;
        double  apparentTemperature = 0;
        double  windDirection       = 0;
        double  windSpeed           = 0;
    };

    struct Response
    {
        Location       location = {};
        Units          units    = {};
        Weather        current  = {};
        QList<Weather> hourly   = {};
    };

    class OpenMeteo : public QObject
    {
        Q_OBJECT

    public:
        typedef void (*CurrentWeatherCallback)(Weather& weather, void* data);
        typedef void (*HourlyWeatherCallback)(QList<Weather>& weather, void* data);
        typedef void (*LocationsCallback)(QList<Location>& locations, void* data);

    private:
        enum class ResponseKind
        {
            CurrentWeather,
            HourlyWeather,
            LocationsSearch,
        };

        union ResponseCallbacks
        {
            CurrentWeatherCallback currentWeather;
            HourlyWeatherCallback  hourlyWeather;
            LocationsCallback      locations;
        };

        struct ResponseContainer
        {
            QNetworkRequest   request;
            ResponseKind      kind;
            ResponseCallbacks callbacks;
            void*             data;
        };

    private:
        QPointer<QNetworkAccessManager> manager  = nullptr;
        QList<ResponseContainer>        requests = {};

    public:
        OpenMeteo();
        ~OpenMeteo();

        void getCurrentWeather(const Location& location, CurrentWeatherCallback callback, void* data);
        void getHourlyWeather(const Location& location, HourlyWeatherCallback callback, void* data);
        void getLocationsByName(const QStringView query, const int count, LocationsCallback callback, void* data);

    private slots:
        void handleNetworkReply(QNetworkReply* reply);
    };
}
