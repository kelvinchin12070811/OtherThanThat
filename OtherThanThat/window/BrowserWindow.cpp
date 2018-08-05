#include <qdesktopservices.h>
#include <qfile.h>
#include <qmessagebox.h>
#include <qwebenginedownloaditem.h>
#include <qwebengineprofile.h>
#include "BrowserWindow.hpp"

BrowserWindow::BrowserWindow(QWidget *parent) :
    BrowserWindow(QUrl("https://accounts.google.com/signin/v2/identifier?service=wise&passive=true&continue=http%3A%2F%2Fdrive.google.com%2F%3Futm_source%3Den_US&utm_medium=button&utm_campaign=web&utm_content=gotodrive&usp=gtd&ltmpl=drive&flowName=GlifWebSignIn&flowEntry=ServiceLogin"),
                  true, parent)
{
}

BrowserWindow::BrowserWindow(const QUrl &url, bool isMainWindow, QWidget *parent):
    workingUrl(url), isMainWindow(isMainWindow), QMainWindow(parent)
{
    setUpUi();
    connectObjects();
}

CustomWebView* BrowserWindow::getWebView()
{
    return webView;
}

void BrowserWindow::closeEvent(QCloseEvent *)
{
    //Save current geometry
    Config::getInstance().setWindowGeo(this->saveGeometry());
}

void BrowserWindow::connectObjects()
{
    //Actions Signals
    connect(aboutAction, &QAction::triggered, [&](){
        QMessageBox::about(this, "About OtherThanThat v" + Config::APP_VERSION,
                           "OtherThanThat is an unofficial Google Drive Client by Kelvin Chin");
    });
    connect(aboutQtAction, &QAction::triggered, [&](){
        QMessageBox::aboutQt(this, QString("About Qt v") + qVersion());
    });
    connect(closeAction, &QAction::triggered, [&](){ this->close(); });
    connect(openInBrowserAction, &QAction::triggered, this, &BrowserWindow::openExternal);

    //Widgets signals
    connect(webView, &CustomWebView::titleChanged, this, &BrowserWindow::titleChanger);
    connect(webView, &CustomWebView::urlChanged, this, &BrowserWindow::zoomFactorChecker);
    connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested, this, &BrowserWindow::downloadRequested);
}

void BrowserWindow::setupMenu()
{
    {//File menu
        auto fileMenu = this->menuBar()->addMenu("&File");

        closeAction = new QAction("Close", this);
        openInBrowserAction = new QAction("Open in browser", this);

        openInBrowserAction->setToolTip("Open this page in browser");

        fileMenu->addAction(openInBrowserAction);
        fileMenu->addSeparator();
        fileMenu->addAction(closeAction);
    }
    {//Help menu
        auto helpMenu = this->menuBar()->addMenu("&About");

        aboutAction = new QAction("About", this);
        aboutQtAction = new QAction("About Qt", this);

        helpMenu->addAction(aboutAction);
        helpMenu->addAction(aboutQtAction);
    }
}

void BrowserWindow::setUpUi()
{
    this->setWindowTitle("OtherThanThat, An Unofficial Google Drive Client");
    this->setMinimumWidth(800 * Config::getInstance().getDPIScale());
    this->setMinimumHeight(600 * Config::getInstance().getDPIScale());

    //Restore prev window geometry if have
    {
        auto geo = Config::getInstance().getWindowGeo();
        if (!geo.isEmpty())
        {
            this->restoreGeometry(geo);
        }
    }

    setupMenu();

    webView = new CustomWebView(this);
    webView->setZoomFactor(Config::getInstance().getDPIScale());
    webView->setUrl(workingUrl);

    this->setCentralWidget(webView);
}

//Slots
void BrowserWindow::downloadRequested(QWebEngineDownloadItem *item)
{
    item = item;//param unuse for now;
    QMessageBox::information(this, "Download notification",
                             "1 item is ready to download\nurl: " + item->path());
}

void BrowserWindow::openExternal()
{
    QDesktopServices::openUrl(webView->url());
}

void BrowserWindow::titleChanger(const QString &newTitle)
{
    this->setWindowTitle(newTitle + " on OtherThanThat");
}

void BrowserWindow::zoomFactorChecker(const QUrl&)
{
    //set zoom factor for heigher dpi each time url loaded
    auto dpiScale = Config::getInstance().getDPIScale();
    if (webView->zoomFactor() != dpiScale)
        webView->setZoomFactor(dpiScale);
}
