#pragma once

#include "thirdparty/qcustomplot.h"

namespace Ui {

class Plot : public QCustomPlot
{
Q_OBJECT

public:
    Plot(QWidget* pp = nullptr);

public slots:
    void OnValue(double v);

private slots:
    void OnMousePress(QMouseEvent*);
    void OnMouseWheel(QWheelEvent*);

private:
    void InitPlotArea();

    QVector<double> mTimeAxis;
    QCPGraph* mGraph = nullptr;
};

}
