#pragma once

#include <QList>
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
}
