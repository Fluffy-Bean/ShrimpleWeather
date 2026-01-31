#pragma once

#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QString>
#include <QWidget>

#include "../api/open_meteo.h"

class Overview : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout> layout    = nullptr;
    QPointer<QLabel>      townLabel = nullptr;
    QPointer<QLabel>      tempLabel = nullptr;

public:
    Overview(QWidget* parent = nullptr);
    ~Overview();

public slots:
    void handleRefresh(API::Response& response);
};
