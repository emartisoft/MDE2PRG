/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Button
 */

#ifndef AMIGABUTTON_H_INCLUDED
#define AMIGABUTTON_H_INCLUDED

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>

#include "AmigaColorDefines.h"

#define AMIGA_BUTTON_HEIGHT 23

class FL_EXPORT AmigaButton : public Fl_Button
{
public:
    AmigaButton(int x, int y, int w, int h, const char* title);
    ~AmigaButton();
protected:
    void draw();
    void resize(int x,int y,int w,int h) {
      Fl_Button::resize(x,y,w,AMIGA_BUTTON_HEIGHT);
    }
};

#endif // AMIGABUTTON_H_INCLUDED
