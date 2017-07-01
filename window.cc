#include "window.h"
#include "plot.h"

#include <cstdlib>
#include <array>

struct Point
{
    double x;
    double y;
    QColor color;
};

inline QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand()) % 255; };
    auto alpha = []() -> int { return std::abs(std::rand()) % 64 + 180; };
    return QColor(color(), color(), color(), alpha());
}

inline Point GenPoint(double x) { return {x, double(std::rand() % 100), GenColor()}; }

template <std::size_t N>
struct GenPoints
{
    std::array<Point, N> operator()()
    {
        return impl(std::make_index_sequence<N>());
    }

private:
    template <std::size_t... Is>
    std::array<Point, N> impl(std::index_sequence<Is...>)
    {
        return {GenPoint(Is)...};
    }
};

namespace Ui {

Window::Window()
{
    mPlot = new Plot(this);

    int i = 0;
    for(auto x : GenPoints<10>()())
    {
        auto now = QDateTime::currentDateTime().addSecs(-60.0 * (9 - i++));
        mPlot->Push(now, x.y, x.color);
    }

    resize(800, 600);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setCentralWidget(mPlot);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]()
    {
        static int i = 0;
        if ((++i) % 5 == 0)
            mPlot->Push(QDateTime::currentDateTime(), std::rand() % 100, GenColor());
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
