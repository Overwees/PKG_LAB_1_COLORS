#ifndef COLORMATH_H
#define COLORMATH_H
#include <QString>
#include <QColor>
class colorMath
{
public:
    colorMath();
    void setColor(QColor color);
private:
    void ConvertFromRGBToCMYK();
    void ConvertFromCMYKToRGB();
    int rgb[3]{0,0,0};
    double hsv[3]{0,0,0};
    double cmyk[4]{0,0,0,1};
    double hls[3]{0,0,0};
    double xyz[3]{0,0,0};
    double lab[3]{0,0,0};
    QString HEX;

};

#endif // COLORMATH_H
