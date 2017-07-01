#pragma once

#include "plot.h"

#include <QMainWindow>

#include <iostream>
#include <cstdlib>
#include <array>

struct Point
{
    double x;
    double y;
    QColor color;
};

inline QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand()) % 255; };
    auto alpha = []() -> int { return std::abs(std::rand()) % 64 + 180; };
    return QColor(color(), color(), color(), alpha());
}

inline Point GenPoint(double x) { return {x, double(std::rand() % 100), GenColor()}; }

template <std::size_t N>
struct GenPoints
{
    std::array<Point, N> operator()()
    {
        return impl(std::make_index_sequence<N>());
    }

private:
    template <std::size_t... Is>
    std::array<Point, N> impl(std::index_sequence<Is...>)
    {
        return {GenPoint(Is)...};
    }
};


namespace Ui {

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window() :
        mPlot(this)
    {
        int i = 0;
        for(auto x : GenPoints<10>()())
        {
            auto now = QDateTime::currentDateTime().addSecs(-60.0 * (9 - i++));
            mPlot.Push(now, x.y, x.color);
        }

        resize(800, 600);
        setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
        setCentralWidget(&mPlot);
    }
    
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint mPosition; // used in mouse events handler

    Plot mPlot;

};

}
