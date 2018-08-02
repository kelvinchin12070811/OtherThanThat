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

void BrowserWindow::setUpUi()
{
    webView = new QWebEngineView(this);
    webView->setUrl(driveUrl);

    this->setCentralWidget(webView);
}
