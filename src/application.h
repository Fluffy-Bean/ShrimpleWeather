#pragma once

#include <QApplication>

#include "api/open_meteo.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    static API::OpenMeteo api;

public:
    Application(int& argc, char** argv);
    ~Application();
};
