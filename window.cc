#include "window.h"

namespace Ui {

bool Window::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() ==  QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        mousePressEvent(mouseEvent);
        return true;
    }
    else if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        mouseMoveEvent(mouseEvent);
        return true;
    }
    else
    {
        return QObject::eventFilter(obj, event);
    }
}

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

        this->move(newpos);
    }
}

}
