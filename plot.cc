#include "plot.h"


namespace Ui {

Plot::Plot(QWidget* pp) :
    QCustomPlot(pp)
{
    InitPlotArea();
}

void Plot::InitPlotArea()
{
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    mGraph = addGraph();
    mGraph->setPen(QPen(QColor(10, 140, 70, 160), 2));

    xAxis->setBasePen(QPen(Qt::white, 1));
    yAxis->setBasePen(QPen(Qt::white, 1));
    xAxis->setTickPen(QPen(Qt::white, 1));
    yAxis->setTickPen(QPen(Qt::white, 1));
    xAxis->setSubTickPen(QPen(Qt::white, 1));
    yAxis->setSubTickPen(QPen(Qt::white, 1));
    xAxis->setTickLabelColor(Qt::white);
    yAxis->setTickLabelColor(Qt::white);
    xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    xAxis->grid()->setSubGridVisible(true);
    yAxis->grid()->setSubGridVisible(true);
    xAxis->grid()->setZeroLinePen(Qt::NoPen);
    yAxis->grid()->setZeroLinePen(Qt::NoPen);
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    setBackground(plotGradient);

    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    axisRect()->setBackground(axisRectGradient);

    rescaleAxes();

    connect(this, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(OnMouseWheel(QWheelEvent*)));
    connect(this, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(OnMousePress(QMouseEvent*)));
}

void Plot::Push(double x, double y)
{
    mXAxis.push_back(x);
    mYAxis.push_back(y);

    mGraph->setData(mXAxis, mYAxis);

    rescaleAxes();
    replot();
}

void Plot::OnMousePress(QMouseEvent*)
{
}

void Plot::OnMouseWheel(QWheelEvent*)
{
}

}
