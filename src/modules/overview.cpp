#include "overview.h"

Overview::Overview(QWidget* parent) : QWidget(parent)
{
    setObjectName("Overview");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setMaximumWidth(600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);

    townLabel = new QLabel(this);
    townLabel->setObjectName("Town");
    townLabel->setText("TOWN");

    tempLabel = new QLabel(this);
    tempLabel->setObjectName("Temperature");
    tempLabel->setText("TEMPERATURE");

    layout->addWidget(townLabel);
    layout->addWidget(tempLabel);

    setLayout(layout);
}

Overview::~Overview()
{
}

void Overview::handleRefresh(API::Response& response)
{
    townLabel->setText(response.location.name);
    tempLabel->setText(QString("%1 %2").arg(response.current.temperature).arg(response.units.temperature));
}
