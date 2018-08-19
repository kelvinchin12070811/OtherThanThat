#ifndef ADDRESSWINDOW_H
#define ADDRESSWINDOW_H
#include <qdialog.h>
#include <qtextbrowser.h>
#include <qurl.h>

class AddressWindow : public QDialog
{
    Q_OBJECT
public:
    AddressWindow(const QUrl& url, QWidget* parrent = nullptr);

    void setupUI();
private:
    QTextBrowser* address{ nullptr };
    QUrl url;
};

#endif // ADDRESSWINDOW_H
