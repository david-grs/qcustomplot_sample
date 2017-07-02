#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>

class QCPColorGraph : public QCPGraph
{
public:
    QCPColorGraph(QCPAxis *keyAxis, QCPAxis *valueAxis);
    ~QCPColorGraph();

    void setData(const QVector<double>& keys,
                 const QVector<double>& values,
                 const QVector<QColor>* colors);

    virtual void drawLinePlot(QCPPainter* painter, const QVector<QPointF>& lines) const override;

private:
    const QVector<QColor>* mColors; // only valid during in setData (calling drawLinePlot() from QCPGraph)
};
