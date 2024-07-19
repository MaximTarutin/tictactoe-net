#include "maxscreensize.h"

//------------------- Ширина экрана ------------------------------

int MaxScreenSize::Screen_Width()
{
    QScreen *screen = QApplication::screens().at(0);
    int _width_ = screen->size().width();
    return(_width_);
}


//------------------- Высота экрана ------------------------------

int MaxScreenSize::Screen_Height()
{
    QScreen *screen = QApplication::screens().at(0);
    int _heighrt_ = screen->size().height();
    return(_heighrt_);
}
