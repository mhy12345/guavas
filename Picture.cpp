#include "stdafx.h"
#include "Picture.h"
using namespace std;
Picture::Picture()
{
    for (int i=0; i<maxw; i++)
    {
        b[i]=brg[0][i];
        r[i]=brg[1][i];
        g[i]=brg[2][i];
    }
}
Picture::Picture(const Picture &picb)
{
    Init(picb);
}
void Picture::Init(const Picture &picb)
{
    memcpy(this,&picb,sizeof(picb));
    for (int i=0; i<maxw; i++)
    {
        b[i]=brg[0][i];
        r[i]=brg[1][i];
        g[i]=brg[2][i];
    }
}
void Picture::AttachFromFile(const char * file_name)
{
    FILE *infile=fopen(file_name,"r");
    if (!infile)
    {
        fprintf(stderr,"Cannot Open %s.\n",file_name);
        exit(0);
    }
    char str[300];
    fgets(str,sizeof(str),infile);
    if (!strstr(str,"P3"))
    {
        fprintf(stderr,"Wrong File!\n");
        exit(0);
    }
    fgets(str,sizeof(str),infile);
    fscanf(infile,"%d %d\n",&width,&height);
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            fscanf(infile,"%d %d %d",&b[i][j],&r[i][j],&g[i][j]);
}

#ifdef WIN32
void Picture::Paint(HDC hdc,int ws=0,int hs=0)
{
    ws=10+((width+10)*ws);
    hs=10+((height+10)*hs);
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            ::SetPixel(hdc,ws+j,hs+i,RGB(r[i][j],g[i][j],b[i][j]));
        }
    }
}
#endif
void Picture::GaussianBlur(int mxstep)
{
    vector<int> vec;
    int *tmat=new int[maxw*maxh];
    int q[min(maxw*maxh,(4*mxstep*mxstep)+10)][2];
    short *tstep=new short[maxw*maxh];
    memset(tstep,-1,sizeof(short)*maxw*maxh);
    for (int k=0; k<3; k++)
    {
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                vec.clear();
                int head=-1,tail=0;
                q[0][0]=i,q[0][1]=j;
                tstep[i*maxw+j]=0;
                int x,y;
                vec.push_back(brg[k][i][j]);
                while (head<tail)
                {
                    x=q[++head][0];
                    y=q[head][1];
                    int sstep=tstep[x*maxw+y];
                    if (sstep==mxstep)continue;
                    for (int k2=0; k2<4; k2++)
                    {
                        x+=mov[k2][0],y+=mov[k2][1];
                        if (x>=0 && x<height && y>=0 && y<width && tstep[x*maxw+y]==-1)
                        {
                            vec.push_back(brg[k][x][y]);
                            tstep[x*maxw+y]=sstep+1;
                            q[++tail][0]=x;
                            q[tail][1]=y;
                        }
                        x-=mov[k2][0],y-=mov[k2][1];
                    }
                }
                for (int k2=0; k2<=tail; k2++)
                {
                    tstep[q[k2][0]*maxw+q[k2][1]]=-1;
                }
                int sum=0;
                for (int k2=0; k2<(int)vec.size(); k2++)
                    sum+=vec[k2];
                tmat[i*maxw+j]=sum/vec.size();
            }
        }
        for (int i=0; i<height; i++)
        {
            for (int j=0; j<width; j++)
            {
                brg[k][i][j]=tmat[i*maxw+j];
            }
        }
    }
    delete[] tmat;
    delete[] tstep;
}
void Picture::ContrastIncrease()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            for (int k=0; k<3; k++)
            {
                brg[k][i][j]=Gaussian_Distribution_h(brg[k][i][j]);
            }
        }
    }
}
int Picture::GetWidth()
{
    return width;
}
int Picture::GetHeight()
{
    return height;
}
int Picture::GetPixel(int x,int y)
{
    return (r[x][y]<<16)+(g[x][y]<<8)+b[x][y];
}
void Picture::SetPixel(int x,int y,int rgbval)
{
    r[x][y]=rgbval>>16;
    rgbval-=r[x][y]<<16;
    g[x][y]=rgbval>>8;
    rgbval-=g[x][y]<<8;
    b[x][y]=rgbval;
}
void Picture::OnlyGreen()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            r[i][j]=b[i][j]=g[i][j];
        }
    }
}
void Picture::OnlyBlue()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            r[i][j]=g[i][j]=b[i][j];
        }
    }
}
void Picture::OnlyRed()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            g[i][j]=b[i][j]=r[i][j];
        }
    }
}
void Picture::operator = (const Picture &picd)
{
    Init(picd);
}
