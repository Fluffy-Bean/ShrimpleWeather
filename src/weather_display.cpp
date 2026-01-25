#include "weather_display.h"

WeatherDisplay::WeatherDisplay(QWidget* parent) : QWidget(parent)
{
    setObjectName("WeatherDisplay");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setMinimumWidth(600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignHCenter);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(16);

    overview = new Overview(this);
    hourly   = new Hourly(this);

    layout->addWidget(overview);
    layout->addWidget(hourly);
    layout->addStretch();
}

WeatherDisplay::~WeatherDisplay()
{
}

void WeatherDisplay::handleRefresh(API::Response& response)
{
    overview->handleRefresh(response);
    hourly->handleRefresh(response);
}
