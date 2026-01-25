cmake_minimum_required(VERSION 3.19)
project(ShrimpleWeather LANGUAGES CXX)

set(CMAKE_AUTORCC ON)

find_package(Qt6 6.8
    REQUIRED COMPONENTS Core Widgets Network
)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/api.h
    src/window.h
    src/window.cpp
    src/side_bar.h
    src/side_bar.cpp
    src/search_bar.h
    src/search_bar.cpp
    src/saved_locations.h
    src/saved_locations.cpp
    src/weather_display.h
    src/weather_display.cpp
    src/modules/overview.h
    src/modules/overview.cpp
    src/modules/hourly.h
    src/modules/hourly.cpp
)

qt_add_resources(${PROJECT_NAME}
    PREFIX "/"
    FILES
        assets/fonts/Inter.ttf
        assets/fonts/MaterialSymbolsOutlined.ttf
        assets/styles/stylesheet.qss
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt::Core
    Qt::Widgets
    Qt::Network
)

install(
    TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
