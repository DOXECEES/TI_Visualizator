cmake_minimum_required(VERSION 3.5)

project(TI_Visualizator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TI_Visualizator
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ialgorithmlz.h ialgorithmlz.cpp
        lz78.h lz78.cpp
        enthropy.h enthropy.cpp
        fraction.h fraction.cpp
        treevisualizer.h treevisualizer.cpp
        binarytree.h binarytree.cpp
        fanotree.h fanotree.cpp
        lz77.h lz77.cpp
        cryptvisualizer.h cryptvisualizer.cpp
        lzfactory.h lzfactory.cpp
        lzss.h lzss.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TI_Visualizator APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TI_Visualizator SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TI_Visualizator
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TI_Visualizator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(TI_Visualizator PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TI_Visualizator
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TI_Visualizator)
endif()
