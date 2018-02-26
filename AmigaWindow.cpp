/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: Amiga Window
 */

#include "AmigaWindow.h"

AmigaWindow::AmigaWindow(int x, int y, int w, int h, const char* title=0) : Fl_Double_Window(x,y,w,h,title)
{
    clear_border();
    color(BGCOLOR);
    setTitle(title);
    closeButtonPressed= false;
}

AmigaWindow::~AmigaWindow()
{
}

void AmigaWindow::setTitle(const char* title)
{
    _title=title;
    redraw();
}

void AmigaWindow::draw()
{
    Fl_Double_Window::draw();
    //top
    fl_rectf(40,0,w()-40,2,WHITE);
    fl_rectf(40,2,w()-40,18,BLUE);
    fl_rectf(40,20,w()-40,2,BLACK);

    //top right buttons
    fl_rectf(w()-94,2,2,18,BLACK);
    fl_rectf(w()-92,2,2,18,WHITE);
    fl_rect(w()-84,4,26,14,BLACK);
    fl_rect(w()-83,5,24,12,BLACK);
    fl_rectf(w()-82,6,12,6,BLACK);
    fl_rectf(w()-80,6,6,4,WHITE);

    fl_rectf(w()-50,2,2,18,BLACK);
    fl_rectf(w()-48,2,2,18,WHITE);

    fl_rectf(w()-38,4,22,10,BLACK);
    fl_rectf(w()-36,6,18,6,BGCOLOR);

    fl_rectf(w()-30,8,22,10,BLACK);
    fl_rectf(w()-28,10,18,6,WHITE);

    fl_rectf(w()-2,2,2,20,BLACK);

    //close button - normal - 40x22
    fl_rectf(0,0,40,22,WHITE);
    fl_rectf(2,2,36,20,BLACK);
    fl_rectf(2,2,34,18,BLUE);
    fl_rectf(14,6,10,10,BLACK);
    fl_rectf(16,8,6,6,WHITE);
    fl_rectf(38,20,2,2,BLACK);

    if (closeButtonPressed)
    {
        // close button pressed
        fl_rectf(0,0,38,22,BLACK);
        fl_rectf(2,2,36,20,WHITE);
        fl_rectf(2,2,34,18,BLUE);
        fl_rectf(14,6,10,10,BLACK);
        fl_rectf(16,8,6,6,BGCOLOR);
        fl_rectf(38,20,2,2,BLACK);
    }

    // set title
    fl_font(FL_HELVETICA_BOLD, 14);
    fl_color(BLACK);
    fl_draw(_title,44,16);

    //left side
    fl_rectf(0,22,2,h()-22,WHITE);
    fl_rectf(2,22,4,h()-22,BLUE);
    fl_rectf(6,22,2,h()-22,BLACK);

    //right side
    fl_rectf(w()-8,22,2,h()-22,WHITE);
    fl_rectf(w()-6,22,4,h()-22,BLUE);
    fl_rectf(w()-2,22,2,h()-22,BLACK);

    fl_rectf(8,h()-20,w()-10,2,WHITE);
    fl_rectf(2,h()-18,w()-4,16,BLUE);
    fl_rectf(2,h()-2,w()-2,2,BLACK);

    //resize button
    fl_rectf(w()-36,h()-18,2,16,WHITE);

    fl_rectf(w()-28,h()-8,22,4,BLACK);
    fl_rectf(w()-24,h()-10,18,2,BLACK);
    fl_rectf(w()-20,h()-12,14,2,BLACK);
    fl_rectf(w()-16,h()-14,10,2,BLACK);
    fl_rectf(w()-12,h()-16,6,2,BLACK);

    fl_rectf(w()-24,h()-8,16,2,WHITE);
    fl_rectf(w()-20,h()-10,12,2,WHITE);
    fl_rectf(w()-16,h()-12,8,2,WHITE);
    fl_rectf(w()-12,h()-14,4,2,WHITE);

}

int AmigaWindow::handle(int event)
{
    static int xoff = 0, yoff = 0;
    int ret = Fl_Double_Window::handle(event);
    switch ( event ) {

        case FL_PUSH:
                if ( Fl::event_button() == FL_LEFT_MOUSE ) {
                            xoff = x() - Fl::event_x_root();
                            yoff = y() - Fl::event_y_root();

                            // close button
                            if((-xoff<CLOSEBUTTON_WIDTH)&&(-yoff<CLOSEBUTTON_HEIGHT))
                            {
                                closeButtonPressed=true;
                                redraw();
                            }

                            ret = 1;
                }
            break;

        case FL_DRAG:
                if ( Fl::event_button() == FL_LEFT_MOUSE ){
                    /*
                    if ((-(x() - Fl::event_x_root())>w()-RESIZEBUTTON_WIDTH)&&(-(y() - Fl::event_y_root())>h()-RESIZEBUTTON_HEIGHT))
                    {// resize window
                        int newWidth = (Fl::event_x_root()-x()<MINIMUM_WIDTH)? MINIMUM_WIDTH : Fl::event_x_root()-x();
                        int newHeight= (Fl::event_y_root()-y()<MINIMUM_HEIGHT) ? MINIMUM_HEIGHT : Fl::event_y_root()-y();
                        size(newWidth, newHeight);
                        default_cursor(FL_CURSOR_NWSE);
                    }
                    */

                    if ((-yoff<DRAGTITLEBAR_HEIGHT)&&(-xoff>CLOSEBUTTON_WIDTH))
                    {// drag window
                        position(xoff + Fl::event_x_root(), yoff + Fl::event_y_root());
                        default_cursor(FL_CURSOR_MOVE);
                    }

                    redraw();
                    ret = 1;
                }
                break;

        case FL_RELEASE:
                if ( Fl::event_button() == FL_LEFT_MOUSE) {
                    default_cursor(FL_CURSOR_DEFAULT);
                    show();
                    // close window
                    //if((-xoff<CLOSEBUTTON_WIDTH)&&(-yoff<CLOSEBUTTON_HEIGHT))
                    if(closeButtonPressed)
                    {
                        exit(0);
                    }
                    ret = 1;
                }
                break;
    }
    return(ret);
}



