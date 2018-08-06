#include "window/BrowserWindow.hpp"
#include <QApplication>
#include <qwebenginesettings.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    BrowserWindow w;
    w.show();

    return a.exec();
}
