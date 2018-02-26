/*
 * Author : emarti, Murat Özdemir
 * Date   : 26.02.2018
 * Comment: MDE formatlı programları PRG formatına dönüştürür
 */

#include "MainWindow.h"

int main()
{
    MainWindow *aw = new MainWindow();
    aw->end();
    aw->show();
    return Fl::run();
}

