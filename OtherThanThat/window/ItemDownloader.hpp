#ifndef ITEMDOWNLOADER_H
#define ITEMDOWNLOADER_H
#include <qdialog.h>
#include <qfile.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkreply.h>
#include <qprogressbar.h>
#include <qpushbutton.h>

class ItemDownloader : public QDialog
{
    Q_OBJECT
public:
    ItemDownloader();

    void setDownload(const QString& defPath, const QUrl& url);
protected:
    void closeEvent(QCloseEvent * ev) override;

private:
    void connectItems();
    void setupUi();
private slots:
    void dlFinished();
    void reportProgess(qint64 recived, qint64 totalSz);
    void writeReady();
private:
    QFile output;

    QLabel* addressLabel{ nullptr };
    QLabel* pathLabel{ nullptr };
    QLabel* progressLabel{ nullptr };

    QLineEdit* addressBar{ nullptr };
    QLineEdit* fileNameBar{ nullptr };

    QHBoxLayout* addressLayout{ nullptr };
    QHBoxLayout* buttonLayout{ nullptr };
    QHBoxLayout* pathLayout{ nullptr };
    QHBoxLayout* progressLayout{ nullptr };

    QNetworkAccessManager networkAccMng;
    QNetworkReply* curDlItem;

    QProgressBar* downloadProgressBar{ nullptr };

    QPushButton* cancelButton{ nullptr };
    QPushButton* pauseResumeButton{ nullptr };

    QString fileName;
    QUrl url;

    QVBoxLayout* mainLayout{ nullptr };
};

#endif // ITEMDOWNLOADER_H
