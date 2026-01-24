#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

#include "weather_data.h"

WeatherData::WeatherData(QWidget* parent) : QWidget(parent)
{
    setObjectName("WeatherData");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setMinimumHeight(400);

    layout = new QHBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(32, 32, 32, 32);
    layout->setSpacing(16);

    temperatureLabel = new QLabel(this);

    layout->addWidget(temperatureLabel);
}

WeatherData::~WeatherData()
{
}

void WeatherData::handleRefresh(Data data)
{
    QString temperatureText = QString("Current Temperature: %1%2")
        .arg(data.temperatureValue)
        .arg(data.temperatureUnit);

    temperatureLabel->setText(temperatureText);
}
