#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>

namespace Ui {

class QCPColorGraph : public QCPGraph
{
public:
    QCPColorGraph(QCPAxis *keyAxis, QCPAxis *valueAxis) :
        QCPGraph(keyAxis, valueAxis)
    {
    }
    virtual void draw(QCPPainter* painter) override
    {
        QCPGraph::draw(painter);
    }
};

class Plot : public QCustomPlot
{
Q_OBJECT

public:
    Plot(QWidget* pp = nullptr);

public slots:
    void Push(double x, double y);

private slots:
    void OnMousePress(QMouseEvent*);
    void OnMouseWheel(QWheelEvent*);

private:
    void InitPlotArea();

    QCPColorGraph* mGraph = nullptr;

    QVector<double> mXAxis;
    QVector<double> mYAxis;
};

}
