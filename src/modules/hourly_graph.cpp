#include "hourly_graph.h"

HourlyGraph::HourlyGraph(QWidget* parent) : QWidget(parent)
{
    setObjectName("HourlyGraph");
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setFixedHeight(300);

    layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    lineSeries = new QLineSeries(this);
    lineSeries->clear();
    lineSeries->setVisible(true);

    axisX = new QValueAxis();
    axisX->setRange(0, 0);
    axisX->setTickCount(10);
    axisX->setLabelFormat("%d");

    axisY = new QValueAxis();
    axisY->setRange(0, 0);
    axisY->setTickCount(1);
    axisY->setLabelFormat("%.2f");

    chart = new QChart();
    chart->addSeries(lineSeries);
    chart->setPlotAreaBackgroundVisible(true);
    chart->legend()->hide();

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    lineSeries->attachAxis(axisX);
    lineSeries->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}

HourlyGraph::~HourlyGraph()
{
}

void HourlyGraph::handleRefresh(API::Response& response)
{
    lineSeries->clear();

    double min =  INFINITY;
    double max = -INFINITY;
    for (int i = 0; i < response.hourly.size(); ++i)
    {
        double value = response.hourly.at(i).rain;

        if (value < min)
        {
            min = value;
        }
        if (value > max)
        {
            max = value;
        }

        lineSeries->append(i, value);
    }

    axisX->setRange(0, response.hourly.size());
    axisY->setRange(min, max);

    chartView->repaint();
}
