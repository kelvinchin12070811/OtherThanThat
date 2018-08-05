#include "CustomWebRenderer.hpp"

CustomWebRenderer::CustomWebRenderer(QObject *parrent):
    QWebEnginePage(parrent)
{
}

bool CustomWebRenderer::acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame)
{
    return QWebEnginePage::acceptNavigationRequest(url, type, isMainFrame);
}
