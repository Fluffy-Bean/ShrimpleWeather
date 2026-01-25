#pragma once

#include <QLabel>
#include <QLayout>
#include <QPointer>
#include <QString>
#include <QWidget>

#include "../api.h"

class Overview : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout> list      = nullptr;
    QPointer<QLabel>      townLabel = nullptr;
    QPointer<QLabel>      tempLabel = nullptr;

public:
    Overview(QWidget* parent = nullptr);
    ~Overview();

public slots:
    void handleRefresh(API::Response& response);
};
