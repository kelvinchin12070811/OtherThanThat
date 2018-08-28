#include <qaction.h>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qmessagebox.h>
#include "FullscreenView.hpp"

FullscreenView::FullscreenView(QWebEngineView *previous, QWidget *parent):
    QWidget(parent), curnView(new QWebEngineView(this)),
    prevView(previous), prevGeo(previous->window()->geometry()),
    fsNotification(new FullscreenNotification(this))
{
    curnView->stackUnder(fsNotification);
    auto exitAction = new QAction(this);
    exitAction->setShortcut(Qt::Key_Escape);

    connect(exitAction, &QAction::triggered, [&](){
        fsNotification->forceStopAll();
        curnView->triggerPageAction(QWebEnginePage::ExitFullScreen);
    });

    this->addAction(exitAction);

    curnView->setPage(prevView->page());
    setGeometry(prevGeo);
    this->showFullScreen();
    prevView->window()->hide();
}

FullscreenView::~FullscreenView()
{
    prevView->setPage(curnView->page());
    prevView->setGeometry(prevGeo);
    prevView->window()->show();
    this->hide();
}

void FullscreenView::resizeEvent(QResizeEvent *event)
{
    QRect viewGeo(QPoint(0, 0), this->size());
    curnView->setGeometry(viewGeo);

    QRect ntfGeo(QPoint(0, 0), fsNotification->sizeHint());
    ntfGeo.moveCenter(viewGeo.center());
    fsNotification->setGeometry(ntfGeo);

    QWidget::resizeEvent(event);
}
