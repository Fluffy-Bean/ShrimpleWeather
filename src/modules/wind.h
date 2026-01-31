#pragma once

#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QString>
#include <QWidget>

#include "../api.h"

class Wind : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout> layout           = nullptr;
    QPointer<QLabel>      measurementLabel = nullptr;

public:
    Wind(QWidget* parent = nullptr);
    ~Wind();

public slots:
    void handleRefresh(API::Response& response);
};
