#include "stdafx.h"
#ifndef CLASS_PICTURE
#define CLASS_PICTURE

class Picture
{
private:
    static const int maxw=1500,maxh=1500;
    int height,width;
    int brg[3][maxw][maxh];
    int *b[maxw],*r[maxw],*g[maxw];
public:
    Picture();
    Picture(Picture& picb);
    void Init(Picture &picb);
    void AttachFromFile(const char * file_name);
    void PrintIntoFile(const char * file_name);
    void Paint(HDC hdc,int ws,int hs);
    void GaussianBlur(int step);
    void ContrastIncrease();
    int GetHeight();
    int GetWidth();
    int GetPixel(int x,int y);
    void SetPixel(int x,int y,int rgbval);
    void OnlyRed();
    void OnlyBlue();
    void OnlyGreen();
    void operator = (Picture &picb);
};
#endif
