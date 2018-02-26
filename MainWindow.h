/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: MDE formatlı programları PRG formatına dönüştürür
 */

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include "AmigaWindow.h"
#include "AmigaButton.h"
#include "AmigaLabel.h"

#include <FL/Fl.H>
#include <FL/fl_ask.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Browser.H>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdio>

#define MAX 256

class MainWindow : public AmigaWindow
{
public:
    MainWindow();
    ~MainWindow();
private:
    Fl_Browser *fblog;
    unsigned int hex2dec(const std::string& hex_text);
    int ConvertToPrg();
    void InitializeComponents();
    void draw();
    static void st_bConvertEvent(Fl_Widget* w,void* data);
    inline void bConvertEvent(Fl_Widget *w);
    static void st_bAboutEvent(Fl_Widget* w,void* data);
    inline void bAboutEvent(Fl_Widget *w);


};

#endif // MAINWINDOW_H_INCLUDED
