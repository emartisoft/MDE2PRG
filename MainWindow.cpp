/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: MDE formatlı programları PRG formatına dönüştürür
 */

#include "MainWindow.h"
#include "pic.xpm"

MainWindow::MainWindow() : AmigaWindow(100,100,680,360,"MDE2PRG 1.0")
{
    InitializeComponents();
}

MainWindow::~MainWindow()
{

}

unsigned int MainWindow::hex2dec(const std::string& hex_text)
{
    unsigned int value = 0;
    const unsigned int length = hex_text.length();
    for (unsigned int i = 0; i < length; ++i)
    {
        unsigned char c = hex_text[i];
        if ((c >= '0') && (c <= '9'))
        {
           value = value * 16 + (c - '0');
        }
        else
        {
          c = toupper(c);
          if ((c >= 'A') && (c <= 'F'))
          {
             value = value * 16 + (c - 'A') + 10;
          }
        }
    }
    return value;
}

int MainWindow::ConvertToPrg()
{
    int totalbyte=0;
    int size = 1024, pos;
    int c;
    char *buffer = (char *)malloc(size);
    char msg[1024];

    bool bStartAddr;

    Fl_File_Chooser chooser(".",                        // directory
                            "*",                        // filter
                            Fl_File_Chooser::SINGLE,    // chooser type
                            "MDE Formatlı Dosya Seçimi");        // title
    chooser.show();

    while(chooser.shown())
        { Fl::wait(); }

    if ( chooser.value() == NULL )
        { return 2; }

    std::string prgfile= std::string(chooser.value());
    prgfile.append(".prg");

    FILE *fprg = fopen(prgfile.c_str(), "wb");
    FILE *f = fopen(chooser.value(), "r");
    if(f && fprg)
    {
      bStartAddr=true;
      do
      {
        pos = 0;
        do
        {
          c = fgetc(f);
          if(c != EOF) buffer[pos++] = (char)c;
          if(pos >= size - 1)
          {
            size *=2;
            buffer = (char*)realloc(buffer, size);
          }
        } while(c != EOF && c != '\n');
        buffer[pos] = 0;

        std::string line = std::string(buffer);
        if (line.length()>=33)
        {
                int cl, cr, ck, kt, ch;
                int dizi[8];

                cl = hex2dec(line.substr(2,2));

                if (bStartAddr)
                {
                    fputc((unsigned char) cl , fprg);
                    fputc((unsigned char) hex2dec(line.substr(0,2)) , fprg);
                    bStartAddr=false;
                }

                kt = hex2dec(line.substr(31,2));
                ch = 0;
                ck = 0;
                cr = 0;

                for(int i=0;i<8;i++)
                {
                  dizi[i]=hex2dec(line.substr(7+i*3,2));
                  cl += dizi[i];
                  if (cl>255) ch++;
                  cr = (cl & 128) / 128;
                  cl = (cl * 2) & 255;
                  ch = (ch * 2) + cr;
                }

                cr = 1;
                ck = (cl + ch + cr) & 255;

                if (ck == kt)
                {
                for(int i=0;i<8;i++)
                {
                    fputc((char)dizi[i], fprg);
                }
                totalbyte+=8;
                }
                else
                {
                    sprintf(msg, "@C1@s@i%s",chooser.value());
                    fblog->add(msg);
                    sprintf(msg, "@C1@s%d. satırda hatalı kodlama!",1+totalbyte/8);
                    fblog->add(msg);
                    sprintf(msg, "@C1@s%s", buffer);
                    fblog->add(msg);
                    
                    // delete file
                    fclose(fprg);
                    fclose(f);
                    free(buffer);
                    if(std::remove(prgfile.c_str())==0) fblog->add("@s@iHatalı PRG dosyası silindi"); else fblog->add("@s@iHatalı PRG dosya silme başarısız");
                    fblog->add("@_");
                    return 0;
                }
        }
      } while(c != EOF);
      fclose(f);
      fclose(fprg);
      totalbyte+=2;
      sprintf(msg, "@s@i%s", prgfile.c_str());
      fblog->add(msg);
      sprintf(msg, "@b@sBoyutu: %d bytes\n", totalbyte);
      fblog->add(msg);
      fblog->add("@_");

    }
    else
    {
        fblog->add("@C1File(s) in use");
        fblog->add("@_");
    }
    free(buffer);
    return 1;
}

void MainWindow::st_bConvertEvent(Fl_Widget* w,void* data)
{
    ((MainWindow*)data)->bConvertEvent(w);
}

inline void MainWindow::bConvertEvent(Fl_Widget *w)
{
    ConvertToPrg();
}

void MainWindow::st_bAboutEvent(Fl_Widget* w,void* data)
{
    ((MainWindow*)data)->bAboutEvent(w);
}

inline void MainWindow::bAboutEvent(Fl_Widget *w)
{
    fblog->add("@bMDE2PRG");
    fblog->add("@C4@fCoded by emarti, Murat Özdemir");
    fblog->add("@s@iFreeware (c) 2018, Sürüm 1.0");
    fblog->add("@s@iFor Linux & Windows");
    fblog->add("@s@iPowered by FLTK (Fast Light Toolkit)");
    fblog->add("@s@iWeb: https://github.com/emartisoft/MDE2PRG");
    fblog->add("@_");
}

void MainWindow::draw()
{
    AmigaWindow::draw();
    fl_draw_pixmap(pic_xpm,20,50);
}

void MainWindow::InitializeComponents()
{
    AmigaLabel *lText = new AmigaLabel(20,30,550,25,"Commodore Dergisi Program Döküm Ekindeki makine dili programlarını PRG formatına dönüştürür.");

    AmigaButton *bConvert = new AmigaButton(540,60,120,25,"Dönüştür");
    bConvert->callback(st_bConvertEvent, this);

    AmigaButton *bAbout = new AmigaButton(540,90,120,25,"Hakkında");
    bAbout->callback(st_bAboutEvent, this);

    fblog = new Fl_Browser(330,130,330,200);
    bAboutEvent(fblog);
}
