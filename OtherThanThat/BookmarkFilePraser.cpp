#include <sstream>
#include <qfile.h>
#include <qfileinfo.h>
#include <qmessagebox.h>
#include <qtextstream.h>
#include "BookmarkFilePraser.hpp"
#include "libs/pugixml/pugixml.hpp"

BookmarkFilePraser::BookmarkFilePraser(const QString &name, FileMode mode):
    fileName(name)
{
    if (mode == FileMode::LoadFile)
    {
        try
        {
            pugi::xml_document document;
            QFile file(fileName);
            file.open(QIODevice::ReadOnly);
            QTextStream ts(&file);
            document.load(std::string(ts.readAll().toUtf8().data()).c_str());

            auto root = document.child("bookmark_meta");
            if (root.empty()) throw std::runtime_error("error prasing bookmark file");

            if (QString::fromUtf8(root.attribute("magic").as_string()) != QString("BMF-CC50"))
                throw std::runtime_error("invalid bookmark file");

            auto targetNode = root.child("target");
            if (targetNode.empty())
                throw std::runtime_error("target not found");
            else
                targetUrl = QString::fromUtf8(targetNode.text().as_string());
        }
        catch (std::exception& e)
        {
            QMessageBox::critical(nullptr, "Error", QString::fromUtf8(e.what()));
        }
    }
}

void BookmarkFilePraser::dump() const
{
    if (fileName.isEmpty())
        throw std::exception("varaible \"BookmarkFilePraser::fileName\" is empty");

    pugi::xml_document document;
    auto decl = document.append_child(pugi::xml_node_type::node_declaration);
    decl.append_attribute("version") = "1.0";
    decl.append_attribute("encoding") = "utf-8";

    auto root = document.append_child("bookmark_meta");
    root.append_attribute("magic") = fileMagicNum.toUtf8().data();

    root.append_attribute("version") = fileVersion.toUtf8().data();

    root.append_child("target").text().set(targetUrl.toUtf8().data());

    std::ostringstream ss;
    document.save(ss);

    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream ts(&file);
        ts << QString::fromUtf8(QByteArray(ss.str().c_str(), ss.str().size()));
    }
}

/********** [Getters] **********/
QString BookmarkFilePraser::getFileName() const
{
    return fileName;
}

QString BookmarkFilePraser::getTargetUrl() const
{
    return targetUrl;
}
/********** [!Getters] **********/

/********** [Setters] **********/
void BookmarkFilePraser::setFileName(const QString &value)
{
    if (fileName != value)
        fileName = value;
}

void BookmarkFilePraser::setTargetUrl(const QString &value)
{
    if (targetUrl != value)
        targetUrl = value;
}
/********** [!Setters] **********/
