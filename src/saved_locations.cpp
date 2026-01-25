#include "saved_locations.h"

SavedLocations::SavedLocations(QWidget* parent) : QWidget(parent)
{
    setObjectName("SavedLocations");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    for (int i = 0; i < 10; ++i)
    {
        QPointer<QPushButton> button = new QPushButton(this);
        button->setFlat(true);
        button->setText("Location Button");

        locationButtons.append(button);
        layout->addWidget(button);
    }

    setLayout(layout);
}

SavedLocations::~SavedLocations()
{
    qDeleteAll(locationButtons);
    locationButtons.clear();
}

void SavedLocations::handleClick()
{
}
