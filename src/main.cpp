#include <QApplication>
#include <QStyleFactory>

#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    Window window;
    window.setWindowTitle("Shrimple Weather");
    window.resize(800, 600);
    window.show();

    return QApplication::exec();
}
