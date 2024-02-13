cmake_minimum_required(VERSION 3.5)

project(my_mirror VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Threads REQUIRED)
#find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    stl_reader/stl_reader.h
    builder/basebuilder.h
    builder/basebuillder.cpp
    object/object.h
    utility/ray/ray.h
    utility/ray/ray.cpp
    utility/material/material.h
    utility/material/material.cpp
    utility/exception/baseexception.h
    utility/bbox/bbox.h
    utility/bbox/bbox.cpp
    object/visibleobject/visibleobject.h
    object/invisibleobject/invisibleobject.h
    object/visibleobject/triangle/triangle.h
    object/visibleobject/triangle/triangle.cpp
    object/visibleobject/model/model.h
    object/visibleobject/model/model.cpp
    object/invisibleobject/kdtree/kdtree.h
    object/invisibleobject/kdtree/kdtree.cpp
    object/invisibleobject/camera/camera.h
    object/invisibleobject/camera/camera.cpp
    object/invisibleobject/light/light.h
    object/invisibleobject/light/light.cpp
    builder/cone/cone.cpp
    builder/cone/cone.h
    builder/cylinder/cylinder.h
    builder/cylinder/cylinder.cpp
    builder/mirror/concave/mirrorconcave.cpp
    builder/mirror/concave/mirrorconcave.h
    builder/mirror/convex/mirrorconvex.h
    builder/mirror/convex/mirrorconvex.cpp
    builder/mirror/plane/mirrorplane.cpp
    builder/mirror/plane/mirrorplane.h
    builder/prysm/penta/prysmpenta.cpp
    builder/prysm/tri/prysmtri.cpp
    builder/prysm/tri/prysmtri.h
    builder/prysm/tetra/prysmtetra.cpp
    builder/prysm/tetra/prysmtetra.h
    builder/prysm/penta/prysmpenta.h
    builder/prysm/penta/prysmpenta.cpp
    builder/pyramide/tri/pyramidetri.cpp
    builder/pyramide/tri/pyramidetri.h
    builder/pyramide/tetra/pyramidetetra.h
    builder/pyramide/tetra/pyramidetetra.cpp
    builder/pyramide/penta/pyramidepenta.h
    builder/pyramide/penta/pyramidepenta.cpp
    builder/sphere/sphere.h
    builder/sphere/sphere.cpp
    drawer/basedrawer.h
    drawer/qtdrawer.h
    drawer/qtdrawer.cpp
    factory/abstractfactory.h
    factory/qtdrawerfactory/qtdrawerfactory.h
    factory/qtdrawerfactory/qtdrawerfactory.cpp
    scene/scene.h
    scene/scene.cpp
    builder/mirror/mirror.h
    builder/mirror/mirror.cpp
    scenemanager/scenemanager.h
    scenemanager/scenemanager.cpp
    command/scenecommand.h
    command/basecommand.h
    facade/facade.cpp
    facade/facade.h
    loaddialog/loaddialog.h
    loaddialog/loaddialog.cpp
)

string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_UP)
if (${CMAKE_BUILD_TYPE_UP} STREQUAL "DEBUG")
     SET(CMAKE_BUILD_TYPE Debug)
    add_executable(my_mirror
        main_test.cpp
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

include_directories(
${PROJECT_SOURCE_DIR}/utility
${PROJECT_SOURCE_DIR}/data
)

set(SOURCE_MODELS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/stl)
set(DEST_MODELS_PATH ${CMAKE_CURRENT_BINARY_DIR}/data/stl)
set(LOAD_IMAGE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/data/gif)
set(LOAD_IMAGE_DEST_PATH ${CMAKE_CURRENT_BINARY_DIR}/data/gif)

add_compile_definitions(MODELS_FILE="${DEST_MODELS_PATH}/")
add_compile_definitions(LOAD_PATH="${CMAKE_CURRENT_BINARY_DIR}/data/gif/load.gif")
add_compile_definitions(MODELS_TYPE=".stl")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SOURCE_MODELS_PATH} ${DEST_MODELS_PATH}
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${LOAD_IMAGE_PATH} ${LOAD_IMAGE_DEST_PATH}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(my_mirror)
endif()
