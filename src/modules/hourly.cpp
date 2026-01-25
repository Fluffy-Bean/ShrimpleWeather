#include "hourly.h"

Hourly::Hourly(QWidget* parent) : QWidget(parent)
{
    setObjectName("Hourly");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setMaximumWidth(600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // scroll = new QScrollArea(this);
    // scroll->setFixedHeight(400);
    // scroll->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    // scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    // scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    list = new QVBoxLayout(this);
    list->setContentsMargins(16, 16, 16, 16);
    list->setSpacing(8);

    // scroll->setLayout(list);
}

Hourly::~Hourly()
{
    qDeleteAll(labels);
    labels.clear();
}

void Hourly::handleRefresh(API::Response& response)
{
    qDeleteAll(labels);
    labels.clear();

    for (int i = 0; i < response.hourly.size(); ++i)
    {
        QString text = QString("%1 - %2 - %3")
            .arg(response.hourly.at(i).time)
            .arg(response.hourly.at(i).temperature)
            .arg(response.hourly.at(i).rain);

        QLabel* label = new QLabel(this);
        label->setText(text);

        labels.append(label);
        list->addWidget(label);
    }
}
