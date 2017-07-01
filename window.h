#pragma once

#include <QMainWindow>

namespace Ui {

struct Plot;

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
    Plot* mPlot;

    QPoint mPosition; // used in mouse events handler
};

}
