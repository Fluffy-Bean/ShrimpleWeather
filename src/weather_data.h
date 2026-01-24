#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>

class WeatherData : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout* layout           = nullptr;
    QLabel*      temperatureLabel = nullptr;

public:
    struct Data
    {
        double  temperatureValue = 0;
        QString temperatureUnit  = "";
    };

public:
    WeatherData(QWidget* parent = nullptr);
    ~WeatherData();

public slots:
    void handleRefresh(Data data);
};
