cmake_minimum_required(VERSION 3.16)

project(AppStore VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include both Widgets and Network modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    Items.h
    Items.cpp
    Book.h
    Book.cpp
    Magazine.h
    Magazine.cpp
    StoreData.h
    StoreData.cpp
    ItemFactory.h
    ItemFactory.cpp
    BackupManager.h
    BackupManager.cpp
    AddItemWidget.h
    AddItemWidget.cpp
    PurchasedItem.h
    Transactions.h
    Transactions.cpp
    Customer.h
    Customer.cpp
    TransactionWidget.h
    TransactionWidget.cpp
    Broadcaster.h
    Broadcaster.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(AppStore
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}




        TransactionTreeModel.h
        TransactionTreeModel.cpp
        TransactionViewWidget.h
        TransactionViewWidget.cpp
        CustomerWidget.h
        CustomerWidget.cpp
    )
else()
    if(ANDROID)
        add_library(AppStore SHARED ${PROJECT_SOURCES})
    else()
        add_executable(AppStore ${PROJECT_SOURCES})
    endif()
endif()

#  Link against Qt Widgets and Network libraries
target_link_libraries(AppStore
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.AppStore)
endif()

set_target_properties(AppStore PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS AppStore
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(AppStore)
endif()
