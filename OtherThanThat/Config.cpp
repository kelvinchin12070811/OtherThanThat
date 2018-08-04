#include <qapplication.h>
#include <qdesktopwidget.h>
#include "Config.hpp"

Config & Config::getInstance()
{
    static Config instance;
    return instance;
}

float Config::getDPIScale()
{
    return dpiScale;
}

Config::Config()
{
    auto desktopWg = QApplication::desktop();
    dpiScale= static_cast<float>(desktopWg->logicalDpiX()) / DEFAULT_DPI;
}
