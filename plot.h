#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>
#include <QColor>
#include <QDateTime>

#include <cassert>

namespace Ui {

class QCPColorGraph : public QCPGraph
{
public:
    QCPColorGraph(QCPAxis *keyAxis, QCPAxis *valueAxis) :
        QCPGraph(keyAxis, valueAxis)
    {
    }

    void setData(const QVector<double>& keys,
                 const QVector<double>& values,
                 const QVector<QColor>& colors);

    virtual void drawLinePlot(QCPPainter* painter, const QVector<QPointF>& lines) const override;

private:
    QVector<QColor> mColors;
};

class Plot : public QCustomPlot
{
Q_OBJECT

public:
    Plot(QWidget* pp = nullptr);

public slots:
    void Push(QDateTime x, double y, QColor color);

private:
    void InitPlotArea();
    void Refresh();
    void RemoveOldPoints();
    
    QCPColorGraph* mGraph = nullptr;

    QVector<QDateTime> mTimestamps;
    QVector<double> mValues;
    QVector<QColor> mColors;

    // no state here, just to not allocate on every refresh
    QVector<double> mTimeAxis;
};

}
