#include "plot.h"

#include <qapplication.h>
#include <qpushbutton.h>

#include <iostream>
#include <cstdlib>
#include <array>

struct Point
{
    double x;
    double y;
    QColor color;
};

QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand()) % 255; };
    auto alpha = []() -> int { return std::abs(std::rand()) % 64 + 180; };
    return QColor(color(), color(), color(), alpha());
}

Point GenPoint(double x) { return {x, double(std::rand() % 100), GenColor()}; }

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

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    Ui::Plot plot;

    int i = 0;
    for(auto x : GenPoints<10>()())
    {
        auto now = QDateTime::currentDateTime().addSecs(-60.0 * (9 - i++));
        plot.Push(now, x.y, x.color);
    }

    plot.resize(800, 600);
    plot.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    plot.show();

    return a.exec();
}
