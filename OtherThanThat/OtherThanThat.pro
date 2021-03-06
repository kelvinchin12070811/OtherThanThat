#-------------------------------------------------
#
# Project created by QtCreator 2018-08-02T16:56:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webenginewidgets network

TARGET = OtherThanThat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    window/BrowserWindow.cpp \
    Config.cpp \
    webview/CustomWebView.cpp \
    webview/CustomWebRenderer.cpp \
    window/ItemDownloader.cpp \
    window/AddressWindow.cpp \
    libs/pugixml/pugixml.cpp \
    webview/CustomWebRenderer.cpp \
    webview/CustomWebView.cpp \
    window/AddressWindow.cpp \
    window/BrowserWindow.cpp \
    window/ItemDownloader.cpp \
    Config.cpp \
    main.cpp \
    BookmarkFilePraser.cpp \
    window/util/FullscreenNotification.cpp \
    window/FullscreenView.cpp

HEADERS += \
    window/BrowserWindow.hpp \
    Config.hpp \
    webview/CustomWebView.hpp \
    webview/CustomWebRenderer.hpp \
    window/ItemDownloader.hpp \
    window/AddressWindow.hpp \
    libs/pugixml/pugiconfig.hpp \
    libs/pugixml/pugixml.hpp \
    webview/CustomWebRenderer.hpp \
    webview/CustomWebView.hpp \
    window/AddressWindow.hpp \
    window/BrowserWindow.hpp \
    window/ItemDownloader.hpp \
    Config.hpp \
    BookmarkFilePraser.hpp \
    window/util/FullscreenNotification.hpp \
    window/FullscreenView.hpp

RESOURCES += \
    resources.qrc

DISTFILES += \
    resource.rc

RC_FILE = resource.rc
