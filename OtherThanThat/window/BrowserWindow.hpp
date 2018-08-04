#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <qbytearray.h>
#include <QMainWindow>
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
    void closeEvent(QCloseEvent* event);

private:
    void setUpUi();

private slots:
    void on_loadFinished();

private:
    CustomWebView* webView{ nullptr };
    QUrl driveUrl;
    QByteArray prevWindowRect;
    QString geoFileName{"win_geo.dat"};
    bool isMainWindow;
};

#endif // BROWSERWINDOW_HPP
