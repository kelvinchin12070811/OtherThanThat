#include <qdesktopservices.h>
#include <qmessagebox.h>
#include "CustomWebRenderer.hpp"

CustomWebRenderer::CustomWebRenderer(QObject *parrent):
    QWebEnginePage(parrent)
{
}

bool CustomWebRenderer::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    if (type != NavigationTypeLinkClicked) return true;

    auto openExternalRequest = []()->QMessageBox::StandardButton {
        return QMessageBox::information(nullptr, "You are now leaving Google's Services",
                                   "It's seems like you are now leaving Google's Service, are you sure to continue?\n"
                                   "We will open the link in your external browser",
                                   QMessageBox::Yes, QMessageBox::No);
    };

    auto link = url.toString();
    if (link.indexOf("ad") != -1) return true;
    if (link.indexOf("google") != -1) return true;
    if (link.indexOf("youtube") != -1) return true;

    if (openExternalRequest() == QMessageBox::Yes)
        QDesktopServices::openUrl(url);
    return false;
}
