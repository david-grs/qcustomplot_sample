#pragma once

#include "thirdparty/qcustomplot.h"

#include <QVector>
#include <QColor>
#include <QDateTime>

struct QCPColorGraph;

namespace Ui {

class StreamPlot : public QCustomPlot
{
Q_OBJECT

public:
    StreamPlot(QWidget* pp, qint64 seconds);
    ~StreamPlot();

public slots:
    void Push(QDateTime x, double y, QColor color);

private:
    void InitPlotArea();
    void Refresh();
    void RemoveOldPoints();

    qint64 mSeconds;

    QCPColorGraph* mGraph = nullptr;

    QVector<QDateTime> mTimestamps;
    QVector<double> mValues;
    QVector<QColor> mColors;

    // no state here, just to not allocate on every refresh
    QVector<double> mTimeAxis;
};

}
