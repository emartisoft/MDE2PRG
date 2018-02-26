/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Label
 */

#include "AmigaLabel.h"

AmigaLabel::AmigaLabel(int x, int y, int w, int h, const char* title=0) : Fl_Box(x,y,w,h,title)
{
    labelfont(FL_HELVETICA);
    box(FL_NO_BOX);
    align(FL_ALIGN_INSIDE | FL_ALIGN_LEFT);
}

AmigaLabel::~AmigaLabel()
{

}
