#pragma once

#include <QString>

struct Location
{
    QString name      = "";
    double  latitude  = 0;
    double  longitude = 0;
};

struct Weather
{
    Location location        = {};
    double   temperature     = 0;
    QString  temperatureUnit = "";
};
