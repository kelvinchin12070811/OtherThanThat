#include <qgraphicseffect.h>
#include <qpropertyanimation.h>
#include "FullscreenNotification.hpp"

FullscreenNotification::FullscreenNotification(QWidget* parrent):
    QLabel(parrent)
{
    this->setText("You are now in fullscreen, press ESC to exit.");
    this->setStyleSheet("font-size: 24px;"
                        "color: white;"
                        "background-color: black;"
                        "border: 2px solid white;"
                        "padding: 10px;");
    this->setAttribute(Qt::WidgetAttribute::WA_TransparentForMouseEvents);

    auto effect = new QGraphicsOpacityEffect;
    effect->setOpacity(1.0);
    this->setGraphicsEffect(effect);

    animations = std::make_unique<QSequentialAnimationGroup>();

    auto staticAnim = new QPropertyAnimation(effect, "opacity", animations.get());
    staticAnim->setDuration(1000);
    staticAnim->setStartValue(0.0);
    staticAnim->setEndValue(1.0);
    staticAnim->setEasingCurve(QEasingCurve::InOutQuad);
    animations->addAnimation(staticAnim);

    animations->addPause(2000);

    auto opacityAnim = new QPropertyAnimation(effect, "opacity", animations.get());
    opacityAnim->setDuration(1000);
    opacityAnim->setStartValue(1.0);
    opacityAnim->setEndValue(0);
    opacityAnim->setEasingCurve(QEasingCurve::InOutQuad);
    animations->addAnimation(opacityAnim);

    connect(this, &FullscreenNotification::shown, [this](){ this->animations->start(); });
    connect(animations.get(), &QSequentialAnimationGroup::finished, [this](){ this->hide(); });
}

void FullscreenNotification::forceStopAll()
{
    if (animations != nullptr && animations->state() == QAbstractAnimation::Running)
        animations->stop();
}

void FullscreenNotification::showEvent(QShowEvent *showEvent)
{
    QLabel::showEvent(showEvent);
    if (!prevVisible && this->isVisible()) emit shown();

    prevVisible = this->isVisible();
}
