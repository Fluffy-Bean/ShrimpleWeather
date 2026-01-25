#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QLayout>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPointer>
#include <QWidget>

#include "api.h"
#include "saved_locations.h"
#include "search_bar.h"

class SideBar : public QWidget
{
    Q_OBJECT

private:
    QPointer<QNetworkAccessManager> manager        = nullptr;
    QNetworkRequest                 locationReq    = {};

    QPointer<QVBoxLayout>           layout         = nullptr;
    QPointer<SearchBar>             searchBar      = nullptr;
    QPointer<SavedLocations>        savedLocations = nullptr;

public:
    SideBar(QWidget* parent = nullptr);
    ~SideBar();

private slots:
    void handleSearch(QStringView query);
    void handleNetworkReply(QNetworkReply* reply);

signals:
    void onLocationSelection(API::Location& location);
};
