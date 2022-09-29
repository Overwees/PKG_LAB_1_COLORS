#include "colormath.h"
#include <cmath>
double static min(double, double, double);
double static max(double, double, double);
double static Hue_to_RGB(double,double,double);
colorMath::colorMath()
{
    HEX = "000000";
}

void colorMath::setRGB(double r,double g,double b)
{
    rgb[0] = double(r);
    rgb[1] = double(g);
    rgb[2] = double(b);
    ConvertFromRGBToHEX();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToHSV();
    ConvertFromRGBToHSL();
    ConvertFromRGBToXYZ();
    ConvertFromXYZToLAB();
}
void colorMath::setCMYK(double c,double m,double y,double k)
{
    cmyk[0] = double(c)/100;
    cmyk[1] = double(m)/100;
    cmyk[2] = double(y)/100;
    cmyk[3] = double(k)/100;
    ConvertFromCMYKToRGB();
    ConvertFromRGBToHEX();
    ConvertFromRGBToHSV();
    ConvertFromRGBToHSL();
    ConvertFromRGBToXYZ();
    ConvertFromXYZToLAB();
}
void colorMath::setHSV(double h,double s,double v)
{
    hsv[0] = double(h) / 360;
    hsv[1] = double(s) / 100;
    hsv[2] = double(v) / 100;
    ConvertFromHSVToRGB();
    ConvertFromRGBToHEX();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToHSL();
    ConvertFromRGBToXYZ();
    ConvertFromXYZToLAB();
}
void colorMath::setHSL(double h,double s,double l)
{
    hsl[0] = double(h) / 360;
    hsl[1] = double(s) / 100;
    hsl[2] = double(l) / 100;
    ConvertFromHSLToRGB();
    ConvertFromRGBToHEX();
    ConvertFromRGBToHSV();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToXYZ();
    ConvertFromXYZToLAB();
}
void colorMath::setXYZ(double x,double y,double z)
{
    xyz[0]=double(x);
    xyz[1]=double(y);
    xyz[2]=double(z);
    if (xyz[0] > 95.047)xyz[0] = 95.047;
    if (xyz[2] > 108.883)xyz[2] = 108.883;
    ConvertFromXYZToLAB();
    ConvertFromXYZToRGB();
    ConvertFromRGBToHEX();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToHSV();
    ConvertFromRGBToHSL();
}
void colorMath::setLAB(double l,double a,double b)
{
    lab[0]=double(l);
    lab[1]=double(a);
    lab[2]=double(b);
    ConvertFromLABToXYZ();
    ConvertFromXYZToRGB();
    ConvertFromRGBToHEX();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToHSV();
    ConvertFromRGBToHSL();
}
void colorMath::setHEX(QString s)
{
    HEX = s;
    ConvertFromHEXToRGB();
    ConvertFromRGBToCMYK();
    ConvertFromRGBToHSV();
    ConvertFromRGBToHSL();
    ConvertFromRGBToXYZ();
    ConvertFromXYZToLAB();
}

void colorMath::ConvertFromRGBToHEX()
{
    QString fir = QString::number(int(rgb[0]),16);
    if (fir.length() == 1)
        fir = "0"+ fir;
    QString sec = QString::number(int(rgb[1]),16);
    if (sec.length() == 1)
        sec = "0"+ sec;
    QString thr = QString::number(int(rgb[2]),16);
    if (thr.length() == 1)
        thr = "0"+ thr;
    HEX = fir + sec + thr;
}
void colorMath::ConvertFromRGBToCMYK()
{
    if ((1- rgb[0]/double(255) < 1 - rgb[1]/double(255)) && (1- rgb[0]/double(255) < 1 - rgb[2]/double(255)))
    {
        cmyk[3] = 1 - rgb[0]/double(255);
    }
    else if (1 - rgb[1]/double(255) < 1 - rgb[2]/double(255))
    {
        cmyk[3] = 1 - rgb[1]/double(255);
    }
    else
    {
        cmyk[3] = 1 - rgb[2]/double(255);
    }
    cmyk[0] = (1-rgb[0]/double(255) - cmyk[3])/(1 - cmyk[3]);
    cmyk[1] = (1-rgb[1]/double(255) - cmyk[3])/(1 - cmyk[3]);
    cmyk[2] = (1-rgb[2]/double(255) - cmyk[3])/(1 - cmyk[3]);
}
void colorMath::ConvertFromRGBToHSV()
{
    //R, G and B input range = 0 ÷ 255
    //H, S and V output range = 0 ÷ 1.0

    double r = ( rgb[0] / double(255) );
    double g = ( rgb[1] / double(255) );
    double b = ( rgb[2] / double(255) );

    double max_val = min(r, g, b);    //Min. value of RGB
    double min_val = max(r, g, b);   //Max. value of RGB
    double del_Max = max_val - min_val;             //Delta RGB value

    hsv[2] = max_val;

    if (del_Max == 0)                     //This is a gray, no chroma...
    {
        hsv[0] = 0;
        hsv[1] = 0;
    }
    else                                    //Chromatic data...
    {
       hsv[1] = del_Max / max_val;

       double del_r = ( ( ( max_val - r ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;
       double del_g = ( ( ( max_val - g ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;
       double del_b = ( ( ( max_val - b ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;

       if( r == max_val )
           hsv[0] = del_b - del_g;
       else if( g == max_val )
           hsv[0] = ( double(1) / double(3) ) + del_r - del_b;
       else if( b == max_val )
           hsv[0] = ( double(2) / double(3) ) + del_g - del_r;
        if ( hsv[0] < 0 )
            hsv[0] += 1;
        if ( hsv[0] > 1 )
            hsv[0] -= 1;
    }
}
void colorMath::ConvertFromRGBToHSL()
{
    //R, G and B input range = 0 ÷ 255
    //H, S and L output range = 0 ÷ 1.0

    double r = ( rgb[0] / 255 );
    double g = ( rgb[1] / 255 );
    double b = ( rgb[2] / 255 );

    double min_value = min(r, g, b);   //Min. value of RGB
    double max_value = max(r, g, b);   //Max. value of RGB
    double del_Max = max_value - min_value;           //Delta RGB value

    hsl[1] = ( max_value + min_value )/ double(2);

    if ( del_Max == 0 )                     //This is a gray, no chroma...
    {
        hsl[0] = 0;
        hsl[1] = 0;
    }
    else                                    //Chromatic data...
    {
       if ( hsl[2] < 0.5 )
            hsl[1] = del_Max / ( max_value + min_value );
       else
            hsl[1] = del_Max / ( 2 - max_value - min_value );

       double del_R = ( ( ( max_value - r ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;
       double del_G = ( ( ( max_value - g ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;
       double del_B = ( ( ( max_value - b ) / double(6) ) + ( del_Max / double(2) ) ) / del_Max;

       if(r == max_value)
            hsl[0] = del_B - del_G;
       else if (g == max_value)
            hsl[0] = double(1) / double(3) + del_R - del_B;
       else if(b == max_value)
            hsl[0] = double(2) / double(3) + del_G - del_R;

        if ( hsl[0] < 0 )
            hsl[0] += 1;
        if ( hsl[0] > 1 )
            hsl[0] -= 1;
    }
}
void colorMath::ConvertFromRGBToXYZ()
{
    double r = rgb[0] / double(255);
    double g = rgb[1] / double(255);
    double b = rgb[2] / double(255);

    if (r > 0.04045)
        r = pow((( r + 0.055 ) / 1.055), 2.4);
    else
        r = r / 12.92;
    if (g > 0.04045)
        g = pow((( g + 0.055 ) / 1.055), 2.4);
    else
        g = g / 12.92;
    if ( b > 0.04045 )
        b = pow(((b + 0.055 ) / 1.055), 2.4);
    else
        b = b / 12.92;

    r = r * 100;
    g = g * 100;
    b = b * 100;

    xyz[0] = r * 0.4124 + g * 0.3576 + b * 0.1805;
    xyz[1] = r * 0.2126 + g * 0.7152 + b * 0.0722;
    xyz[2] = r * 0.0193 + g * 0.1192 + b * 0.9505;
    if (xyz[0] < 0) xyz[0] = 0;
    if (xyz[0] > 95) xyz[0] = 95.047;
    if (xyz[1]< 0) xyz[1] = 0;
    if (xyz[1]> 100) xyz[1] = 100;
    if (xyz[2]< 0) xyz[2] = 0;
    if (xyz[2]> 108.883) xyz[2] = 108.883;
}

void colorMath::ConvertFromXYZToLAB()
{
    double x = xyz[0] / 95.047;
    double y = xyz[1] / 100;
    double z = xyz[2] / 108.883;

    if ( x > 0.008856 )
        x = cbrt(x);
    else
        x = ( 7.787 * x ) + ( double(16) / double(116) );
    if ( y > 0.008856 )
        y = cbrt(y);
    else
        y = ( 7.787 * y ) + ( double(16) / double(116) );
    if ( z > 0.008856 )
        z = cbrt(z);
    else
        z = ( 7.787 * z ) + ( double(16) / double(116) );

    lab[0] = ( 116 * y ) - 16;
    if (lab[0] < 0) lab[0] = 0;
    if (lab[0] > 100) lab[0] = 100;
    lab[1] = 500 * ( x - y );
    if (lab[1]< -128) lab[1] = -128;
    if (lab[1]> 128) lab[1] = 128;
    lab[2] = 200 * ( y - z );
    if (lab[2]< -128) lab[2] = -128;
    if (lab[2]> 128) lab[2] = 128;
}
void colorMath::ConvertFromCMYKToRGB()
{
    rgb[0]= 255*(1 - cmyk[0])*(1 - cmyk[3]);
    rgb[1]= 255*(1 - cmyk[1])*(1 - cmyk[3]);
    rgb[2]= 255*(1 - cmyk[2])*(1 - cmyk[3]);
}
void colorMath::ConvertFromHSVToRGB()
{
    //H, S and V input range = 0 ÷ 1.0
    //R, G and B output range = 0 ÷ 255

    if (hsv[1] == 0)
    {
       rgb[0] = hsv[2] * 255;
       rgb[1] = hsv[2] * 255;
       rgb[2] = hsv[2] * 255;
    }
    else
    {
       double H = hsv[0] * 6;
       if (H == 6)
           H = 0;      //H must be < 1
       int var_i = (int)H;             //Or ... var_i = floor( var_h )
       double var_1 = hsv[2] * (1 - hsv[1] );
       double var_2 = hsv[2] * (1 - hsv[1] * (H - var_i ));
       double var_3 = hsv[2] * (1 - hsv[1] * (1 - ( H - var_i )));
    double var_r, var_g, var_b;

       if      ( var_i == 0 ) { var_r = hsv[2]     ; var_g = var_3 ; var_b = var_1; }
       else if ( var_i == 1 ) { var_r = var_2 ; var_g = hsv[2]     ; var_b = var_1; }
       else if ( var_i == 2 ) { var_r = var_1 ; var_g = hsv[2]     ; var_b = var_3; }
       else if ( var_i == 3 ) { var_r = var_1 ; var_g = var_2 ; var_b = hsv[2];     }
       else if ( var_i == 4 ) { var_r = var_3 ; var_g = var_1 ; var_b = hsv[2];     }
       else                   { var_r = hsv[2]     ; var_g = var_1 ; var_b = var_2; }

       rgb[0] = var_r * 255;
       rgb[1] = var_g * 255;
       rgb[2] = var_b * 255;
    }
    if(rgb[0]> 255)rgb[0] = 255;
    if(rgb[1]> 255)rgb[1] = 255;
    if(rgb[2]> 255)rgb[2] = 255;
}
void colorMath::ConvertFromHSLToRGB()
{
    //H, S and L input range = 0 ÷ 1.0
    //R, G and B output range = 0 ÷ 255

    if ( hsl[1] == 0 )
    {

       rgb[0] = hsl[2] * 255;
       rgb[1] = hsl[2] * 255;
       rgb[2] = hsl[2] * 255;
    }
    else
    {
       double val_2;
       if ( hsl[2] < 0.5 )
            val_2 = hsl[2] * ( 1 + hsl[1] );
       else
            val_2 = ( hsl[1] + hsl[2] ) - ( hsl[2] * hsl[1] );

       double val_1 = 2 * hsl[2] - val_2;

       rgb[0] = 255 * Hue_to_RGB( val_1, val_2, hsl[0] + ( double(1) / double(3) ));
       rgb[1] = 255 * Hue_to_RGB( val_1, val_2, hsl[0]);
       rgb[2] = 255 * Hue_to_RGB( val_1, val_2, hsl[0] - ( double(1) / double(3) ));
    }
    if(rgb[0]> 255)rgb[0] = 255;
    if(rgb[1]> 255)rgb[1] = 255;
    if(rgb[2]> 255)rgb[2] = 255;
}
void colorMath::ConvertFromXYZToRGB()
{
    //X, Y and Z input refer to a D65/2° standard illuminant.
    //sR, sG and sB (standard RGB) output range = 0 ÷ 255

    double x = double(xyz[0]) / double(100);
    double y = double(xyz[1]) / double(100);
    double z = double(xyz[2]) / double(100);

    double r = x *  3.2406 + y * -1.5372 + z * -0.4986;
    double g = x * -0.9689 + y *  1.8758 + z *  0.0415;
    double b = x *  0.0557 + y * -0.2040 + z *  1.0570;

    if (r > 0.0031308)
            r = 1.055 *  pow(r, 1 / 2.4 ) - 0.055;
    else
            r = 12.92 * r;
    if ( g > 0.0031308 )
            g = 1.055 * pow(g, 1 / 2.4) - 0.055;
    else
            g = 12.92 * g;
    if ( b > 0.0031308 )
            b = 1.055 * pow(b, 1 / 2.4) - 0.055;
    else
            b = 12.92 * b;

    rgb[0] = r * 255;
    rgb[1] = g * 255;
    rgb[2] = b * 255;
    if(rgb[0]> 255)rgb[0] = 255;
    if(rgb[0]< 0)rgb[0] = 0;
    if(rgb[1]> 255)rgb[1] = 255;
    if(rgb[1]< 0)rgb[1] = 0;
    if(rgb[2]> 255)rgb[2] = 255;
    if(rgb[2]< 0)rgb[2] = 0;
}
void colorMath::ConvertFromLABToXYZ()
{
    // l [0;100] a [-128,128] and b [-128,128]
    double y = ( lab[0] + 16 ) / double(116);
    double x = lab[1] / double(500) + y;
    double z = y - lab[2] / double(200);

    if ( pow(y,3)  > 0.008856 )
        y = pow(y,3);
    else
        y = ( y - double(16) / double(116) ) / 7.787;
    if ( pow(x,3)  > 0.008856 )
        x = pow(x,3);
    else
        x = ( x - double(16) / double(116) ) / 7.787;
    if ( pow(z,3)  > 0.008856 )
        z = pow(z,3);
    else
        z = ( z - double(16) / double(116) ) / 7.787;

    xyz[0] = x * 95.047;
    xyz[1] = y * 100;
    xyz[2] = z * 108.883;
    if (xyz[0] < 0) xyz[0] = 0;
    if (xyz[0] > 95.047) xyz[0] = 95.047;
    if (xyz[1]< 0) xyz[1] = 0;
    if (xyz[1]> 100) xyz[1] = 100;
    if (xyz[2]< 0) xyz[2] = 0;
    if (xyz[2]> 108.883) xyz[2] = 108.883;
}

void colorMath::ConvertFromHEXToRGB()
{
    bool ok;
    QString buffer1(HEX[0]);
    buffer1 += HEX[1];
    QString buffer2(HEX[2]);
    buffer2 += HEX[3];
    QString buffer3(HEX[4]);
    buffer3 += HEX[5];
    rgb[0]=buffer1.toInt(&ok,16);
    rgb[1]=buffer2.toInt(&ok,16);
    rgb[2]=buffer3.toInt(&ok,16);
}

double colorMath::getR_rgb()const
{
    return double(rgb[0]);
}
double colorMath::getG_rgb()const
{
    return double(rgb[1]);
}
double colorMath::getB_rgb()const
{
    return double(rgb[2]);
}

double colorMath::getC_cmyk()const
{
    return double(cmyk[0])*100;
}
double colorMath::getM_cmyk()const
{
    return double(cmyk[1])*100;
}
double colorMath::getY_cmyk()const
{
    return double(cmyk[2])*100;
}
double colorMath::getK_cmyk()const
{
    return double(cmyk[3])*100;

}

double colorMath::getH_hsv()const
{
    return double(hsv[0])*360;
}
double colorMath::getS_hsv()const
{
    return double(hsv[1])*100;
}
double colorMath::getV_hsv()const
{
    return double(hsv[2])*100;
}

double colorMath::getH_hsl()const
{
    return double(hsl[0])*360;
}
double colorMath::getL_hsl()const
{
    return double(hsl[2])*100;
}
double colorMath::getS_hsl()const
{
    return double(hsl[1])*100;
}

double colorMath::getX_xyz()const
{
    return double(xyz[0]);
}
double colorMath::getY_xyz()const
{
    return double(xyz[1]);
}
double colorMath::getZ_xyz()const
{
    return double(xyz[2]);
}

double colorMath::getL_lab()const
{
    return double(lab[0]);
}
double colorMath::getA_lab()const
{
    return double(lab[1]);
}
double colorMath::getB_lab()const
{
    return double(lab[2]);
}

QString colorMath::getHEX()const
{
    return HEX;
}

double static min(double a, double b, double c)
{
    if(a < b && a < c)
    {
        return a;
    }
    else if(b < c)
        {
            return b;
        }
    else
        {
            return c;
        }

}
double static max(double a, double b, double c)
{
    if(a > b && a > c)
    {
        return a;
    }
    else if(b > c)
        {
            return b;
        }
    else
        {
            return c;
        }
}
double static Hue_to_RGB(double val_1,double val_2,double valH )
{
   if (valH < 0)
       valH += 1;
   if(valH > 1)
       valH -= 1;
   if (( 6 * valH ) < 1)
       return ( val_1 + ( val_2 - val_1 ) * 6 * valH );
   if (( 2 * valH ) < 1)
       return ( val_2 );
   if (( 3 * valH ) < 2)
       return ( val_1 + ( val_2 - val_1 ) * ( ( double(2) / double(3) ) - valH ) * 6 );
   return ( val_1 );
}
