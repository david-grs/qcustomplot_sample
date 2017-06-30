#include "plot.h"

#include <qapplication.h>
#include <qpushbutton.h>

#include <iostream>

QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand() * 1000) % 255; };
    auto alpha = []() -> int { return std::abs(std::rand() * 1000) % 100 + 155; };
    return QColor(color(), color(), color(), alpha());
}

struct Point
{
    double x;
    double y;
    QColor color;
};

int main( int argc, char **argv )
{
    QApplication a( argc, argv );
    Ui::Plot plot;

    for(auto x : {Point{1, 2, GenColor()}, Point{4, 10, GenColor()}, Point{5, 3, GenColor()}, Point{20, 15, GenColor()}})
        plot.Push(x.x, x.y, x.color);

    plot.show();
    return a.exec();
}
