#include "stream_plot.h"
#include "color_graph.h"

namespace Ui {

StreamPlot::StreamPlot(QString title,
                       qint64 seconds,
                       QWidget* pp) :
    QCustomPlot(pp),
    mTitle(title),
    mSeconds(seconds)
{
    InitPlotArea();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]()
    {
        Refresh();
    });
    timer->start(100);
}

StreamPlot::~StreamPlot() =default;

void StreamPlot::RemoveOldPoints()
{
    QDateTime oldest = QDateTime::currentDateTime().addSecs(- mSeconds);

    std::size_t n = 0;
    for (n = 0; n + 1 < mTimestamps.size() && mTimestamps[n + 1] < oldest; ++n);

    mTimestamps.erase(mTimestamps.begin(), mTimestamps.begin() + n);
    mValues.erase(mValues.begin(), mValues.begin() + n);
    mColors.erase(mColors.begin(), mColors.begin() + n);
}

void StreamPlot::Refresh()
{
    RemoveOldPoints();

    qint64 now = QDateTime::currentDateTime().toMSecsSinceEpoch();

    mTimeAxis.clear();
    mTimeAxis.reserve(mValues.size());

    for (const QDateTime& time : mTimestamps)
    {
        qint64 ts = time.toMSecsSinceEpoch();
        const double relativeSeconds = - (now - ts) / 1000.0;

        mTimeAxis.push_back(relativeSeconds);
    }

    mTimeAxis.push_back(.0);
    mGraph->setData(mTimeAxis, mValues, &mColors);

    replot();
}

void StreamPlot::Push(QDateTime ts, double y, QColor color)
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

    Refresh();
}

void StreamPlot::InitPlotArea()
{
    mGraph = new QCPColorGraph(xAxis, yAxis);
    mGraph->setName(QLatin1String("MainGraph"));

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

    QSharedPointer<QCPAxisTickerFixed> tt(new QCPAxisTickerFixed);
    tt->setTickStep(mSeconds / 4.0);
    xAxis->setTicker(tt);

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

    xAxis->setRange(- mSeconds, 1.0);
    yAxis->setRange(0, 100);

    QCPItemText *textLabel = new QCPItemText(this);
    textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    textLabel->position->setCoords(0.90, 0); // top right
    textLabel->setText(mTitle);
    textLabel->setFont(QFont(font().family(), 15, QFont::Weight::Bold));
    textLabel->setColor(QColor(61, 230, 1, 165));
}

}

