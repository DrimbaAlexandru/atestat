// (c) Drimba Alexandru, 2015
// Amu nu chiar copyright, da' nici ca impartim pe net si din-alea. OK? OK!

#include <iostream>
#include <time.h>
#include <fstream>
#include <sys/stat.h>
//#include <cmath>
#include <math.h>
//#include <stdio.h>

#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>

#define PI 3.14159
#define LOG 0
#define LIN 1

#define BTN_START_AV_UNSEL      strcat(relpath,"start unsel.png")
#define BTN_START_AV_SEL        strcat(relpath,"start sel.png")
#define BTN_START_UNAV_UNSEL    strcat(relpath,"start unav.png")
#define BTN_START_UNAV_SEL      strcat(relpath,"start unav sel.png")
#define BTN_LOAD_UNSEL          strcat(relpath,"load unsel.png")
#define BTN_LOAD_SEL            strcat(relpath,"load sel.png")
#define BTN_SETTINGS_SEL        strcat(relpath,"settings sel.png")
#define BTN_SETTINGS_UNSEL      strcat(relpath,"settings unsel.png")
#define BTN_EXIT_SEL            strcat(relpath,"exit sel.png")
#define BTN_EXIT_UNSEL          strcat(relpath,"exit unsel.png")
#define BTN_ANALYZE_TYPE_SEL    strcat(relpath,"anal type sel.png")
#define BTN_ANALYZE_TYPE_UNSEL  strcat(relpath,"anal type unsel.png")
#define BTN_FFT_SIZE_UNAV_SEL   strcat(relpath,"FFT unav sel.png")
#define BTN_FFT_SIZE_UNAV_UNSEL  strcat(relpath,"FFT unav unsel.png")
#define BTN_FFT_SIZE_UNDEF_SEL    strcat(relpath,"FFT size sel.png")
#define BTN_FFT_SIZE_UNDEF_UNSEL   strcat(relpath,"FFT size unsel.png")
#define BTN_FFT_512_SEL           strcat(relpath,"FFT 512 sel.png")
#define BTN_FFT_1024_SEL         strcat(relpath,"FFT 1024 sel.png")
#define BTN_FFT_2048_SEL        strcat(relpath,"FFT 2048 sel.png")
#define BTN_FFT_4096_SEL        strcat(relpath,"FFT 4096 sel.png")
#define BTN_FFT_8192_SEL        strcat(relpath,"FFT 8192 sel.png")
#define BTN_FFT_16384_SEL       strcat(relpath,"FFT 16384 sel.png")
#define BTN_FFT_32768_SEL       strcat(relpath,"FFT 32768 sel.png")
#define BTN_FFT_512_UNSEL       strcat(relpath,"FFT 512 unsel.png")
#define BTN_FFT_1024_UNSEL      strcat(relpath,"FFT 1024 unsel.png")
#define BTN_FFT_2048_UNSEL      strcat(relpath,"FFT 2048 unsel.png")
#define BTN_FFT_4096_UNSEL      strcat(relpath,"FFT 4096 unsel.png")
#define BTN_FFT_8192_UNSEL      strcat(relpath,"FFT 8192 unsel.png")
#define BTN_FFT_16384_UNSEL     strcat(relpath,"FFT 16384 unsel.png")
#define BTN_FFT_32768_UNSEL     strcat(relpath,"FFT 32768 unsel.png")
#define BTN_FREQ_RANGE_5_SEL    strcat(relpath,"FR 5 sel.png")
#define BTN_FREQ_RANGE_5_UNSEL  strcat(relpath,"FR 5 unsel.png")
#define BTN_FREQ_RANGE_50_SEL   strcat(relpath,"FR 50 sel.png")
#define BTN_FREQ_RANGE_50_UNSEL strcat(relpath,"FR 50 unsel.png")
#define BTN_SCALE_LIN_SEL       strcat(relpath,"scale lin sel.png")
#define BTN_SCALE_LIN_UNSEL     strcat(relpath,"scale lin unsel.png")
#define BTN_SCALE_LOG_SEL       strcat(relpath,"scale log sel.png")
#define BTN_SCALE_LOG_UNSEL     strcat(relpath,"scale log unsel.png")

#define BTN_BACK_SEL            strcat(relpath,"back sel.png")
#define BTN_BACK_UNSEL          strcat(relpath,"back unsel.png")
#define STATUS_BAR              strcat(relpath,"status bar.png")

#define WIN_EXITED              -1
#define WIN_MENU                0
#define WIN_SETTINGS            1
#define WIN_ANALYZE             2

#define STR_NO_MODIFY "\1"

using namespace std;

char path[256];
char relpath[256];
char l1[128],l2[128],l3[128],l4[128];
int screen_x = GetSystemMetrics(SM_CXSCREEN);;
int screen_y = GetSystemMetrics(SM_CYSCREEN);

void set_status_bar(char s1[128] ,char c1[128],
                    char s2[128] ,char c2[128],
                    char s3[128] ,char c3[128],
                    char s4[128] ,char c4[128]);

void ulong2str(  long n, char c[10])
{
    int p=0,nc=0;
    p=n;
    while(p>0)
    {
        p/=10;nc++;
    }
    p=0;
    while(n>0)
    {

        switch(n%10)
        {
            case 0:{c[nc-p-1]='0';break;}
            case 1:{c[nc-p-1]='1';break;}
            case 2:{c[nc-p-1]='2';break;}
            case 3:{c[nc-p-1]='3';break;}
            case 4:{c[nc-p-1]='4';break;}
            case 5:{c[nc-p-1]='5';break;}
            case 6:{c[nc-p-1]='6';break;}
            case 7:{c[nc-p-1]='7';break;}
            case 8:{c[nc-p-1]='8';break;}
            case 9:{c[nc-p-1]='9';break;}
            default:{c[nc-p-1]='E';break;}
        }
        p++;
        n/=10;
    }
    c[nc]='\0';
}
char four4bit2hex(unsigned  n)//--------------------- FOR DEBUG -------------------
{
    switch(n){
        case 0: return '0';
        case 1: return '1';
        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: return 0;}
}
struct comp
{
float i,r;
};


/*-----------------------------------------   DFT ------------------------------*/

float DFT (float frq, float x[44100], long N, long NYQUIST_FRQ)
{

    float amp;
    long n;
    comp xk;

        xk.i=0;
        xk.r=0;
        for(n=0;n<N-1;n++)
        {
            xk.r+=x[n]*(cos(-2*PI/NYQUIST_FRQ*frq*n));
            xk.i+=x[n]*(sin(-2*PI/NYQUIST_FRQ*frq*n));
        }
        amp=sqrt(xk.r*xk.r+xk.i*xk.i)/N;
        //if(amp<0.0000001) amp=0;
        return amp;
}

// ------------------------------- OPEN FILE WINDOW ----------------------
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char *OpenDialog(HWND);
HWND ghwndEdit;
#define IDM_FILE_NEW 1

void OpenDialog(HWND hwnd, char filepath[260])
{
  OPENFILENAME ofn;
  TCHAR szFile[MAX_PATH];

  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.lpstrFile = szFile;
  ofn.lpstrFile[0] = '\0';
  ofn.hwndOwner = hwnd;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = TEXT("Wav files(*.wav)\0*.wav\0");
  ofn.nFilterIndex = 1;
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrFileTitle = NULL;
  ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

  if(GetOpenFileName(&ofn))
      {//LoadFile(ofn.lpstrFile);
        CloseWindow(hwnd);
       //std::cout<<ofn.lpstrFile;
       strcpy(filepath,ofn.lpstrFile);
       }else
    filepath[0]=0;
}
// --------------------------------- FFT --------------------------------

comp inc(comp a,  int n,  int N)
{
    comp r;
    r.r=a.r*(cos(-2*PI*n/N))-a.i*(sin(-2*PI*n/N));
    r.i=a.r*(sin(-2*PI*n/N))+a.i*(cos(-2*PI*n/N));
    return r;
}
comp ad(comp a,comp b)
{
    comp r;
    r.r=a.r+b.r;
    r.i=a.i+b.i;
    return r;
}
comp sc(comp a,comp b)
{
    comp r;
    r.r=a.r-b.r;
    r.i=a.i-b.i;
    return r;
}

void butterfly(comp BUF[],  int N)
{
      int i;

    if(N>2)
    {
        comp BUF_PAR[N/2],BUF_IMPAR[N/2];

        for(i=0;i<N/2;i++)
        {
         BUF_PAR[i].r=BUF[i*2].r;
         BUF_PAR[i].i=BUF[i*2].i;
         BUF_IMPAR[i].r=BUF[i*2+1].r;
         BUF_IMPAR[i].i=BUF[i*2+1].i;
         }
         butterfly(BUF_PAR,N/2);
         butterfly(BUF_IMPAR,N/2);

        for(i=0;i<N/2;i++)
        {
         BUF[i].r=BUF_PAR[i].r;
         BUF[i].i=BUF_PAR[i].i;
         BUF[i+N/2].r=BUF_IMPAR[i].r;
         BUF[i+N/2].i=BUF_IMPAR[i].i;
        }
    }
  /*  comp BUF_INIT[N];
    for(i=0;i<N;i++)
    {
        BUF_INIT[i].r=BUF[i].r;
        BUF_INIT[i].i=BUF[i].i;
    }*/

//---//
    comp a1,a2;
    for (i=0;i<N/2;i++)
    {
        a1.i=BUF[i].i;
        a1.r=BUF[i].r;
        a2.i=BUF[i+N/2].i;
        a2.r=BUF[i+N/2].r;
        BUF[i]=ad((BUF[i]),inc(BUF[N/2+i],i,N));
        BUF[i+N/2]=sc(a1,inc(a2,i,N));
    }

    /*for(i=N/2;i<N;i++)
    {
        BUF[i]=sc((BUF_INIT[i-N/2]),inc(BUF_INIT[i],i-N/2,N));
    }*/

}
void incrucisare(comp* v1, comp* v2, int n, int N)
{
    comp x,y;
    x=*v1;y=*v2;

    *v1=ad(inc(y,n,N),x);
    *v2=sc(x,inc(y,n,N));
}
void butterfly2(comp BUF[], int N)
{
    int i,j,k,l;

    for(k=1;k<N;k*=2)
        {for(i=0;i<N/k/2;i++)
            for(j=0;j<k;j++)
            {
                incrucisare(&BUF[i*k*2+j],&BUF[i*k*2+j+k],j,k*2);
                //cout<<i*k*2+j<<" "<<i*k*2+j+k<<" "<<j<<" "<<k*2<<endl;
            }
            /*cout<<endl<<endl;
            for(l=0;l<N;l++)
                cout<<BUF[l].r<<"-"<<BUF[l].i<<" ";
            cout<<endl<<endl;*/
        }
}
void FFT(float BUF_INIT[],long N)
{
    comp BUF[N];
    int i;
    int lista_pozitii[N];
    lista_pozitii[0]=0;
    int distanta=N/2;
    for(distanta=1;distanta<N;distanta*=2)
        for(i=distanta;i<distanta*2;i++)
            lista_pozitii[i]=N/distanta/2+lista_pozitii[i-distanta];

    //for(i=0;i<N;i++)
    //    cout<<lista_pozitii[i]<< " " ;

    for(i=0;i<N;i++)
    {
        BUF[i].r=BUF_INIT[lista_pozitii[i]];
        //cout<<BUF[i].r<<" ";
        BUF[i].i=0;
    }
    butterfly2(BUF,N);
    for(i=0;i<N;i++)
        BUF_INIT[i]=sqrt(BUF[i].r*BUF[i].r+BUF[i].i*BUF[i].i)/N;
}
/*
void FFT(float BUF[],long N)
{
    comp BUF_COMP[N];
    int i;
    for(i=0;i<N;i++)
    {
        BUF_COMP[i].r=BUF[i];
        BUF_COMP[i].i=0;
    }
    butterfly(BUF_COMP,N);
    for(i=0;i<N;i++)
        BUF[i]=sqrt(BUF_COMP[i].r*BUF_COMP[i].r+BUF_COMP[i].i*BUF_COMP[i].i)/N;
}
*/
// ------------------------------LINIAR 2 LOG ---------------------------

double coef=1.00596989474;

void lin2log(float BUF[],  int BUF_SIZE,int lowlim,float lg[1024],int SMPL_RT)
{

    float freq;int i;
    for(freq=lowlim,i=0;((freq<=lowlim*441)&&(i<1024));freq*=coef,i++)
    {
         lg[i]=BUF[long((freq)*BUF_SIZE/SMPL_RT)];
        //cout<<lg[i]<<endl;
        //i*SMPL_RT/BUF_SIZE
    }
    //getch();
}

// ------------------------- SMOOTH ----------------------------
void smooth(float BUF[],int n)
{
    int i,start,stop;
    start=0;
    while(start<n)
    {
        stop=start;
        while(BUF[stop]==BUF[start])
            stop++;
        for(i=start;i<stop;i++)
            BUF[i]=BUF[i]+(i-start)*(BUF[stop]-BUF[start])/(stop-start);
        start=stop;
    }
}
//--------------------------------UPDATE TIME -----------------
void updatetime(double &seconds)
{
    time_t timer;
    struct tm y2k;
    //double seconds;

    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;
    time(&timer);  /* get current time; same as: timer = time(NULL)  */

    seconds = difftime(timer,mktime(&y2k));
}
//- - -- - - - - - ROTUNJIRE -------
long pc(long n)
{
    int put=1;
    while(n>100)
    {
        put*=10;
        n/=10;
    }
    return n*put;
}
//---------------------FUCK THAT SHIT-------------------
long endian2long(char buf[5],int var)
{
    int i,n;long big=0;
    for(i=0;i<var;i++)
       {n=int(buf[i]);
        if(n<0)
            n+=256;
        big+=n*pow(256,i);}
    return big;
}

//  --------------------------HEADER-------------------
int getheader(char filename[256],long &SMPL_R,int &BTRT, int &CH,long &datasize, int &headsize)
{
    ifstream in(filename, ios::binary);
    char buf[5]={'\0'};
    int i;
    //headsize=0;

    in.read(buf,4);
    //RIFF descriptor
    if(strcmp(buf,"RIFF")!=0)
        return 0;
    cout<<buf<<" ";
    in.read(buf,4);
    //chunk size
    in.read(buf,4);
    //format
    if(strcmp(buf,"WAVE")!=0)
        return 0;
    cout<<buf<<" ";
    in.read(buf,4);
    //fmt sub-chunk
    if(strcmp(buf,"fmt ")!=0)
        return 0;
    cout<<buf<<" ";
    //subchumk 1 size
    long subchunk1size=0;
    in.read(buf,4);
    subchunk1size=endian2long(buf,4);

    cout<<subchunk1size<<" "<<endl;
    in.read(buf,2);
    //audio format
    int audioformat;
    audioformat=endian2long(buf,2);
    if(audioformat!=1)
        return 0;
    //channels number
    in.read(buf,2);
    CH=endian2long(buf,2);
    cout<<CH<<" channels"<<" "<<endl;
    //sample rate
    in.read(buf,4);
    SMPL_R=endian2long(buf,4);

    cout<<"sample rate:"<<SMPL_R<<" "<<endl;
    //BYTERATE
    long byterate;
    in.read(buf,4);
    byterate=endian2long(buf,4);
    //BLOCK ALIGN
    int blockalign;
    in.read(buf,2);
    blockalign=endian2long(buf,2);
    //BITRATE
    in.read(buf,2);
    BTRT=endian2long(buf,2);
    cout<<"bit rate:"<<BTRT<<" "<<endl;

    headsize=36;
    if(subchunk1size>16)
    in.read(buf,subchunk1size-16);
    headsize+=subchunk1size-16;

    in.read(buf,4);headsize+=4;
    cout<<buf<<" ";
    if(strcmp(buf,"fact")==0)
        {(in.read(buf,4));headsize+=4;
        long factchunkbullshitfuckthisshitsize=endian2long(buf,4);
        for(i=0;i<factchunkbullshitfuckthisshitsize;i++){in.read(buf,1);headsize+=1;}
        in.read(buf,4);headsize+=4;
        cout<<buf<<" ";}
    if(strcmp(buf,"data")!=0)
        {return 0;}
    in.read(buf,4);headsize+=4;
    datasize=endian2long(buf,4);
    cout<<datasize/CH/(BTRT/8)<<" samples"<<endl;
    cout<<datasize/CH/(BTRT/8)/SMPL_R<<" seconds"<<endl;
    return 1;
}
//FFT WINDOW
void FFT_windowing(char filename[256],sf::RenderWindow &win,int BUF_SIZE,int FFT_SIZE,int SCALE,int BASE_FRQ)
{
    if(filename[0])
    {
        long SAMPLE_RATE,chunk2size;
        int  BITRATE,    CHANNELS,    head_size;

        cout<<filename<<" "<<SAMPLE_RATE<<" "<<BITRATE<<" "<<CHANNELS<<" "<<chunk2size<<" "<<head_size;
        if(getheader(filename,SAMPLE_RATE,BITRATE,CHANNELS,chunk2size,head_size)==0)
            set_status_bar(l1,"THIS WAV FILE IS NOT VALID.",l2,"",l3,"",l4,"");
        else
            {
        cout<<endl<<endl<<"THIS WAV FILE IS VALID."<<endl;

        sf::Text text;
        sf::Font font;
        strcpy(relpath,path);
        font.loadFromFile(strcat(relpath,"arial.ttf"));
        text.setFont(font);
        text.setCharacterSize(16);
        text.setColor(sf::Color::White);

        int n1,n2;
        float sample,    LC_BUF[FFT_SIZE],  RC_BUF[FFT_SIZE];
        int paused=0,exit_by_esc=0;
        char buffer[2];
        long i;
        int n;
        ifstream vin(filename, ios::binary);
        ofstream out("C:/Users/Alex/Desktop/Olimpiada/atestat final/Drimba - Atestat 2015/Atestat Drimba Alexandru 2015 last try/out.txt");
        for(i=0;i<head_size;i++)
        {
            vin.read(buffer,1);
            /* n=(buffer[0]);
            if(n<0)n=n+256;
            if(i%16==0) cout<<endl;
            cout<<four4bit2hex(n/16);
            cout<<four4bit2hex(n%16);

            cout<<endl;
            cout<<buffer[0]<<"->"<<n;
            cout<<" ";*/
        }


        cout<<endl;
        cout<<endl;
        //ofstream out("samples.txt");

        // initwindow(screen_x,1000);
        sf::RenderWindow window(sf::VideoMode(screen_x,screen_y), "FFT",sf::Style::Fullscreen);

        window.clear();
        Sleep(1000);

        //int rgb;
        float pas;
        pas=BUF_SIZE*50/SAMPLE_RATE;
        char hz[10];
        int frq;
        int q;
        float logar[1024],oldlogar[1024];
        //PlaySound(filename, NULL, SND_ASYNC);
        sf::Music music;
        music.openFromFile(filename);
        music.play();

        sf::Clock clock;
        sf::Time taimu=clock.getElapsedTime(),dif,inittaimu=taimu,totaldelay=sf::seconds(0.0f),elapsed,starttaimu=taimu;
        window.clear();window.display();
        while (window.isOpen())
        {



        long k;
        sf::Event event;
        for(k=0;k<(chunk2size)/BUF_SIZE/CHANNELS/2;k++)
        {

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    {window.close();k=-2;}
            }
            while (win.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    {window.close();
                    k=-2;
                    win.close();
                    }
            }
            if(k==-1){window.close();break;}
            for(i=0;i<FFT_SIZE;i++)
            {
                LC_BUF[i]=0;
                RC_BUF[i]=0;
            }
        for(i=0;i<BUF_SIZE;i++)
        {
            vin.read(buffer,2);//get left channel
            n2=(buffer[0]);
            n1=(buffer[1]);

            if(n1<0)n1=n1+256;
            if(n2<0)n2=n2+256;

            if(n1<128) n1+=128;
            else if(n1>=128) n1-=128;

            sample=((n1-128)*256+n2);
            LC_BUF[i]=sample/32768;
            if(CHANNELS==2)
        {
            vin.read(buffer,2);//get right channel
            n2=(buffer[0]);
            n1=(buffer[1]);
            if(n1<0)n1=n1+256;
            if(n2<0)n2=n2+256;

        /*if(i%8==0) cout<<endl;
            cout<<four4bit2hex(n1/16);
            cout<<four4bit2hex(n1%16);
            cout<<" ";
            cout<<four4bit2hex(n2/16);
            cout<<four4bit2hex(n2%16);
            cout<<" ";*/

            if(n1<128) n1+=128;
            else if(n1>=128) n1-=128;
            sample=((n1-128)*256+n2);
            RC_BUF[i]=sample/32768;
            LC_BUF[i]=(RC_BUF[i]+LC_BUF[i])/2;
            LC_BUF[i]=LC_BUF[i]*(0.42-0.5*cos(2*PI*i/(FFT_SIZE-1))+0.08*cos(4*PI*i/(FFT_SIZE-1)));
        }
     /*
            out<<sample/32768<<endl;
    */
            /*cout<<endl;
            cout<<buffer[0]<<"->"<<n;*/
        }

/*
        frecv frecvente[1024];
        float frq;

        char hz[10];
        for(frq=25,i=0;(frq<NYQUIST_FRQ)&&(i<1024);frq*=1.00664521655,i++)
        {
        frecvente[i].frq=frq;
        frecvente[i].amp=DFT(frq, RC_BUF, BUF_SIZE, NYQUIST_FRQ);
        frecvente[i].amp*=25;
        if(frecvente[i].amp>1)frecvente[i].amp=1;
        //cout<<frecvente[i].frq<<" Hz - "<<frecvente[i].amp<<endl;
        int rgb=((frecvente[i].amp))*255;
        //setcolor(COLOR(rgb,rgb,rgb));
        //line((k*2)%1000,1024-i,(k+1)*2%1000,1024-i);
        if(rgb>0){
        putpixel((k*2)%1000,1024-i,COLOR(rgb,rgb,rgb));
        putpixel((k*2)%1000+1,1024-i,COLOR(rgb,rgb,rgb));
        }
        //line((k*2)%1000,1023-i,(k+1)*2%1000,1023-i);
        ulong2str(frq,hz);
        if(k==0) if(i%26==0) {setcolor(WHITE);line(1044,1024-i,1055,1024-i);outtextxy(1060,1016-i,strcat(hz,"Hz"));}
        }
*/

        FFT(LC_BUF,FFT_SIZE);

        /* setcolor(BLACK);
        line(k*2%1000,0,k*2%1000,1000);
        line(k*2%1000+1,0,k*2%1000+1,1000);*/
        for(frq=0;frq<1024;frq++)
            if(k!=0)
                 oldlogar[frq]=logar[frq];
            else oldlogar[frq]=0;

        if(SCALE==LOG)
            lin2log(LC_BUF,FFT_SIZE,BASE_FRQ,logar,SAMPLE_RATE);
            else
            for(frq=0;frq<1024;frq++)
                logar[frq]=LC_BUF[int(frq*float(FFT_SIZE)/2048*BASE_FRQ/50)];
        //smooth(logar,1024);
        sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128), 0),sf::Color(0,0,0)),
                    sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128)+BUF_SIZE*50/SAMPLE_RATE+1, screen_y),sf::Color(0,0,0))
                };
        window.draw(line, 2, sf::Lines);
        out<<k<<" - ";
        for(i=0;i<1024;i++)
        {


            //logar[i]=logar[i]*FFT_SIZE/BUF_SIZE;
logar[i]*=4;
            if(logar[i]>0.0000314)
                logar[i]=log2(logar[i])/(15)+1;

            logar[i]*=1;
            if(logar[i]>1)
                logar[i]=1;
            //logar[i]=sqrt(logar[i]);
            //logar[i]/=2;

        }
        smooth(logar,1024);
        //cout<<(k*BUF_SIZE*50/SAMPLE_RATE)%1024<<endl;
        for(q=0;q<2;q++)
        {
            for(i=0;i<1024;i++)
            {
                if(SCALE==LOG)
                    frq=pow(coef,i)*BASE_FRQ;
                else frq=i*float(SAMPLE_RATE/2048*BASE_FRQ/50);

                sf::Vertex line[] =
                {
                    sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128), screen_y-i*screen_y/1024),sf::Color(oldlogar[i]*255,oldlogar[i]*255,oldlogar[i]*255)),
                    sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128)+BUF_SIZE*50/SAMPLE_RATE+1, screen_y-i*screen_y/1024),sf::Color(logar[i]*255,logar[i]*255,logar[i]*255))
                };

                window.draw(line, 2, sf::Lines);

                if(k==0) if(i*screen_y/1024%26==0)
                {
                    ulong2str(pc(frq),hz);
                    sf::Vertex line[] =
                    {   sf::Vertex(sf::Vector2f((screen_x-128)+20, screen_y-i*screen_y/1024),sf::Color(255,255,255)),
                        sf::Vertex(sf::Vector2f((screen_x-128)+40, screen_y-i*screen_y/1024),sf::Color(255,255,255))
                    };
                    window.draw(line, 2, sf::Lines);
                    text.setCharacterSize(16);
                    text.setString(strcat(hz," Hz"));
                    text.setPosition((screen_x-128)+60, screen_y-8-i*screen_y/1024);
                    window.draw(text);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                   music.stop();
                   set_status_bar(l1,"Force exit by ESC!",l2,l2,l3,l3,l4,l4);
                   exit_by_esc=1;k=-2;window.close();break;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    { if(!paused) cout<<"for k="<<k<<" - PAUSED"<<endl;paused=1;}
            }

            if((q==0))
                {
                    while(1)
                    {
                        taimu=music.getPlayingOffset();
                        dif=taimu-inittaimu;
                        elapsed=(taimu);
                        totaldelay=sf::seconds(elapsed.asSeconds()-(k)*float(BUF_SIZE)/SAMPLE_RATE);
                        //cout<<totaldelay.asSeconds()<<endl;
                        if(totaldelay.asSeconds()>2)
                        {
                            //COMPUTING_SIZE_TOO_BIG=1;
                            cout<<"Time taken to process is too big and cannot sync with the audio. \nOperation aborted!"<<endl;
                            set_status_bar(l1,"Time taken to process is too big",
                                           l2,"and cannot sync with the audio.",
                                           l3,"Operation aborted!",
                                           l4,"Please change the FFT size.");
                            cout<<"Delay: "<<totaldelay.asSeconds()<<endl;
                            window.close();
                            k=-2;
                            break;
                        }
                       /* if(totaldelay.asSeconds()<=0)
                            Sleep(1);*/
                        if((totaldelay.asSeconds()<=2)&&((totaldelay.asSeconds()>0)))
                            {break;}
                    Sleep(50);
                    }
                //if(k!=-2)cout<<"for k="<<k<<" - "<< dif.asSeconds()<<" s; max: "<<float(BUF_SIZE)/SAMPLE_RATE<<" s; delay - "<<totaldelay.asSeconds()<<" s"<<endl;
                inittaimu=taimu;
                }
                if(paused) {music.pause();
                            while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) Sleep(20);}
                while(paused==1)
                {

                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                        {
                            paused=0;while(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) Sleep(20);
                            inittaimu=clock.getElapsedTime();
                            starttaimu=clock.getElapsedTime();
                            music.play();
                            break;
                        }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                        {
                            set_status_bar(l1,"Force exit by ESC!",l2,l2,l3,l3,l4,l4);
                            window.close();music.stop();
                            k=-2;break;
                        }
                    Sleep(50);
                }
            if((k*BUF_SIZE)/SAMPLE_RATE<((k+1)*BUF_SIZE)/SAMPLE_RATE)
                {
                ulong2str(k*BUF_SIZE/SAMPLE_RATE+1,hz);
                text.setString(strcat(hz," s"));
                text.setPosition((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128)-36,0);
                text.setCharacterSize(12);
                window.draw(text);
                sf::Vertex line[] =
                {   sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128),0),sf::Color(255,255,255)),
                    sf::Vertex(sf::Vector2f((k*BUF_SIZE*50/SAMPLE_RATE)%(screen_x-128),32),sf::Color(255,255,255))
                };
                window.draw(line, 2, sf::Lines);
                }
            window.display();
            }

         //if(k%500==0) if(k!=0){window.clear();}
        }
        if((!exit_by_esc)&&(window.isOpen()))
                 {
                while(window.isOpen())
                {
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            {window.close();k=-2;}
                    }
                    while (win.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            {window.close();
                            k=-2;
                            win.close();
                            }
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                    {
                   music.stop();
                   set_status_bar(l1,"End of file!",l2,"",l3,"",l4,"");
                   exit_by_esc=1;k=-2;window.close();break;
                   }
                }
                }

        }

    }
    }
}
//welcome window
void welcome_w()
{
    sf::RenderWindow hello(sf::VideoMode(384,256),"Spectrogram",sf::Style::None);
    sf::Texture texture;
    strcpy(relpath,path);
    texture.loadFromFile(strcat(relpath,"hello.bmp"));
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(float(384)/256, 1.0);
    hello.draw(sprite);
    hello.display();
    Sleep(2500);
    hello.close();
    Sleep(200);
}
//
void putsprite(sf::RenderWindow &win,char fpath[256],int x, int y)
{
    sf::Texture texture;
    sf::Sprite sprite;
    texture.loadFromFile(fpath);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    sprite.setScale(0.5f,0.5f);
    win.draw(sprite);
}
void clean_status_bar(sf::RenderWindow &win)
{
    sf::RectangleShape shape(sf::Vector2f(235, 60));
    shape.setFillColor(sf::Color(255, 255, 255));
    shape.setPosition(70,353);
    win.draw(shape);
}
void set_status_bar(char s1[128] ,char c1[128],
                    char s2[128] ,char c2[128],
                    char s3[128] ,char c3[128],
                    char s4[128] ,char c4[128])
{
        strcpy(s1,c1);
        strcpy(s2,c2);
        strcpy(s3,c3);
        strcpy(s4,c4);
}
void write_to_status_bar(sf::RenderWindow &win,char s1[128],char s2[128]={'\0'},char s3[128]={'\0'},char s4[128]={'\0'})
{
    //clean_status_bar(win);
    sf::Text text;
    sf::Font font;
    strcpy(relpath,path);
    font.loadFromFile(strcat(relpath,"arial.ttf"));
    text.setFont(font);
    text.setCharacterSize(14);
    text.setColor(sf::Color::Black);

    text.setString(s1);
    text.setPosition(70,353);
    win.draw(text);

    text.setString(s2);
    text.setPosition(70,368);
    win.draw(text);

    text.setString(s3);
    text.setPosition(70,383);
    win.draw(text);

    text.setString(s4);
    text.setPosition(70,398);
    win.draw(text);
}

void update_main_menu(sf::RenderWindow &win,int sel,int is_file_loaded,char s1[128],char s2[128],char s3[128],char s4[128])
{
    win.clear(sf::Color::White);
    sf::Text text;
    sf::Font font;
    strcpy(relpath,path);
    font.loadFromFile(strcat(relpath,"arial.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::Black);
    text.setString("Status bar:");
    text.setPosition(64,330);
    win.draw(text);
    write_to_status_bar(win,s1,s2,s3,s4);
    strcpy(relpath,path);
    putsprite(win,STATUS_BAR,64,350);
    strcpy(relpath,path);
    if(sel==0) if(is_file_loaded) putsprite(win,BTN_START_AV_SEL,64,25);
                            else  putsprite(win,BTN_START_UNAV_SEL,64,25);
    else       if(is_file_loaded) putsprite(win,BTN_START_AV_UNSEL,64,25);
                            else  putsprite(win,BTN_START_UNAV_UNSEL,64,25);
    strcpy(relpath,path);
    if(sel==1) putsprite(win,BTN_LOAD_SEL,64,100);
         else  putsprite(win,BTN_LOAD_UNSEL,64,100);
    strcpy(relpath,path);
    if(sel==2) putsprite(win,BTN_SETTINGS_SEL,64,175);
         else  putsprite(win,BTN_SETTINGS_UNSEL,64,175);
    strcpy(relpath,path);
    if(sel==3) putsprite(win,BTN_EXIT_SEL,64,250);
         else  putsprite(win,BTN_EXIT_UNSEL,64,250);
    win.display();
}

void update_settings_menu(sf::RenderWindow &win, int sel,int FFT_SIZE, int lowlim,int SCALE, char s1[128],char s2[128],char s3[128],char s4[128])
{
    win.clear(sf::Color::White);
    sf::Text text;
    sf::Font font;
    strcpy(relpath,path);
    font.loadFromFile(strcat(relpath,"arial.ttf"));
    text.setFont(font);
    text.setCharacterSize(16);
    text.setColor(sf::Color::Black);
    text.setString("Status bar:");
    text.setPosition(64,330);
    win.draw(text);
    write_to_status_bar(win,s1,s2,s3,s4);
    strcpy(relpath,path);
    putsprite(win,STATUS_BAR,64,350);
    strcpy(relpath,path);
    if(sel==0)
        switch(FFT_SIZE)
        {
            case 512:   {putsprite(win,BTN_FFT_512_SEL,64,25);break;}
            case 1024:  {putsprite(win,BTN_FFT_1024_SEL,64,25);break;}
            case 2048:  {putsprite(win,BTN_FFT_2048_SEL,64,25);break;}
            case 4096:  {putsprite(win,BTN_FFT_4096_SEL,64,25);break;}
            case 8192:  {putsprite(win,BTN_FFT_8192_SEL,64,25);break;}
            case 16384: {putsprite(win,BTN_FFT_16384_SEL,64,25);break;}
            case 32768: {putsprite(win,BTN_FFT_32768_SEL,64,25);break;}
            default:    {putsprite(win,BTN_FFT_SIZE_UNDEF_SEL,64,25);break;}
        }
    else
        switch(FFT_SIZE)
        {
            case 512:   {putsprite(win,BTN_FFT_512_UNSEL,64,25);break;}
            case 1024:  {putsprite(win,BTN_FFT_1024_UNSEL,64,25);break;}
            case 2048:  {putsprite(win,BTN_FFT_2048_UNSEL,64,25);break;}
            case 4096:  {putsprite(win,BTN_FFT_4096_UNSEL,64,25);break;}
            case 8192:  {putsprite(win,BTN_FFT_8192_UNSEL,64,25);break;}
            case 16384: {putsprite(win,BTN_FFT_16384_UNSEL,64,25);break;}
            case 32768: {putsprite(win,BTN_FFT_32768_UNSEL,64,25);break;}
            default:    {putsprite(win,BTN_FFT_SIZE_UNDEF_UNSEL,64,25);break;}
        }
    strcpy(relpath,path);
    if(sel==1)
        switch(lowlim)
        {   case 50:    {putsprite(win,BTN_FREQ_RANGE_50_SEL,64,100);break;}
            default:    putsprite(win,BTN_FREQ_RANGE_5_SEL,64,100);
        }
    else
        switch(lowlim)
        {   case 50:    {putsprite(win,BTN_FREQ_RANGE_50_UNSEL,64,100);break;}
            default:    {putsprite(win,BTN_FREQ_RANGE_5_UNSEL,64,100);break;}
        }
    strcpy(relpath,path);
    if(sel==2)
    switch(SCALE)
        {   case LIN:   {putsprite(win,BTN_SCALE_LIN_SEL,64,175);break;}
            default:    putsprite(win,BTN_SCALE_LOG_SEL,64,175);
        }
    else
        switch(SCALE)
        {   case LIN:   {putsprite(win,BTN_SCALE_LIN_UNSEL,64,175);break;}
            default:    putsprite(win,BTN_SCALE_LOG_UNSEL,64,175);
        }
    strcpy(relpath,path);
    if(sel==3) putsprite(win,BTN_BACK_SEL,64,250);
         else  putsprite(win,BTN_BACK_UNSEL,64,250);
    win.display();
}

void draw_main_menu(sf::RenderWindow &win,char filename[])
{

    int location=WIN_MENU,sel=0,is_file_loaded=(filename[0]!='\0');
    int set_sel=0;
    int  FFT_SIZE=8192, SCALE=LOG, BASE_FRQ=50;
    long BUF_SIZE;
    long SAMPLE_RATE,chunk2size;
    int  BITRATE,    CHANNELS,    head_size;

        sf::Text text;
        sf::Font font;
        strcpy(relpath,path);
        font.loadFromFile(strcat(relpath,"arial.ttf"));
        text.setFont(font);
        text.setCharacterSize(16);
        text.setColor(sf::Color::Black);
       // win.clear(sf::Color::White);

    while (win.isOpen())
    {
        sf::Event event;
        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
        }
    if(location==WIN_MENU)
    {

        update_main_menu(win,sel,is_file_loaded,l1,l2,l3,l4);
        while(location==WIN_MENU)
        {
            //getch();
            //while (win.pollEvent(event))
            if (event.type == sf::Event::Closed)
                {win.close();}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {win.close();break;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    Sleep(50);
                sel--;
                if(sel<0)sel+=4;
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    Sleep(50);
                sel++;
                if(sel>3)sel-=4;
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    Sleep(50);
                switch(sel)
                {
                    case 0:{if(is_file_loaded)location=WIN_ANALYZE;break;}
                    case 1:{OpenDialog(ghwndEdit,filename);
                            if(filename[0])
                                    {is_file_loaded=1;

                                    set_status_bar(l1,"Successfully loaded the WAV file.",l2,"",l3,"",l4,"");
                                    if(getheader(filename,SAMPLE_RATE,BITRATE,CHANNELS,chunk2size,head_size)==1)
                                        {if((BITRATE!=16)||(CHANNELS>2))
                                            set_status_bar(l1,l1,l2,"This WAV file is not supported.",l3,"",l4,"");
                                         else { strcpy(l2,"Sample rate: ");
                                                strcpy(l3,"Channels: ");
                                                strcpy(l4,"Lenght: ");
                                                char nr[10];
                                                ulong2str(SAMPLE_RATE,nr);
                                                strcat(l2,nr);
                                                ulong2str(CHANNELS,nr);
                                                strcat(l3,nr);
                                                ulong2str(chunk2size/CHANNELS/(BITRATE/8)/SAMPLE_RATE,nr);
                                                strcat(l4,nr);
                                                strcat(l4," s");

                                                }
                                        }
                                    }
                            else {is_file_loaded=0;
                                    set_status_bar(l1,"Error at loading the WAV file.",l2,"",l3,"",l4,"");}
                            break;}
                    case 2:{set_sel=0;location=WIN_SETTINGS;break;}
                    case 3:{win.close();location=WIN_EXITED;break;}
                    default:{break;}
                }
                break;
            }
//Sleep(1000);
        }
    }
    if(location==WIN_ANALYZE)
        {

            if(FFT_SIZE<2048) BUF_SIZE=FFT_SIZE;
                else BUF_SIZE=SAMPLE_RATE*FFT_SIZE/65536;
            //cout<<BUF_SIZE;
            set_status_bar(l1,"",l2,"",l3,"",l4,"");
            FFT_windowing(filename,win,BUF_SIZE,FFT_SIZE,SCALE,BASE_FRQ);location=WIN_MENU;}
    if(location==WIN_SETTINGS)
    {

        update_settings_menu(win,set_sel,FFT_SIZE,BASE_FRQ,SCALE,l1,l2,l3,l4);
        while(location==WIN_SETTINGS)
        {
            Sleep(50);
            win.pollEvent(event);
            if (event.type == sf::Event::Closed)
                {win.close();break;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {win.close();break;}

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    Sleep(20);
                set_sel--;
                if(set_sel<0)set_sel+=4;
                break;
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    Sleep(20);
                set_sel++;
                if(set_sel>3)set_sel-=4;
                break;
            }

            if(set_sel==0)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    Sleep(20);

                {if(FFT_SIZE==512)FFT_SIZE=32768;else FFT_SIZE/=2; break;};
                break;
            }
            if(set_sel==0)
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    Sleep(20);

                {if(FFT_SIZE==32768)FFT_SIZE=512;else FFT_SIZE*=2; break;};
                break;
            }


            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                while(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                    Sleep(20);
                switch(set_sel)
                {

                    case 1:{if(BASE_FRQ==50) BASE_FRQ=5; else BASE_FRQ=50; break;}
                    case 2:{if(SCALE==LOG) SCALE=LIN; else SCALE=LOG; break;}
                    case 3:{location=WIN_MENU;break;}
                    default:{break;}
                }
                break;
            }

        }
    }
    }
}

// --------------------------------- MAIN -------------------------------
int main()
{
  /*  ifstream in("cale.txt");
    in.get(path,256);*/
    GetCurrentDirectory(256,path);
    strcat(path,"/\0");
    welcome_w();
    char filename[256]={'\0'};
    sf::RenderWindow win(sf::VideoMode(384,512),"Main Menu");
    set_status_bar(l1,"Hello World!",l2,"",l3,"",l4,"");
    draw_main_menu(win,filename);
    //OpenDialog(ghwndEdit,filename);
    //long a,d;int b,c,e;
    //draw_main_menu(win,filename);
    //Sleep(1000);
    //getch();
    return 0;
}

//  ______ _____ _____   ___  _   _ _____ _____   _    _ _   ___   __  _   _ _____ _____ ___ ___ ___
//  | ___ \  ___/  __ \ / _ \| | | /  ___|  ___| | |  | | | | \ \ / / | \ | |  _  |_   _|__ \__ \__ \
//  | |_/ / |__ | /  \// /_\ \ | | \ `--.| |__   | |  | | |_| |\ V /  |  \| | | | | | |    ) | ) | ) |
//  | ___ \  __|| |    |  _  | | | |`--. \  __|  | |/\| |  _  | \ /   | . ` | | | | | |   / / / / / /
//  | |_/ / |___| \__/\| | | | |_| /\__/ / |___  \  /\  / | | | | |   | |\  \ \_/ / | |  |_| |_| |_|
//  \____/\____/ \____/\_| |_/\___/\____/\____/   \/  \/\_| |_/ \_/   \_| \_/\___/  \_/  (_) (_) (_)

