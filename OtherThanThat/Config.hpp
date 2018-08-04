#ifndef CONFIG_H
#define CONFIG_H

class Config
{
public:
    static Config& getInstance();

    float getDPIScale();
private:
    const float DEFAULT_DPI{ 96.0f };
    float dpiScale{ 0 };
private:
    Config();
};

#endif // CONFIG_H
