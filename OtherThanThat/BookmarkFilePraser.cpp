#include <sstream>
#include <qmessagebox.h>
#include "BookmarkFilePraser.hpp"
#include "libs/pugixml/pugixml.hpp"

BookmarkFilePraser::BookmarkFilePraser(const QString &name, FileMode mode):
    fileName(name)
{
    if (mode == FileMode::LoadFile)
    {
        pugi::xml_document document;
        document.load_file(name.toUtf8().data());
        auto root = document.child("bookmark_meta");
        if (root.empty()) throw ("error prasing bookmark file");

        if (root.attribute("magic").as_string() != "BMF-CC50")
            throw std::runtime_error("invalid bookmark file");
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

    document.save_file(fileName.toUtf8().data());
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
