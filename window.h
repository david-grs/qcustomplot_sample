#pragma once

#include <QMainWindow>

namespace Ui {

struct StreamPlot;

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
    StreamPlot* mPlot;

    QPoint mPosition; // used in mouse events handler
};

}
