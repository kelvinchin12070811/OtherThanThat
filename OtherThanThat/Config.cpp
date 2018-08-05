#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qfile.h>
#include <qdebug.h>
#include "Config.hpp"

const QString Config::APP_VERSION = "1.0";
const QString Config::GEO_FILE_NAME = "win_geo.dat";

Config & Config::getInstance()
{
    static Config instance;
    return instance;
}

float Config::getDPIScale()
{
    return dpiScale;
}

const QByteArray& Config::getWindowGeo() const
{
    return windowGeo;
}

void Config::setWindowGeo(const QByteArray &value)
{
    if (value == windowGeo) return;
    windowGeo = value;
    isWindowGeoChanged = true;
}

Config::Config()
{
    //Get desktop dpi
    auto desktopWg = QApplication::desktop();
    dpiScale= static_cast<float>(desktopWg->logicalDpiX()) / DEFAULT_DPI;

    //Get previous window geo
    QFile file(Config::GEO_FILE_NAME);
    if (file.open(QIODevice::ReadOnly))
    {
        windowGeo = file.readAll();
    }
}

Config::~Config()
{
    //Save current window geo
    if (isWindowGeoChanged)
    {
        QFile file(Config::GEO_FILE_NAME);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(windowGeo);
        }
    }
}
