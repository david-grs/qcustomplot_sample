#include "color_graph.h"

#include <cassert>

QCPColorGraph::QCPColorGraph(QCPAxis *keyAxis, QCPAxis *valueAxis) :
    QCPGraph(keyAxis, valueAxis)
{
}

QCPColorGraph::~QCPColorGraph()
{
    mColors = nullptr;
}

void QCPColorGraph::setData(const QVector<double>& keys,
                            const QVector<double>& values,
                            const QVector<QColor>* colors)
{
    assert(keys.size() == values.size());
    assert(keys.size() == colors->size());

    mColors = colors;
    QCPGraph::setData(keys, values);
}

void QCPColorGraph::drawLinePlot(QCPPainter* painter, const QVector<QPointF>& points) const
{
    if (points.size() < 2 || painter->pen().style() == Qt::NoPen || painter->pen().color().alpha() == 0)
        return;

    applyDefaultAntialiasingHint(painter);

    QPointF lastPoint = points[0];
    for (int i = 1; i < points.size(); ++i)
    {
        painter->setPen(QPen((*mColors)[i], 4));

        drawPolyline(painter, {lastPoint, points[i]});
        lastPoint = points[i];
    }
}
