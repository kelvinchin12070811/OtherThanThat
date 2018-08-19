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
    void cmdLineChecker();
    void connectObjects();
    void setupMenu();
    void setUpUi();

private slots:
    void downloadRequested(QWebEngineDownloadItem* item);
    void loadStarted();
    void loadFinished();
    void openBookmark();
    void openExternal();
    void saveBookmark();
    void savePDF();
    void titleChanger(const QString& newTitle);
    void zoomFactorChecker(const QUrl&);

private:
    bool isMainWindow;
    bool loaded{ true };
    CustomWebView* webView{ nullptr };

    QAction* aboutAction{ nullptr };
    QAction* aboutQtAction{ nullptr };
    QAction* backNavAction{ nullptr };
    QAction* closeAction{ nullptr };
    QAction* forwardNavAction{ nullptr };
    QAction* openBookmarkAction{ nullptr };
    QAction* openInBrowserAction{ nullptr };
    QAction* refreshAction{ nullptr };
    QAction* saveBookmarkAction{ nullptr };
    QAction* savePDFAction{ nullptr };
    QAction* showAddressAction{ nullptr };

    QByteArray prevWindowRect;
    QString webTitle{ "about-blank" };
    QUrl workingUrl{ "about:blank" };
};

#endif // BROWSERWINDOW_HPP
