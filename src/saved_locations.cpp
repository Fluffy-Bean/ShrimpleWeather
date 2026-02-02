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
    layout->setContentsMargins(0, 16, 0, 16);
    layout->setSpacing(0);

    QList<QString> locations = {
        "London",
        "Oslo",
        "Berlin",
        "Zurich",
        "Warsaw",
        "Paris",
    };

    for (int i = 0; i < locations.size(); ++i)
    {
        QPointer<QPushButton> button = makeLocationButton(this, locations.at(i));
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

QPointer<QPushButton> SavedLocations::makeLocationButton(QWidget* parent, const QString& name)
{
    QPointer<QPushButton> button = new QPushButton(parent);
    button->setObjectName("SavedLocationsButton");
    button->setFlat(true);

    QPointer<QWidget>     root   = new QWidget(button);
    QPointer<QHBoxLayout> layout = new QHBoxLayout(button);
    layout->setContentsMargins(16, 0, 16, 0);
    layout->setSpacing(8);
    layout->setAlignment(Qt::AlignLeft);

    {
        QPointer<QLabel> label = new QLabel(root);
        label->setObjectName("SavedLocationsButtonIcon");
        label->setText("weather_hail");
        layout->addWidget(label);
    }

    {
        QPointer<QLabel> label = new QLabel(root);
        label->setObjectName("SavedLocationsButtonName");
        label->setText(name);
        layout->addWidget(label);
    }

    layout->addStretch();

    assert(connect(button, &QPushButton::clicked, [=]() {
        emit onLocationSelect(name);
    }));

    return button;
}

