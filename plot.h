#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>
#include <QColor>

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
                 const QVector<QColor>& colors)
    {
        assert(keys.size() == values.size());
        assert(keys.size() == colors.size());

        QCPGraph::setData(keys, values);
        mColors = colors;
    }

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
    void Push(double x, double y, QColor color);

private slots:
    void OnMousePress(QMouseEvent*);
    void OnMouseWheel(QWheelEvent*);

private:
    void InitPlotArea();

    QCPColorGraph* mGraph = nullptr;

    QVector<double> mKeys;
    QVector<double> mValues;
    QVector<QColor> mColors;
};

}
