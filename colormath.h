#ifndef COLORMATH_H
#define COLORMATH_H
#include <QString>
#include <QColor>
class colorMath
{
public:
    colorMath();
    void setRGB(double,double,double);
    void setCMYK(double,double,double,double);
    void setHSV(double,double,double);
    void setHSL(double,double,double);
    void setXYZ(double,double,double);
    void setLAB(double,double,double);
    void setHEX(QString);
    double getR_rgb()const;
    double getG_rgb()const;
    double getB_rgb()const;
    double getC_cmyk()const;
    double getM_cmyk()const;
    double getY_cmyk()const;
    double getK_cmyk()const;
    double getH_hsv()const;
    double getS_hsv()const;
    double getV_hsv()const;
    double getH_hsl()const;
    double getL_hsl()const;
    double getS_hsl()const;
    double getX_xyz()const;
    double getY_xyz()const;
    double getZ_xyz()const;
    double getL_lab()const;
    double getA_lab()const;
    double getB_lab()const;
    QString getHEX()const;
private:
    void ConvertFromRGBToHEX();
    void ConvertFromRGBToCMYK();
    void ConvertFromRGBToHSV();
    void ConvertFromRGBToHSL();
    void ConvertFromRGBToXYZ();
    void ConvertFromXYZToLAB();

    void ConvertFromHEXToRGB();
    void ConvertFromCMYKToRGB();
    void ConvertFromHSVToRGB();
    void ConvertFromHSLToRGB();
    void ConvertFromXYZToRGB();
    void ConvertFromLABToXYZ();
    double rgb[3]{0,0,0};
    double hsv[3]{0,0,0};
    double cmyk[4]{0,0,0,1};
    double hsl[3]{0,0,0};
    double xyz[3]{0,0,0};
    double lab[3]{0,0,0};
    QString HEX;

};

#endif // COLORMATH_H
