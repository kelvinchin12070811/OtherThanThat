#ifndef CONFIG_H
#define CONFIG_H
#include <vector>
#include <qbytearray.h>
#include <qsize.h>
#include <qstring.h>

class Config
{
public:
    static Config& getInstance();

    float getDPIScale();

    const QByteArray& getWindowGeo() const;
    void setWindowGeo(const QByteArray &value);

    const std::vector<QString>& getCmdArgs() const;
    void setCmdArgs(const std::vector<QString>& args);
    void setCmdArgs(std::vector<QString>&& args);
    void setCmdArgs(int argc, char** argv);

    QString getAppDataLocation();
    QString getGeoFileName();

    QSize adjustScale(const QSize& size);

    template <typename T>
    T adjustScale(const T& value)
    {
        return static_cast<T>(value * this->dpiScale);
    }

public: //Constant
    static const QString APP_VERSION;

private:
    const float DEFAULT_DPI{ 96.0f };
    bool isWindowGeoChanged{ false };
    float dpiScale{ 0 };
    QByteArray windowGeo;
    QString appDataLocation;
    QString geoFileName{ "win_geo.dat" };
    std::vector<QString> cmdArgs;

private:
    Config();
    ~Config();
};

#endif // CONFIG_H
