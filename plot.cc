#include "plot.h"


namespace Ui {

Plot::Plot(QWidget* pp) :
    QCustomPlot(pp)
{
    InitPlotArea();
}

void Plot::InitPlotArea()
{
}

void Plot::OnValue(double v)
{
}

void Plot::OnMousePress(QMouseEvent*)
{
}

void Plot::OnMouseWheel(QWheelEvent*)
{
}

}
