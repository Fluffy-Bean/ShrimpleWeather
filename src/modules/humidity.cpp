#include "humidity.h"

Humidity::Humidity(QWidget* parent) : QWidget(parent)
{
    setObjectName("Humidity");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(8);

    QPointer<QWidget>     titleBar       = new QWidget(this);
    QPointer<QHBoxLayout> titleBarLayout = new QHBoxLayout(titleBar);
    titleBarLayout->setContentsMargins(0, 0, 0, 0);
    titleBarLayout->setSpacing(8);

    QPointer<QLabel> titleIcon = new QLabel(this);
    titleIcon->setObjectName("HumidityIcon");
    titleIcon->setText("humidity_percentage");

    QPointer<QLabel> titleLabel = new QLabel(this);
    titleLabel->setObjectName("HumidityLabel");
    titleLabel->setText("Humidity");

    titleBarLayout->addWidget(titleIcon);
    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();

    measurementLabel = new QLabel(this);
    measurementLabel->setObjectName("HumidityMeasurement");
    measurementLabel->setText("00%");

    layout->addWidget(titleBar);
    layout->addWidget(measurementLabel);

    setLayout(layout);
}

Humidity::~Humidity()
{
}

void Humidity::handleRefresh(API::Response& response)
{
    measurementLabel->setText(QString("%1%2").arg(response.current.humidity).arg(response.units.humidity));
}
