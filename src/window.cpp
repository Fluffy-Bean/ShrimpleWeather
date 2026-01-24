#include <QMainWindow>

#include "window.h"

Window::Window(QWidget *parent) : QMainWindow(parent)
{
    setObjectName("Window");
}

Window::~Window()
{
}
