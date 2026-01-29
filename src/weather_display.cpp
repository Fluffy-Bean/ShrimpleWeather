#include "weather_display.h"

WeatherDisplay::WeatherDisplay(QWidget* parent) : QScrollArea(parent)
{
    setObjectName("WeatherDisplay");
    setWidgetResizable(true);
    setMinimumWidth(600);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    container = new QWidget(this);
    container->setObjectName("WeatherDisplayContainer");
    container->setAttribute(Qt::WA_StyledBackground, true);
    container->setAutoFillBackground(true);

    layout = new QVBoxLayout(container);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(16);

    overview = new Overview(container);
    hourly   = new Hourly(container);

    layout->addWidget(overview);
    layout->addWidget(hourly);
    layout->addStretch();

    setWidget(container);
}

WeatherDisplay::~WeatherDisplay()
{
}

void WeatherDisplay::handleRefresh(API::Response& response)
{
    overview->handleRefresh(response);
    hourly->handleRefresh(response);
}
