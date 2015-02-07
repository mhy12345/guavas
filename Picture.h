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
    char *note;
public:
    Picture();
    Picture(const Picture& picb);
    ~Picture();
    void Init(const Picture &picb);
    void AttachFromFile(const char * file_name);
    void PrintIntoFile(const char * file_name)const;
    void PrintPicture(FILE* outfile=stdout)const;
#ifdef WIN32
    void Paint(HDC hdc,int ws,int hs)const;
#endif
    void GaussianBlur(int step);
    void ContrastIncrease();
    int GetHeight()const;
    int GetWidth()const;
    void SetHeight(int nh);
    void SetWidth(int nw);
    int GetPixel(int x,int y)const;
    void SetPixel(int x,int y,int rgbval);
    void OnlyRed();
    void OnlyBlue();
    void OnlyGreen();
    bool IsWhite(int x,int y)const;
    bool IsBlack(int x,int y)const;
    void operator = (const Picture &picb);
    void FillWord(int col=0);
    void StainRemoval();
    void BandW();
    void Contract();
};
#endif
