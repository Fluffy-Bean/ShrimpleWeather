#include "saved_locations.h"

SavedLocations::SavedLocations(QWidget* parent) : QWidget(parent)
{
    setObjectName("SavedLocations");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);

    list = new QVBoxLayout(this);
    list->setContentsMargins(0, 0, 0, 0);
    list->setSpacing(0);

    for (int i = 0; i < 10; ++i)
    {
        QPointer<QPushButton> button = new QPushButton(this);
        button->setFlat(true);
        button->setText("Location Button");

        locationButtons.append(button);
        list->addWidget(button);
    }
}

SavedLocations::~SavedLocations()
{
    locationButtons.clear();
}

void SavedLocations::handleClick()
{
}
