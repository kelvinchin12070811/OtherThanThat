#ifndef FULLSCREENVIEW_HPP
#define FULLSCREENVIEW_HPP

#include <qpointer.h>
#include <qwidget.h>
#include <qwebengineview.h>
#include "window/util/FullscreenNotification.hpp"

class FullscreenView : public QWidget
{
    Q_OBJECT
public:
    explicit FullscreenView(QWebEngineView* previous, QWidget* parent = nullptr);
    ~FullscreenView();

protected:
    void resizeEvent(QResizeEvent* event) override;
private:
    QRect prevGeo;
    QPointer<QWebEngineView> curnView{ nullptr };
    QPointer<QWebEngineView> prevView{ nullptr };
    QPointer<FullscreenNotification> fsNotification{ nullptr };
};

#endif // FULLSCREENVIEW_HPP
