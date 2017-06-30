#include "thirdparty/qcustomplot.h"

#include <qapplication.h>
#include <qpushbutton.h>

namespace Ui {
    
class Plot : public QCustomPlot
{
Q_OBJECT

public:
    Plot(QWidget* pp = nullptr);

public slots:
    void OnValue(double v);

private slots:
    void OnMousePress(QMouseEvent*);
    void OnMouseWheel(QWheelEvent*);

private:
    void InitPlotArea();

    QVector<double> mTimeAxis;
    QCPGraph* mGraph = nullptr;
};

Plot::Plot(QWidget* pp) :
    QCustomPlot(pp)
{
    InitPlotArea();
}

void Plot::InitPlotArea()
{
}

}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    Ui::Plot plot;
    plot.show();
    return a.exec();
}
