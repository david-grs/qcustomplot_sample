#include "plot.h"

#include <qapplication.h>
#include <qpushbutton.h>


QColor GenColor()
{
    return QColor(std::rand() % 255, std::rand() % 255, std::rand() % 255);
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
