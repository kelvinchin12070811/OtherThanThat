#include "window/BrowserWindow.hpp"
#include <exception>
#include <QApplication>
#include <qicon.h>
#include <qmessagebox.h>
#include <qwebenginesettings.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/resources/icon.png"));
    try
    {
        {
            std::vector<QString> args;
            auto argsRaw = a.arguments();
            args.reserve(argsRaw.size());

            for (auto& itr : argsRaw)
                args.push_back(itr);

            Config::getInstance().setCmdArgs(args);
        }

        QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

        BrowserWindow w;
        w.show();

        return a.exec();
    }
    catch (const std::exception& e)
    {
        auto str = QString::fromUtf8(QByteArray(e.what()));
        QMessageBox::critical(nullptr, "Exception occur", str);
        return -1;
    }
}
