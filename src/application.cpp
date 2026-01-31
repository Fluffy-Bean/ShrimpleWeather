#include "application.h"

API::OpenMeteo Application::api = API::OpenMeteo();

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
}

Application::~Application()
{
}
