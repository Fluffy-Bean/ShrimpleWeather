cmake_minimum_required(VERSION 3.19)
project(ShrimpleWeather LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.8
    REQUIRED COMPONENTS Core Widgets Charts Network
)
qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
    src/application.h
    src/application.cpp
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
    src/module_section.h
    src/module_section.cpp
    src/modules/overview.h
    src/modules/overview.cpp
    src/modules/hourly.h
    src/modules/hourly.cpp
    src/modules/hourly_graph.h
    src/modules/hourly_graph.cpp
    src/modules/humidity.h
    src/modules/humidity.cpp
    src/modules/wind.h
    src/modules/wind.cpp
    src/api/open_meteo.cpp
    src/api/open_meteo.h
)

qt_add_resources(${PROJECT_NAME}
    PREFIX "/"
    FILES
        assets/fonts/Inter.ttf
        assets/fonts/MaterialSymbolsOutlined.ttf
        assets/styles/stylesheet.qss
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Charts
    Qt6::Network
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
