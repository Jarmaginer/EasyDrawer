#pragma once
#include"Shape.h"


class Circle : public Shape {
public:
    Circle(POINT center = { 0, 0 }, int radius = 0);
    void draw() const override;
    void parseInfoFromStream(std::stringstream& ss) override;
    std::string generateLabel() const override;
    RECT getBoundingBox() const override;
    void move(int dx, int dy) override;
    void zoom(double factor, POINT zoomCenter) override;
    std::wstring getInfo() const override;
    std::shared_ptr<Shape> clone() const override;

private:
    POINT center;
    int radius;
};

