#include "CustomWebView.hpp"
#include "window/BrowserWindow.hpp"

CustomWebView::CustomWebView(QWidget* parent):
    QWebEngineView(parent)
{
}

QWebEngineView* CustomWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    auto window = new BrowserWindow(QUrl("about:blank"), false, nullptr);
    window->setAttribute(Qt::WidgetAttribute::WA_DeleteOnClose);
    window->show();
    return window->getWebView();
}
