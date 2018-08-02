#ifndef BROWSERWINDOW_HPP
#define BROWSERWINDOW_HPP

#include <QMainWindow>

class BrowserWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BrowserWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // BROWSERWINDOW_HPP