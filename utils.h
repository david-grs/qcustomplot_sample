#pragma once

#include "colors.h"

#include <cstdlib>
#include <array>
#include <vector>

struct Point
{
    double x;
    double y;
    QColor color;
};

static const std::vector<QColor> PreDefinedColors = {LightGreen, Blue, LightYellow, Cyan, Orange, Purple, Red};

inline QColor GenColorPre() { return PreDefinedColors.at(std::rand() % PreDefinedColors.size()); }

inline QColor GenColor()
{
    auto color = []() -> int { return std::abs(std::rand()) % 200 + 55; };
    auto alpha = []() -> int { return std::abs(std::rand()) % 64 + 180; };
    return QColor(color(), color(), color(), alpha());
}

inline Point GenPoint(double x) { return {x, double(std::rand() % 100), GenColorPre()}; }

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
