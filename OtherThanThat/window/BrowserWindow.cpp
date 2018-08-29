#include <memory>
#include <qdesktopservices.h>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qwebengineprofile.h>
#include <BookmarkFilePraser.hpp>
#include "BrowserWindow.hpp"
#include "window/AddressWindow.hpp"

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

void BrowserWindow::cmdLineChecker()
{
    auto& args = Config::getInstance().getCmdArgs();
    if (args.empty() || args.size() <= 1) return;
    auto file = args.back();
    if (file.isEmpty()) return;

    BookmarkFilePraser bmfPraser(file, BookmarkFilePraser::FileMode::LoadFile);
    auto url = bmfPraser.getTargetUrl();
    if (!url.isEmpty())
    {
        workingUrl = url;
    }
}

void BrowserWindow::connectObjects()
{
    //Actions Signals
    connect(aboutAction, &QAction::triggered, [&](){
        QMessageBox::about(this, "About OtherThanThat v" + Config::APP_VERSION,
                           "<img src=\":/ott/resources/icon.png\"/><br/>OtherThanThat is an unofficial Google Drive Client by Kelvin Chin");
    });
    connect(aboutQtAction, &QAction::triggered, [&](){
        QMessageBox::aboutQt(this, QString("About Qt v") + qVersion());
    });
    connect(backNavAction, &QAction::triggered, [&](){
        this->webView->back();
    });
    connect(closeAction, &QAction::triggered, [&](){ this->close(); });
    connect(forwardNavAction, &QAction::triggered, [&](){
        this->webView->forward();
    });
    connect(openBookmarkAction, &QAction::triggered, this, &BrowserWindow::openBookmark);
    connect(openCacheLocation, &QAction::triggered, [&]() {
       QDesktopServices::openUrl(QUrl(Config::getInstance().getAppDataLocation()));
    });
    connect(openInBrowserAction, &QAction::triggered, this, &BrowserWindow::openExternal);
    connect(refreshAction, &QAction::triggered, [&](){
        this->webView->reload();
    });
    connect(saveBookmarkAction, &QAction::triggered, this, &BrowserWindow::saveBookmark);
    connect(savePDFAction, &QAction::triggered, this, &BrowserWindow::savePDF);
    connect(showAddressAction, &QAction::triggered, [&](){
        AddressWindow* win = new AddressWindow(this->webView->url(), this);
        win->setAttribute(Qt::WA_DeleteOnClose, true);
        win->show();
    });

    //Widgets signals
    connect(webView, &CustomWebView::loadFinished, this, &BrowserWindow::loadFinished);
    connect(webView, &CustomWebView::loadStarted, this, &BrowserWindow::loadStarted);
    connect(webView->page(), &QWebEnginePage::fullScreenRequested, this, &BrowserWindow::fullScreenRequested);
    connect(webView, &CustomWebView::titleChanged, this, &BrowserWindow::titleChanger);
    connect(webView, &CustomWebView::urlChanged, this, &BrowserWindow::zoomFactorChecker);
    connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested, this, &BrowserWindow::downloadRequested);
}

void BrowserWindow::setupMenu()
{
    {//File menu
        auto fileMenu = this->menuBar()->addMenu("&File");

        closeAction = new QAction("Close", this);
        openBookmarkAction = new QAction("Open local bookmark", this);
        openCacheLocation = new QAction("Open cache folder", this);
        saveBookmarkAction = new QAction("Create local bookmark", this);
        savePDFAction = new QAction("Save current page as PDF", this);

        openBookmarkAction->setShortcut(QKeySequence::Open);
        saveBookmarkAction->setShortcut(QKeySequence::Save);

        fileMenu->addAction(saveBookmarkAction);
        fileMenu->addAction(openBookmarkAction);
        fileMenu->addSeparator();
        fileMenu->addAction(savePDFAction);
        fileMenu->addSeparator();
        fileMenu->addAction(openCacheLocation);
        fileMenu->addAction(closeAction);
    }
    {//Navigatin menu
        auto navMenu = this->menuBar()->addMenu("&Navigation");

        backNavAction = new QAction("Back", this);
        forwardNavAction = new QAction("Forward", this);
        refreshAction = new QAction("Refresh", this);
        openInBrowserAction = new QAction("Open in browser", this);
        showAddressAction = new QAction("Current URL", this);

        backNavAction->setShortcut(QKeySequence::StandardKey::Back);
        forwardNavAction->setShortcut(QKeySequence::StandardKey::Forward);
        openInBrowserAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key::Key_O));
        refreshAction->setShortcut(QKeySequence(Qt::Key_F5));

        backNavAction->setToolTip("Navigate back");
        forwardNavAction->setToolTip("Navigate forward");
        openInBrowserAction->setToolTip("Open this page in browser");
        refreshAction->setToolTip("Reload current page");

        navMenu->addAction(backNavAction);
        navMenu->addAction(forwardNavAction);
        navMenu->addSeparator();
        navMenu->addAction(refreshAction);
        navMenu->addAction(openInBrowserAction);
        navMenu->addSeparator();
        navMenu->addAction(showAddressAction);
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
    this->setMinimumSize(Config::getInstance().adjustScale(QSize(800, 600)));

    //Restore prev window geometry if have
    {
        auto geo = Config::getInstance().getWindowGeo();
        if (!geo.isEmpty())
        {
            this->restoreGeometry(geo);
        }
    }

    cmdLineChecker();
    setupMenu();

    webView = new CustomWebView(this);
    webView->setZoomFactor(Config::getInstance().getDPIScale());
    webView->setUrl(workingUrl);

    this->setCentralWidget(webView);
}

//Slots
void BrowserWindow::downloadRequested(QWebEngineDownloadItem *item)
{
    //(new ItemDownloader)->setDownload(item->path(), item->url());
    QDesktopServices::openUrl(item->url());
    QMessageBox::information(this, "Download request sent",
                             "The request of downloading \"" + QFileInfo(item->path()).fileName() + "\" has been sent to your browser.");
}

void BrowserWindow::fullScreenRequested(QWebEngineFullScreenRequest request)
{
    if (request.toggleOn())
    {
        if (fsViewer != nullptr) return;
        request.accept();
        fsViewer = std::make_unique<FullscreenView>(webView);
    }
    else
    {
        if (fsViewer == nullptr) return;
        request.accept();
        fsViewer = nullptr;
    }
}

void BrowserWindow::loadStarted()
{
    loaded = false;
    this->setWindowTitle(webTitle + " on OtherThanThat [Loading...]");
}

void BrowserWindow::loadFinished()
{
    loaded = true;
    if (loaded)
        this->setWindowTitle(webTitle + " on OtherThanThat");
}

void BrowserWindow::openBookmark()
{
    QString file = QFileDialog::getOpenFileName(this, "Select bookmark", "", "Bookmark file(*.bmf)");
    if (file.isEmpty()) return;

    BookmarkFilePraser bmfPraser(file, BookmarkFilePraser::FileMode::LoadFile);
    auto url = bmfPraser.getTargetUrl();
    if (!url.isEmpty())
    {
        webView->setHtml(QString("<html>"
                                 "<head>"
                                 "<title>Redirecting to bookmarked destination...</title>"
                                 "<meta http-equiv=\"refresh\" content=\"5;url=%1\">"
                                 "</head>"
                                 "</html>").arg(url));
        return;
    }
}

void BrowserWindow::openExternal()
{
    QDesktopServices::openUrl(webView->url());
}

void BrowserWindow::saveBookmark()
{
    QString file = QFileDialog::getSaveFileName(this, "Save bookmark to...", webTitle, "Bookmark file(*.bmf)");
    if (file.isEmpty()) return;

    QFileInfo fileName(file);
    if (fileName.baseName() == webTitle)
        file = fileName.path() + "/" + webTitle + "." + fileName.completeSuffix();

    BookmarkFilePraser bmfPraser(file, BookmarkFilePraser::FileMode::CreateFile);
    bmfPraser.setTargetUrl(webView->url().toString());
    bmfPraser.dump();
}

void BrowserWindow::savePDF()
{
    /*if (loaded == false)
    {
        QMessageBox::information(this, "Page not finish load yet", "This page have not yet finish loaded, try again after it load finish");
        return;
    }*/
    QString fileName = QFileDialog::getSaveFileName(this, "Save your PDF to...", webTitle, "PDF file(*.pdf)");
    webView->page()->printToPdf(fileName);
}

void BrowserWindow::titleChanger(const QString &newTitle)
{
    webTitle = newTitle;
    this->setWindowTitle(newTitle + " on OtherThanThat");
}

void BrowserWindow::zoomFactorChecker(const QUrl& url)
{
    //set zoom factor for heigher dpi each time url loaded
    auto dpiScale = Config::getInstance().getDPIScale();
    if (webView->zoomFactor() != dpiScale)
        webView->setZoomFactor(dpiScale);
}
