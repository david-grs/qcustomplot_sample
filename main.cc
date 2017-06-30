#include "plot.h"

#include <qapplication.h>
#include <qpushbutton.h>


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Ui::Plot plot;

    for(auto x : {std::make_pair(1,2), std::make_pair(4,10), std::make_pair(6,8)})
        plot.Push(x.first, x.second);
        
    plot.show();
    return a.exec();
}
