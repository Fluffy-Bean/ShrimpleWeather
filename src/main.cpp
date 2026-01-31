#include <QApplication>
#include <QStyleFactory>

#include "application.h"
#include "window.h"

int main(int argc, char *argv[])
{
    Application application(argc, argv);
    Application::setStyle(QStyleFactory::create("Fusion"));

    Window window;
    window.setWindowTitle("Shrimple Weather");
    window.resize(800, 600);
    window.show();

    return Application::exec();
}
