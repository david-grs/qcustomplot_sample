#include "window.h"
#include "stream_plot.h"
#include "utils.h"

namespace Ui {

Window::Window()
{
    mPlot = new StreamPlot(this, 600);

    int i = 0;
    for(auto x : GenPoints<10>()())
    {
        auto now = QDateTime::currentDateTime().addSecs(-60.0 * (9 - i++));
        mPlot->Push(now, x.y, x.color);
    }

    resize(1000, 200);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setCentralWidget(mPlot);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]()
    {
        static int i = 0;
        if ((++i) % 5 == 0)
            mPlot->Push(QDateTime::currentDateTime(), std::rand() % 100, GenColorPre());
    });

    timer->start(1000);

    mPlot->installEventFilter(this);
}

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
