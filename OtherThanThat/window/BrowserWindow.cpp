#include <qfile.h>
#include "BrowserWindow.hpp"

BrowserWindow::BrowserWindow(QWidget *parent) :
    BrowserWindow(QUrl("https://accounts.google.com/signin/v2/identifier?service=wise&passive=true&continue=http%3A%2F%2Fdrive.google.com%2F%3Futm_source%3Den_US&utm_medium=button&utm_campaign=web&utm_content=gotodrive&usp=gtd&ltmpl=drive&flowName=GlifWebSignIn&flowEntry=ServiceLogin"),
                  true, parent)
{
}

BrowserWindow::BrowserWindow(const QUrl &url, bool isMainWindow, QWidget *parent):
    driveUrl(url), isMainWindow(isMainWindow), QMainWindow(parent)
{
    setUpUi();
}

CustomWebView* BrowserWindow::getWebView()
{
    return webView;
}

void BrowserWindow::closeEvent(QCloseEvent *event)
{
    if (!isMainWindow) return;

    auto currentState = this->saveGeometry();
    if (currentState == prevWindowRect) return;

    QFile geoFile(geoFileName);
    if (geoFile.open(QIODevice::WriteOnly))
    {
        geoFile.write(currentState);
    }
}

void BrowserWindow::setUpUi()
{
    auto setWindowSize = [&]()
    {
        this->setMinimumWidth(800 * Config::getInstance().getDPIScale());
        this->setMinimumHeight(600 * Config::getInstance().getDPIScale());
    };

    if (isMainWindow)
    {
        QFile winRectStateFile(geoFileName);
        if (winRectStateFile.open(QIODevice::ReadOnly))
        {
            prevWindowRect = winRectStateFile.readAll();
            this->restoreGeometry(prevWindowRect);
        }
        else
        {
            setWindowSize();
        }
        winRectStateFile.close();
    }
    else
    {
        setWindowSize();
    }

    webView = new CustomWebView(this);
    webView->setZoomFactor(Config::getInstance().getDPIScale());
    webView->setUrl(driveUrl);

    this->setCentralWidget(webView);
}

void BrowserWindow::on_loadFinished()
{

}
