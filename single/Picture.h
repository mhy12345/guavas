#include "stdafx.h"

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
#ifdef WIN32
    void Paint(HDC hdc,int ws,int hs);
#endif
    void Gaussian_Blur(int step);
    int GetHeight();
    int GetWidth();
    int GetPixel(int w,int h);
    void SetPixel(int w,int h,int rgbval);
    void OnlyRed();
    void OnlyBlue();
    void OnlyGreen();
};
