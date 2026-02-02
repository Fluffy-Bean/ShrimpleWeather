#include "side_bar.h"

SideBar::SideBar(QWidget* parent) : QWidget(parent)
{
    setObjectName("SideBar");
    setAttribute(Qt::WA_StyledBackground, true);
    setAutoFillBackground(true);
    setFixedWidth(320);

    layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 1, 0); // 1px to avoid border
    layout->setSpacing(0);

    searchBar = new SearchBar(this);
    savedLocations = new SavedLocations(this);

    layout->addWidget(searchBar);
    layout->addWidget(savedLocations);

    setLayout(layout);

    assert(connect(searchBar, &SearchBar::onSearch, this, &SideBar::handleSearch));
    assert(connect(savedLocations, &SavedLocations::onLocationSelect, this, &SideBar::handleSearch));
}

SideBar::~SideBar()
{
}

void SideBar::handleSearch(QStringView query)
{
    Application::api.getLocationsByName(query, 1, [](QList<API::Location>& locations, void* data) {
        SideBar* _this = static_cast<SideBar*>(data);

        API::Location location = locations.at(0);

        emit _this->onLocationSelection(location);
    }, this);
}
