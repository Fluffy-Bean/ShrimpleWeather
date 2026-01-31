#include "saved_locations.h"

SavedLocations::SavedLocations(QWidget* parent) : QScrollArea(parent)
{
    setObjectName("SavedLocations");
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(true);

    QPointer<QWidget> container = new QWidget(this);
    container->setObjectName("WeatherDisplayContainer");
    container->setAttribute(Qt::WA_StyledBackground, true);
    container->setAutoFillBackground(true);

    QPointer<QVBoxLayout> layout = new QVBoxLayout(container);
    layout->setContentsMargins(16, 16, 16, 16);
    layout->setSpacing(0);

    for (int i = 0; i < 10; ++i)
    {
        QPointer<QPushButton> button = new QPushButton(container);
        button->setFlat(true);
        button->setText("Location Button");

        locationButtons.append(button);
        layout->addWidget(button);
    }

    layout->addStretch();

    setWidget(container);
}

SavedLocations::~SavedLocations()
{
    qDeleteAll(locationButtons);
    locationButtons.clear();
}

void SavedLocations::handleClick()
{
}
