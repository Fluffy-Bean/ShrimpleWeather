#include "weather_display.h"

#include "module_section.h"

WeatherDisplay::WeatherDisplay(QWidget* parent) : QScrollArea(parent)
{
    setObjectName("WeatherDisplay");
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWidgetResizable(true);
    setMinimumWidth(600);

    container = new QWidget(this);
    container->setObjectName("WeatherDisplayContainer");
    container->setAttribute(Qt::WA_StyledBackground, true);
    container->setAutoFillBackground(true);

    layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(16);

    {
        overview = new Overview(container);

        QPointer<ModuleSection> section = new ModuleSection(container);
        section->addWidget(overview);

        layout->addWidget(section);
    }

    {
        hourlyGraph = new HourlyGraph(container);

        QPointer<ModuleSection> section = new ModuleSection(container);
        section->addWidget(hourlyGraph);

        layout->addWidget(section);
    }

    {
        humidity    = new Humidity(container);
        wind        = new Wind(container);

        QPointer<ModuleSection> section = new ModuleSection(container);
        section->addWidget(humidity);
        section->addWidget(wind);

        layout->addWidget(section);
    }

    layout->addStretch();

    setWidget(container);
}

WeatherDisplay::~WeatherDisplay()
{
}

void WeatherDisplay::handleRefresh(API::Response& response)
{
    overview->handleRefresh(response);
    hourlyGraph->handleRefresh(response);
    humidity->handleRefresh(response);
    wind->handleRefresh(response);
}
