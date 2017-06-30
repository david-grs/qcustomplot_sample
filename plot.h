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

public:
    void InitPlotArea();
    void Refresh();

    QCPColorGraph* mGraph = nullptr;

    QVector<QDateTime> mTimestamps;
    QVector<double> mValues;
    QVector<QColor> mColors;
};

}
