#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <QMainWindow>
#include <qwebengineview.h>
#include <qurl.h>

class BrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget *parent = nullptr);
    BrowserWindow(const QUrl& url, bool isMainWindow = true, QWidget* parent = nullptr);

private:
    void setUpUi();

private:
    QWebEngineView* webView{ nullptr };
    QUrl driveUrl;
    bool isMainWindow;
};

#endif // BROWSERWINDOW_HPP
