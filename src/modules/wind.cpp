#include "wind.h"

Wind::Wind(QWidget* parent) : QWidget(parent)
{
    setObjectName("Wind");
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
    titleIcon->setObjectName("WindIcon");
    titleIcon->setText("air");

    QPointer<QLabel> titleLabel = new QLabel(this);
    titleLabel->setObjectName("WindLabel");
    titleLabel->setText("Wind");

    titleBarLayout->addWidget(titleIcon);
    titleBarLayout->addWidget(titleLabel);
    titleBarLayout->addStretch();

    measurementLabel = new QLabel(this);
    measurementLabel->setObjectName("WindMeasurement");
    measurementLabel->setText("0km/h");

    layout->addWidget(titleBar);
    layout->addWidget(measurementLabel);

    setLayout(layout);
}

Wind::~Wind()
{
}

void Wind::handleRefresh(API::Response& response)
{
    measurementLabel->setText(QString("%1%2").arg(response.current.windSpeed).arg(response.units.windSpeed));
}
