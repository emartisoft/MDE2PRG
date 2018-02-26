/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Window
 */

#ifndef AMIGAWINDOW_H_INCLUDED
#define AMIGAWINDOW_H_INCLUDED

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>

#include "AmigaColorDefines.h"

//  button size defines
#define RESIZEBUTTON_WIDTH  36
#define RESIZEBUTTON_HEIGHT 20
#define CLOSEBUTTON_WIDTH   40
#define CLOSEBUTTON_HEIGHT  22
#define DRAGTITLEBAR_HEIGHT 22

// minimum window size
#define MINIMUM_WIDTH   680
#define MINIMUM_HEIGHT  360

class FL_EXPORT AmigaWindow : public Fl_Double_Window
{
public:
    AmigaWindow(int x, int y, int w, int h, const char* title);
    ~AmigaWindow();
    void setTitle(const char* title);
protected:
    int handle(int event);
    void draw();
    bool closeButtonPressed;
    const char* _title;
};
#endif // AMIGAWINDOW_H_INCLUDED
