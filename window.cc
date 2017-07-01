#include "window.h"

namespace Ui {

void Window::mousePressEvent(QMouseEvent *event)
{
    mPosition = event->pos();
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint diff = event->pos() - mPosition;
        QPoint newpos = this->pos() + diff;

        move(newpos);
    }
}

}
