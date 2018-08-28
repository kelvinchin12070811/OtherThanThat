#include <qwebenginesettings.h>
#include "CustomWebRenderer.hpp"
#include "CustomWebView.hpp"
#include "window/BrowserWindow.hpp"

CustomWebView::CustomWebView(QWidget* parent):
    QWebEngineView(parent)
{
    this->setPage(new CustomWebRenderer(this));
    this->settings()->setAttribute(QWebEngineSettings::FullScreenSupportEnabled, true);
}

QWebEngineView* CustomWebView::createWindow(QWebEnginePage::WebWindowType)
{
    auto window = new BrowserWindow(QUrl("about:blank"), false, nullptr);
    window->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    window->show();
    return window->getWebView();
}
