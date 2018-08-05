#include <regex>
#include <string>
#include <qdesktopservices.h>
#include <qmessagebox.h>
#include "CustomWebRenderer.hpp"

CustomWebRenderer::CustomWebRenderer(QObject *parrent):
    QWebEnginePage(parrent)
{
}

bool CustomWebRenderer::acceptNavigationRequest(const QUrl &url, NavigationType type, bool)
{
    if (type != NavigationTypeLinkClicked) return true;
    std::string targetUrl = url.toString().toUtf8().data();
    std::regex rule("^https?://\\w+\\.(google|youtube)\\.com");

    if (std::regex_search(targetUrl, rule))
        return true;

    auto openExternalRequest = QMessageBox::information(nullptr, "You are now leaving Google's Services",
                                   "It's seems like you are now leaving Google's Service, are you sure to continue?\nWe will open the link in your external browser",
                                   QMessageBox::Yes, QMessageBox::No);

    if (openExternalRequest == QMessageBox::Yes)
        QDesktopServices::openUrl(url);
    return false;
}
