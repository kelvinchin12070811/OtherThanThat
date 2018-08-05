#ifndef CUSTOMWEBVIEW_HPP
#define CUSTOMWEBVIEW_HPP
#include <qwebengineview.h>

class CustomWebView : public QWebEngineView
{
public:
    CustomWebView(QWidget* parent = nullptr);
protected:
    QWebEngineView* createWindow(QWebEnginePage::WebWindowType) override;
};

#endif // CUSTOMWEBVIEW_HPP
