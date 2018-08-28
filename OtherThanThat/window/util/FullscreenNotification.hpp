#ifndef FULLSCREENNOTIFICATION_HPP
#define FULLSCREENNOTIFICATION_HPP

#include <memory>
#include <qlabel.h>
#include <qsequentialanimationgroup.h>

class FullscreenNotification : public QLabel
{
    Q_OBJECT
public:
    explicit FullscreenNotification(QWidget* parrent = nullptr);

    void forceStopAll();
protected:
    void showEvent(QShowEvent* showEvent);
signals:
    void shown();
private:
    bool prevVisible{ false };
    std::unique_ptr<QSequentialAnimationGroup> animations{ nullptr };
};

#endif // FULLSCREENNOTIFICATION_HPP
