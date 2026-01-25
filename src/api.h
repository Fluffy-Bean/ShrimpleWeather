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
        QString temperature         = "°C";
        QString apparentTemperature = "°C";
        QString rain                = "mm";
    };

    struct Weather
    {
        QString  time                = "";
        bool     isDay               = true;
        double   rain                = 0;
        double   temperature         = 0;
        double   apparentTemperature = 0;
    };

    struct Response
    {
        Location       location = {};
        Units          units    = {};
        Weather        current  = {};
        QList<Weather> hourly   = {};
    };
}
