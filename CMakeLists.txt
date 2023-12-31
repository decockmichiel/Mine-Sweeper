cmake_minimum_required(VERSION 3.25.3)

project(MineSweeper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_PREFIX_PATH ~/Qt/6.5.3/macos)

find_package(Qt6 6.5 REQUIRED COMPONENTS
    Qml
    Quick
    Widgets
)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_resources(QT_RESOURCES src/resources.qrc)

qt_add_executable(MineSweeper
    src/main.cpp
    ${QT_RESOURCES}
)

qt_add_qml_module(MineSweeper
    URI CORE
    VERSION 1.0
    SOURCES
        src/core/include/controller.h
        src/core/include/tile_model.h
)

add_subdirectory(src)
# add_subdirectory(tests)

target_link_libraries(MineSweeper PRIVATE
    core
    Qt6::Qml
    Qt6::Quick
    Qt6::Widgets
)
