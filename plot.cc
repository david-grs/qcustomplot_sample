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
        Refresh();
        static int i = 0;
        if ((++i) % 5 == 0)
            Push(QDateTime::currentDateTime(), std::rand() % 100, GenColor());
    });

    timer->start(1000);
}

void Plot::Refresh()
{
    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    mTimeAxis.clear();
    mTimeAxis.reserve(mValues.size());

    for (const QDateTime& time : mTimestamps)
    {
        qint64 ts = time.toMSecsSinceEpoch();
        const double relativeMinutes = - (now - ts) / 60000.0;

        mTimeAxis.push_back(relativeMinutes);
    }

    mTimeAxis.push_back(.0);
    mGraph->setData(mTimeAxis, mValues, mColors);

    replot();
}

void Plot::Push(QDateTime ts, double y, QColor color)
{
    // values are pushed in that way:
    // 1. values =     [ 1  1 ]
    //    timestamps = [ X ]
    //
    // 2. values =     [ 1 1 2 2 ]
    //    timestamps = [ X Y Y ]
    //
    // 3.etc

    const bool firstPoint = mTimestamps.empty();

    mTimestamps.push_back(ts);
    mValues.push_back(y);
    mColors.push_back(color);

    if (!firstPoint)
        mTimestamps.push_back(ts.addMSecs(1));
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

    xAxis->setRange(-10, 0);
    yAxis->setRange(0, 100);
}

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

