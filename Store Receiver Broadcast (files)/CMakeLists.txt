cmake_minimum_required(VERSION 3.16)

project(StoreReceiver VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------
# Find Qt Modules (Widgets + Network)
# --------------------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

# --------------------------
# Source Files
# --------------------------
set(PROJECT_SOURCES
    main.cpp
    ReceiverWindow.cpp
    ReceiverWindow.h
    UdpListener.cpp
    UdpListener.h
)

# --------------------------
# Add Executable
# --------------------------
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StoreReceiver
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(StoreReceiver ${PROJECT_SOURCES})
endif()

# --------------------------
# Link Libraries (Widgets + Network)
# --------------------------
target_link_libraries(StoreReceiver
    PRIVATE Qt${QT_VERSION_MAJOR}::Widgets
            Qt${QT_VERSION_MAJOR}::Network
)

# --------------------------
# macOS/iOS Bundle Identifier (optional)
# --------------------------
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.StoreReceiver)
endif()

# --------------------------
# Set Target Properties
# --------------------------
set_target_properties(StoreReceiver PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# --------------------------
# Installation Rules
# --------------------------
include(GNUInstallDirs)
install(TARGETS StoreReceiver
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# --------------------------
# Finalize for Qt 6
# --------------------------
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StoreReceiver)
endif()
