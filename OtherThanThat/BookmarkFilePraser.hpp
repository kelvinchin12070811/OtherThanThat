#ifndef BOOKMARKFILEPRASER_HPP
#define BOOKMARKFILEPRASER_HPP
#include <exception>
#include <qstring.h>

class BookmarkFilePraser
{
public:
    enum class FileMode : uint8_t { LoadFile, CreateFile };
public:
    BookmarkFilePraser() = default;
    BookmarkFilePraser(const QString& name, FileMode mode);
    void dump() const;

/********** [Getters] **********/
public:
    QString getFileName() const;
    QString getTargetUrl() const;
/********** [!Getters] **********/

/********** [Setters] **********/
public:
    void setFileName(const QString& value);
    void setTargetUrl(const QString& value);
/********** [!Setters] **********/

/********** [Properties] **********/
private:
    QString fileName;
    QString fileVersion{ "1.0" };
    QString fileMagicNum{ "BMF-CC50" };
    QString targetUrl;
/********** [!Properties] **********/
};

#endif // BOOKMARKFILEPRASER_HPP
