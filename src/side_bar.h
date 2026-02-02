#pragma once

#include <QLayout>
#include <QPointer>
#include <QWidget>

#include "saved_locations.h"
#include "search_bar.h"
#include "api/open_meteo.h"
#include "application.h"

class SideBar : public QWidget
{
    Q_OBJECT

private:
    QPointer<QVBoxLayout>    layout         = nullptr;
    QPointer<SearchBar>      searchBar      = nullptr;
    QPointer<SavedLocations> savedLocations = nullptr;
    int                      onLocationSelect;

public:
    SideBar(QWidget* parent = nullptr);
    ~SideBar();

private slots:
    void handleSearch(QStringView query);

signals:
    void onLocationSelection(API::Location& location);
};
