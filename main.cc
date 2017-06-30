#include "plot.h"

#include <qapplication.h>
#include <qpushbutton.h>


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Ui::Plot plot;
    plot.show();
    return a.exec();
}
