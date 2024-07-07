#include "Shape.h"

void Shape::changeLineStyle() {
    if (lineStyle == 4) {
        lineStyle = 0;
    }
    else {
        lineStyle++;
    }
}

void Shape::addLineWidth() {
    lineWidth++;
}

void Shape::reduceLineWidth() {
    if (lineWidth > 1) {
        lineWidth--;
    }
}

void Shape::setColor(int co) {
    this->color = co;
}

void Shape::setFill(bool fill) {
    this->fillcolor = COLOR;
    this->is_fill = fill;
}

void Shape::setFillColour(int co) {
    this->fillcolor = co;
}

void Shape::changePoints(int x, int y) {
    // 默认实现为空
}
