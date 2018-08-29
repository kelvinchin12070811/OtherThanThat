#include <vector>
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

    std::vector<QString> filters = {
      "ad",
      "google",
      "youtube"
    };

    {
        auto filterChecker = [link, filters]()->bool {
          for (auto& itr : filters)
          {
              if (link.indexOf(itr) > -1)
                  return true;
          }
        };

        if (filterChecker()) return true;
    }
    if (openExternalRequest() == QMessageBox::Yes)
        QDesktopServices::openUrl(url);
    return false;
}
