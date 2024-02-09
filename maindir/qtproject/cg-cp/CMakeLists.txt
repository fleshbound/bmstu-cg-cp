cmake_minimum_required(VERSION 3.5)

project(my_mirror VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    stl_reader/stl_reader.h
    builder/basebuilder.h
    object/object.h
    utility/ray/ray.h
    utility/ray/ray.cpp
    utility/material/material.h
    utility/material/material.cpp
)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UP)
if (${CMAKE_BUILD_TYPE_UP} STREQUAL "DEBUG")
     SET(CMAKE_BUILD_TYPE Debug)
    add_executable(my_mirror
        main.cpp
        ${PROJECT_SOURCES})
else()
    add_executable(my_mirror
        main_release.cpp
        ${PROJECT_SOURCES})
endif()

target_link_libraries(my_mirror PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    TBB::tbb
    Threads::Threads
)

set_target_properties(my_mirror PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(my_mirror)
endif()
