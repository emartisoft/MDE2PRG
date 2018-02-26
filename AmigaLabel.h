/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Label
 */

#ifndef AMIGALABEL_H_INCLUDED
#define AMIGALABEL_H_INCLUDED

#include <FL/Fl.H>
#include <FL/Fl_Box.H>

class FL_EXPORT AmigaLabel : public Fl_Box
{
public:
    AmigaLabel(int x, int y, int w, int h, const char* title);
    ~AmigaLabel();
};

#endif // AMIGALABEL_H_INCLUDED
