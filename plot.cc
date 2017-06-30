#include "plot.h"

#include <iostream>

namespace Ui {

// TODO remove
QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand()) % 255; };
    auto alpha = []() -> int { return std::abs(std::rand()) % 64 + 180; };
    return QColor(color(), color(), color(), alpha());
}

Plot::Plot(QWidget* pp) :
    QCustomPlot(pp)
{
    InitPlotArea();

    // TODO remove

    QTimer *timer = new QTimer(this);
    //timer->setSingleShot(true);

    connect(timer, &QTimer::timeout, [this]() {
        // Push(QDateTime::currentDateTime(), std::rand() % 100, GenColor());
        // timer->deleteLater();
    });

    timer->start(1000);
}

void Plot::Refresh()
{
    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    QVector<double> timeAxis;
    timeAxis.reserve(mValues.size());

    for (const QDateTime& time : mTimestamps)
    {
        qint64 ts = time.toMSecsSinceEpoch();
        const double relativeMinutes = - (now - ts) / 60000.0;

        timeAxis.push_back(relativeMinutes);
    }

    mGraph->setData(timeAxis, mValues, mColors);

    rescaleAxes();
    replot();
}

void Plot::Push(QDateTime ts, double y, QColor color)
{
    mTimestamps.push_back(ts);
    mValues.push_back(y);
    mColors.push_back(color);
}

void Plot::InitPlotArea()
{
    setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    mGraph = new QCPColorGraph(xAxis, yAxis);
    mGraph->setName(QLatin1String("MainGraph "));

    mGraph->setPen(QPen(QColor(10, 140, 70, 160), 4));

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

#if 0
void Plot::OnMousePress(QMouseEvent* event)
{
    // Three actions possible here:
    // - right click = reset zoom
    // - left click with ctrl = drag
    // - left click (withtout ctrl) = zoom
    if (event->button() == Qt::RightButton)
    {
        rescaleAxes();
        replot();
    }
    else if (QApplication::keyboardModifiers() & Qt::ControlModifier)
    {
        setSelectionRectMode(QCP::SelectionRectMode::srmNone);
    }
    else
    {
        setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    }
}

void Plot::OnMouseWheel(QWheelEvent* event)
{
    const QCPRange xAxisRange = axisRect()->rangeZoomAxis(Qt::Horizontal)->range();
    const QCPRange yAxisRange = axisRect()->rangeZoomAxis(Qt::Vertical)->range();
    const bool zoomOut = event->angleDelta().y() < 0; // scroll down

    // it's already out of bounds, no need to go further
    if (zoomOut && ((xAxisRange.lower < .0 && xAxisRange.upper > 120.0) || (yAxisRange.lower < .0 && yAxisRange.upper > 100.0)))
        axisRect()->setRangeZoom(0);
    else
        axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}
#endif

void QCPColorGraph::setData(const QVector<double>& keys,
                            const QVector<double>& values,
                            const QVector<QColor>& colors)
{
    assert(keys.size() == values.size());
    assert(keys.size() == colors.size());

    QCPGraph::setData(keys, values);
    mColors = colors;
}

void QCPColorGraph::drawLinePlot(QCPPainter* painter, const QVector<QPointF>& points) const
{
    if (points.size() < 2 || painter->pen().style() == Qt::NoPen || painter->pen().color().alpha() == 0)
        return;

    applyDefaultAntialiasingHint(painter);

    QPointF lastPoint = points[0];
    for (int i = 1; i < points.size(); ++i)
    {
        painter->setPen(QPen(mColors[i], 4));

        drawPolyline(painter, {lastPoint, points[i]});
        lastPoint = points[i];
    }
}

}

