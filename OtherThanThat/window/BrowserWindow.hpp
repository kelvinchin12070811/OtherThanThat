#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <qbytearray.h>
#include <QMainWindow>
#include <qmenu.h>
#include <qmenubar.h>
#include <qurl.h>
#include "Config.hpp"
#include "webview/CustomWebView.hpp"

class BrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget *parent = nullptr);
    BrowserWindow(const QUrl& url, bool isMainWindow = true, QWidget* parent = nullptr);

    CustomWebView* getWebView();

protected:
    void closeEvent(QCloseEvent*);

private:
    void connectObjects();
    void setupMenu();
    void setUpUi();

private slots:
    void downloadRequested(QWebEngineDownloadItem* item);
    void openExternal();
    void titleChanger(const QString& newTitle);
    void zoomFactorChecker(const QUrl&);

private:
    bool isMainWindow;
    CustomWebView* webView{ nullptr };

    QAction* aboutAction{ nullptr };
    QAction* aboutQtAction{ nullptr };
    QAction* backNavAction{ nullptr };
    QAction* closeAction{ nullptr };
    QAction* forwardNavAction{ nullptr };
    QAction* openInBrowserAction{ nullptr };
    QAction* refreshAction{ nullptr };
    QAction* showAddressAction{ nullptr };

    QByteArray prevWindowRect;
    QUrl workingUrl{ "about:blank" };
};

#endif // BROWSERWINDOW_HPP
