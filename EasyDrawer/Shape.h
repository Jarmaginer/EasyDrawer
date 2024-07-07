

#pragma once
#include"tools.h"

class Shape {
public:
    virtual void draw() const = 0;
    virtual RECT getBoundingBox() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual ~Shape() {}
    virtual std::shared_ptr<Shape> clone() const = 0;
    virtual std::string generateLabel() const = 0;
    virtual void parseInfoFromStream(std::stringstream& ss) = 0;
    virtual void changeLineStyle();
    virtual void addLineWidth();
    virtual void reduceLineWidth();
    virtual void zoom(double factor, POINT center) = 0;
    virtual void setColor(int co);
    virtual std::wstring getInfo() const = 0;
    void setFill(bool fill);
    virtual void setFillColour(int co);
    virtual void changePoints(int x, int y);

    int color = COLOR;
    int fillcolor = COLOR;
    bool is_fill = false;
    int lineWidth = 1;
    int lineStyle = PS_SOLID;
};
