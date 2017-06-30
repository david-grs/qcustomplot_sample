#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>

namespace Ui {

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

    QCPGraph* mGraph = nullptr;

    QVector<double> mXAxis;
    QVector<double> mYAxis;
};

}
