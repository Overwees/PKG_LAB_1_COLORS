#include "colormath.h"

colorMath::colorMath()
{
    HEX = "#000000";
}

void colorMath::setColor(QColor color)
{
    rgb[0]= color.red();
    rgb[1]= color.green();
    rgb[2]= color.blue();
    ConvertFromRGBToCMYK();
}

void colorMath::ConvertFromRGBToCMYK()
{
    if ((1- rgb[0]/255 < 1 - rgb[1]/255) && (1- rgb[0]/255 < 1 - rgb[2]/255))
    {
        cmyk[3] = 1- rgb[0]/255;
    }
    else if (1 - rgb[1]/255 < 1 - rgb[2]/255)
    {
        cmyk[3] = 1- rgb[1]/255;
    }
    else
    {
        cmyk[3] = 1- rgb[2]/255;
    }
    cmyk[0] = (1-rgb[0]/255 - cmyk[3])/(1 - cmyk[3]);
    cmyk[1] = (1-rgb[1]/255 - cmyk[3])/(1 - cmyk[3]);
    cmyk[2] = (1-rgb[2]/255 - cmyk[3])/(1 - cmyk[3]);
}

void colorMath::ConvertFromCMYKToRGB()
{
    rgb[0]= 255*(1 - cmyk[0])*(1 - cmyk[3]);
    rgb[1]= 255*(1 - cmyk[1])*(1 - cmyk[3]);
    rgb[2]= 255*(1 - cmyk[2])*(1 - cmyk[3]);
}
