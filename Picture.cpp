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
    note=new char[NOTE_LEN];
}
Picture::Picture(const Picture &picb)
{
    Init(picb);
    note=new char[NOTE_LEN];
}
Picture::~Picture()
{
    delete[] note;
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
    fgets(note,NOTE_LEN*sizeof(char),infile);
    if (!strstr(note,"P3"))
    {
        fprintf(stderr,"Wrong File!\n");
        exit(0);
    }
    fgets(note,NOTE_LEN*sizeof(char),infile);
    fscanf(infile,"%d %d\n",&width,&height);
    int maxval;
    fscanf(infile,"%d",&maxval);
    if (maxval!=255)
    {
        fprintf(stderr,"Wrong File Format!\n");
        exit(0);
    }
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            fscanf(infile,"%d %d %d",&r[i][j],&g[i][j],&b[i][j]);
    fclose(infile);
}

void Picture::PrintIntoFile(const char * file_name)const
{
    FILE *outfile=fopen(file_name,"w");
    fprintf(outfile,"P3\n");
    fprintf(outfile,"%s",note);
    fprintf(outfile,"%d %d\n",width,height);
    fprintf(outfile,"255\n");
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            fprintf(outfile,"%d %d %d  ",r[i][j],g[i][j],b[i][j]);
        }
        fprintf(outfile,"\n");
    }
    fclose(outfile);
}
void Picture::PrintPicture(FILE *outfile)const
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            fprintf(outfile,"[%d,%d,%d]\n",r[i][j],g[i][j],b[i][j]);
        }
        fprintf(outfile,"\n");
    }
}

#ifdef WIN32
void Picture::Paint(HDC hdc,int hs=0,int ws=0)const
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
int Picture::GetWidth()const
{
    return width;
}
int Picture::GetHeight()const
{
    return height;
}

void Picture::SetHeight(int nh)
{
    this->height=nh;
}
void Picture::SetWidth(int nw)
{
    this->width=nw;
}
int Picture::GetPixel(int x,int y)const
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
bool Picture::IsWhite(int x,int y)const
{
    return r[x][y]+g[x][y]+b[x][y]>240*3;
}
bool Picture::IsBlack(int x,int y)const
{
    return r[x][y]+g[x][y]+b[x][y]<15*3;
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
void Picture::FillWord(int col)
{
    const int cdiff=20;
    int *qx=new int[maxw*maxh];
    int *qy=new int[maxw*maxh];
    int *vis=new int[maxw*maxh];
    int *nrgb=new int[maxw*maxh];
    int *bdis=new int[maxw*maxh];
    memset(vis,0,sizeof(int)*maxw*maxh);
    memset(bdis,-1,sizeof(int)*maxw*maxh);
    int head=-1,tail=0;
    int cst;
    int bfstime=0;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (IsWhite(i,j))
            {
                head=-1,tail=0;
                qx[0]=i,qy[0]=j;
                vis[i*maxw+j]=++bfstime;
                int x,y;
                while (head<tail)
                {
                    x=qx[++head],y=qy[head];
                    for (int k=0; k<4; k++)
                    {
                        x+=mov[k][0],y+=mov[k][1];
                        if (x>=0 && x<height && y>=0 && y<width && vis[x*maxw+y]!=bfstime)
                        {
                            if (IsBlack(x,y))
                            {
                                bdis[i*maxw+j]=abs(x-i)+abs(y-j);
                                break;
                            }
                            vis[x*maxw+y]=bfstime;
                            qx[++tail]=x;
                            qy[tail]=y;
                        }
                        x-=mov[k][0],y-=mov[k][1];
                    }
                }
      //          printf("BlackDis[%d,%d]:%d\n",i,j,bdis[i*maxw+j]);
            }
        }
    }
    memset(vis,0,sizeof(int)*maxw*maxh);
    //PrintPicture(stdout);
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (vis[i*maxw+j])continue;
            tail=0;
            head=-1;
            qx[tail]=i,qy[tail]=j;
            int x,y;
            int psum=0;
            while (head<tail)
            {
                ++head;
                x=qx[head];
                y=qy[head];
                psum+=r[x][y]+g[x][y]+b[x][y];
                cst=GetPixel(x,y);
                for (int k=0; k<4; k++)
                {
                    x+=mov[k][0],y+=mov[k][1];
                    if (x>=0 && x<height && y>=0 && y<width && !vis[x*maxw+y] && RGBdiff(GetPixel(x,y),cst)<cdiff)
                    {
                        tail++;
                        qx[tail]=x,qy[tail]=y;
                        vis[x*maxw+y]=true;
                    }
                    x-=mov[k][0],y-=mov[k][1];
                }
            }
            printf("Tail Size:%d\n",tail+1);
            printf("Averange Color:%d\n",psum/(tail+1)/3);
            bool flag=true;
            for (int k=0;k<=tail;k++)
            {
                if (IsWhite(qx[k],qy[k]) && bdis[qx[k]*maxw+qy[k]]>15)
                {
                    flag=false;
                    break;
                }
            }
            if (tail<width*height*0.01 && psum/(tail+1)/3>200 && flag)
            {
                for (int k=0; k<=tail; k++)
                {
                    nrgb[qx[k]*maxw+qy[k]]=col;
                }
            }
            else
            {
                for (int k=0; k<=tail; k++)
                {
                    nrgb[qx[k]*maxw+qy[k]]=GetPixel(qx[k],qy[k]);
                }
            }
        }
    }
    for (int i=0; i<height; i++)
        for (int j=0; j<width; j++)
            SetPixel(i,j,nrgb[i*maxw+j]);
    delete[] qx;
    delete[] qy;
    delete[] vis;
}
void Picture::BandW()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            if (r[i][j]+g[i][j]+b[i][j]>200*3)
            {
                r[i][j]=g[i][j]=b[i][j]=255;
            }
            else
            {
                r[i][j]=g[i][j]=b[i][j]=0;
            }
        }
    }
}

void Picture::Contract()
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
        }
    }
}
