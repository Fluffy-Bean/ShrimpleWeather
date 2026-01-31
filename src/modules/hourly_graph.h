#pragma once

#include <QChartView>
#include <QLabel>
#include <QLayout>
#include <QLineSeries>
#include <QList>
#include <QPointer>
#include <QString>
#include <QValueAxis>
#include <QWidget>

#include "../api/open_meteo.h"

class HourlyGraph : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout> layout     = nullptr;
    QPointer<QLineSeries> lineSeries = nullptr;
    QPointer<QValueAxis>  axisX      = nullptr;
    QPointer<QValueAxis>  axisY      = nullptr;
    QPointer<QChart>      chart      = nullptr;
    QPointer<QChartView>  chartView  = nullptr;

public:
    HourlyGraph(QWidget* parent = nullptr);
    ~HourlyGraph();

public slots:
    void handleRefresh(API::Response& response);
};
