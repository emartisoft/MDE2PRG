/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Button
 */

#include "AmigaButton.h"

AmigaButton::AmigaButton(int x, int y, int w, int h, const char* title=0) : Fl_Button(x,y,w,AMIGA_BUTTON_HEIGHT,title)
{
    labelfont(FL_HELVETICA);
}

AmigaButton::~AmigaButton()
{
}

void AmigaButton::draw()
{
    if(value())
    {
        fl_rectf(x(),y(),w()-1,AMIGA_BUTTON_HEIGHT-1, BLACK);
        fl_rectf(x()+1,y()+1,w()-1,AMIGA_BUTTON_HEIGHT-1, WHITE);
        fl_rectf(x()+1,y()+1,w()-2,AMIGA_BUTTON_HEIGHT-2, BLUE);
    }
    else
    {
        fl_rectf(x(),y(),w()-1,AMIGA_BUTTON_HEIGHT-1, WHITE);
        fl_rectf(x()+1,y()+1,w()-1,AMIGA_BUTTON_HEIGHT-1, BLACK);
        fl_rectf(x()+1,y()+1,w()-2,AMIGA_BUTTON_HEIGHT-2, BGCOLOR);
    }

    Fl_Button::draw_label();
}
