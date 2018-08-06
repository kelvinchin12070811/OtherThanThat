#include <QCloseEvent>
#include <qfiledialog.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qnetworkrequest.h>
#include <qurl.h>
#include "Config.hpp"
#include "ItemDownloader.hpp"

ItemDownloader::ItemDownloader()
{
    this->setAttribute(Qt::WA_DeleteOnClose);
    setupUi();
    connectItems();
}

void ItemDownloader::setDownload(const QString &defPath, const QUrl &url)
{
    fileName = defPath;
    this->url = url;

    fileName = QFileDialog::getSaveFileName(this, "Save to...", fileName);
    output.setFileName(fileName);
    if (!output.open(QFile::OpenModeFlag::WriteOnly))
        return;

    QNetworkRequest request(this->url);
    curDlItem = networkAccMng.get(request);
    connect(curDlItem, &QNetworkReply::downloadProgress, this, &ItemDownloader::reportProgess);
    connect(curDlItem, &QNetworkReply::finished, this, &ItemDownloader::dlFinished);
    connect(curDlItem, &QNetworkReply::readyRead, this, &ItemDownloader::writeReady);
    this->show();
}

void ItemDownloader::closeEvent(QCloseEvent *ev)
{
    if (curDlItem == nullptr) return;

    if (!curDlItem->isFinished())
    {
        auto response = QMessageBox::information(this, "Download not compleate yet",
                                                 "Your file \"" + QFileInfo(fileName).fileName() + "\" has not yet finish.\n" +
                                                 "would you like to cancel it?", QMessageBox::Yes, QMessageBox::No);
        if (response == QMessageBox::No)
            ev->ignore();
        else
            curDlItem->close();
    }
}

void ItemDownloader::connectItems()
{
    connect(cancelButton, &QPushButton::clicked, [&]()
    {
        if (curDlItem != nullptr)
        {
            curDlItem->close();
        }
        this->close();
    });
}

void ItemDownloader::setupUi()
{
    auto factor = Config::getInstance().getDPIScale();

    QSize windowSize(512 * factor, 120 * factor);

    this->setMinimumSize(windowSize);
    this->setMaximumSize(windowSize);

    addressLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    pathLayout = new QHBoxLayout;
    progressLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    addressLabel  = new QLabel("Address  :", this);
    pathLabel     = new QLabel("Save to   :", this);
    progressLabel = new QLabel("Progress :", this);

    addressBar = new QLineEdit(this);
    addressBar->setMinimumHeight(20 * factor);
    addressBar->setReadOnly(true);

    fileNameBar = new QLineEdit(this);
    fileNameBar->setMinimumHeight(20 * factor);
    fileNameBar->setReadOnly(true);

    downloadProgressBar = new QProgressBar(this);
    downloadProgressBar->setMinimumHeight(20 * factor);

    cancelButton = new QPushButton("Cancel", this);
    //pauseResumeButton = new QPushButton("Pause", this);
    cancelButton->setMinimumHeight(20 * factor);
    cancelButton->setMaximumHeight(20 * factor);

    downloadProgressBar->setValue(0);

    addressLayout->addWidget(addressLabel);
    addressLayout->addWidget(addressBar);

    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);
    //buttonLayout->addWidget(pauseResumeButton);

    pathLayout->addWidget(pathLabel);
    pathLayout->addWidget(fileNameBar);

    progressLayout->addWidget(progressLabel);
    progressLayout->addWidget(downloadProgressBar);

    mainLayout->addItem(addressLayout);
    mainLayout->addItem(pathLayout);
    mainLayout->addItem(progressLayout);
    mainLayout->addItem(buttonLayout);
    this->setLayout(mainLayout);
}

void ItemDownloader::dlFinished()
{
    QMessageBox::information(this, "File downloaded", "File \"" + QFileInfo(fileName).fileName() + "\" has been downloaded.");
    this->close();
}

void ItemDownloader::reportProgess(qint64 recived, qint64 totalSz)
{
    downloadProgressBar->setValue((recived / totalSz) * 100);
}

void ItemDownloader::writeReady()
{
    if(output.isOpen())
    {
        output.write(curDlItem->readAll());
    }
}
