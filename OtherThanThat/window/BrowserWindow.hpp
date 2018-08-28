#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <memory>
#include <qbytearray.h>
#include <QMainWindow>
#include <qmenu.h>
#include <qmenubar.h>
#include <qpointer.h>
#include <qurl.h>
#include <qwebenginefullscreenrequest.h>
#include "Config.hpp"
#include "webview/CustomWebView.hpp"
#include "window/FullScreenView.hpp"

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
    void cmdLineChecker();
    void connectObjects();
    void setupMenu();
    void setUpUi();

private slots:
    void downloadRequested(QWebEngineDownloadItem* item);
    void fullScreenRequested(QWebEngineFullScreenRequest request);
    void loadStarted();
    void loadFinished();
    void openBookmark();
    void openExternal();
    void saveBookmark();
    void savePDF();
    void titleChanger(const QString& newTitle);
    void zoomFactorChecker(const QUrl& url);

private:
    bool isMainWindow;
    bool loaded{ true };
    QPointer<CustomWebView> webView{ nullptr };

    QPointer<QAction> aboutAction{ nullptr };
    QPointer<QAction> aboutQtAction{ nullptr };
    QPointer<QAction> backNavAction{ nullptr };
    QPointer<QAction> closeAction{ nullptr };
    QPointer<QAction> forwardNavAction{ nullptr };
    QPointer<QAction> openBookmarkAction{ nullptr };
    QPointer<QAction> openCacheLocation{ nullptr };
    QPointer<QAction> openInBrowserAction{ nullptr };
    QPointer<QAction> refreshAction{ nullptr };
    QPointer<QAction> saveBookmarkAction{ nullptr };
    QPointer<QAction> savePDFAction{ nullptr };
    QPointer<QAction> showAddressAction{ nullptr };

    std::unique_ptr<FullscreenView> fsViewer{ nullptr };

    QByteArray prevWindowRect;
    QString webTitle{ "browser about blank" };
    QUrl workingUrl{ "about:blank" };
};

#endif // BROWSERWINDOW_HPP
