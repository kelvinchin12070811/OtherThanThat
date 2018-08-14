#ifndef CUSTOMWEBRENDERER_HPP
#define CUSTOMWEBRENDERER_HPP
#include <qwebenginepage.h>

class CustomWebRenderer : public QWebEnginePage
{
    Q_OBJECT
public:
    CustomWebRenderer(QObject* parrent = nullptr);

protected:
    bool acceptNavigationRequest(const QUrl &url, NavigationType type, bool isMainFrame);
};

#endif // CUSTOMWEBRENDERER_HPP
