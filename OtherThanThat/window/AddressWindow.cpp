#include <qlayout.h>
#include "AddressWindow.hpp"
#include "Config.hpp"

AddressWindow::AddressWindow(const QUrl& url, QWidget* parrent):
    QDialog(parrent), url(url)
{
    setupUI();
}

void AddressWindow::setupUI()
{
    QSize size(600, 128);
    Config::getInstance().adjustScale(size);

    this->setMinimumSize(size);
    this->setWindowTitle("Current address");

    this->setLayout(new QVBoxLayout(this));
    auto layout = this->layout();
    address = new QTextBrowser(this);
    layout->addWidget(address);

    address->setText(url.toString());
    address->setReadOnly(true);
}
