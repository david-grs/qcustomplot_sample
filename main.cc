#include "thirdparty/qcustomplot.h"
#include <qapplication.h>
#include <qpushbutton.h>


int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    QCustomPlot plot;
    plot.show();
    return a.exec();
}
