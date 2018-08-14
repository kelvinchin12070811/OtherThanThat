#include "window/BrowserWindow.hpp"
#include <QApplication>
#include <qicon.h>
#include <qwebenginesettings.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/icon.png"));

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    BrowserWindow w;
    w.show();

    return a.exec();
}
