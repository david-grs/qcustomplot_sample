#pragma once

#include "plot.h"

#include <QMainWindow>

namespace Ui {

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint mPosition; // used in mouse events handler

    Plot mPlot;

};

}
