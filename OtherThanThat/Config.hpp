#ifndef CONFIG_H
#define CONFIG_H
#include <qbytearray.h>

class Config
{
public:
    static Config& getInstance();

    float getDPIScale();

    const QByteArray& getWindowGeo() const;
    void setWindowGeo(const QByteArray &value);

public: //Constant
    static const QString APP_VERSION;
    static const QString GEO_FILE_NAME;

private:
    bool isWindowGeoChanged{ false };
    const float DEFAULT_DPI{ 96.0f };
    float dpiScale{ 0 };
    QByteArray windowGeo;

private:
    Config();
    ~Config();
};

#endif // CONFIG_H
