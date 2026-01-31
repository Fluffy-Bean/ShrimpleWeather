#include "window.h"
#include "application.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setObjectName("Window");

    {
        const int     fontID     = QFontDatabase::addApplicationFont(":/assets/fonts/MaterialSymbolsOutlined.ttf");
        const QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
    }

    {
        const int fontID         = QFontDatabase::addApplicationFont(":/assets/fonts/Inter.ttf");
        const QString fontFamily = QFontDatabase::applicationFontFamilies(fontID).at(0);
        QFont font(fontFamily);
        font.setPixelSize(13);

        setFont(font);
    }

    QFile file(":/assets/styles/stylesheet.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString style_sheet = QString(file.readAll());
        setStyleSheet(style_sheet);
    }
    else {
        qWarning() << "Failed to load stylesheet";
    }

    root = new QWidget(this);
    this->setCentralWidget(root);

    layout = new QHBoxLayout(root);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    sideBar        = new SideBar(root);
    weatherDisplay = new WeatherDisplay(root);

    layout->addWidget(sideBar);
    layout->addWidget(weatherDisplay);

    assert(connect(sideBar, &SideBar::onLocationSelection, this, &Window::handleLocationSelection));
}

Window::~Window()
{
}

void Window::handleLocationSelection(API::Location& location)
{
    currentWeather.location = location;

    Application::api.getCurrentWeather(location, [](API::Weather& weather, void* data) {
        Window* _this = static_cast<Window*>(data);

        _this->currentWeather.current = weather;
        _this->weatherDisplay->handleRefresh(_this->currentWeather);
    }, this);

    Application::api.getHourlyWeather(location, [](QList<API::Weather>& weather, void* data) {
        Window* _this = static_cast<Window*>(data);

        _this->currentWeather.hourly = weather;
        _this->weatherDisplay->handleRefresh(_this->currentWeather);
    }, this);
}
