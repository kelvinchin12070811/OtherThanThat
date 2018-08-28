#include <qapplication.h>
#include <qdebug.h>
#include <qdesktopwidget.h>
#include <qfile.h>
#include <qdir.h>
#include <qwebengineprofile.h>
#include "Config.hpp"

const QString Config::APP_VERSION = "1.0";

Config & Config::getInstance()
{
    static Config instance;
    return instance;
}

float Config::getDPIScale()
{
    return 1.0;
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

const std::vector<QString>& Config::getCmdArgs() const
{
    return cmdArgs;
}

void Config::setCmdArgs(const std::vector<QString> &args)
{
    cmdArgs = args;
}

void Config::setCmdArgs(std::vector<QString> &&args)
{
    cmdArgs = std::move(args);
}

void Config::setCmdArgs(int argc, char **argv)
{
    cmdArgs.reserve(argc);
    for (int x = 0; x < argc; x++)
        cmdArgs.push_back(argv[x]);
}

QString Config::getAppDataLocation()
{
    return appDataLocation;
}

QString Config::getGeoFileName()
{
    return geoFileName;
}

QSize Config::adjustScale(const QSize &size)
{
    return QSize(size.width() * dpiScale, size.height() * dpiScale);
}

Config::Config()
{
    //Get desktop dpi
    auto desktopWg = QApplication::desktop();
    dpiScale= static_cast<float>(desktopWg->logicalDpiX()) / DEFAULT_DPI;

    {//Get local appdata location
        QDir cacheDir(QWebEngineProfile::defaultProfile()->cachePath());
        cacheDir.cd("../../../");
        appDataLocation = cacheDir.absolutePath();

        if(!QDir(appDataLocation + "/settings").exists())
        {
            cacheDir.mkdir("settings");
        }

        geoFileName = appDataLocation + "/settings/" + geoFileName;
    }

    //Get previous window geo
    QFile file(getGeoFileName());
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
        QFile file(getGeoFileName());
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(windowGeo);
        }
    }
}
