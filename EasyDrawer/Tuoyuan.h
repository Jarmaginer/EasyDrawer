#pragma once
#include"Shape.h"

class Tuoyuan : public Shape {
public:
    Tuoyuan(POINT topLeft = { 0,0 }, POINT bottomRight = { 0,0 });

    void draw() const override;
    void parseInfoFromStream(std::stringstream& ss);
    std::string generateLabel() const;
    RECT getBoundingBox() const override;
    void move(int dx, int dy) override;
    void zoom(double factor, POINT zoomCenter) override;
    std::shared_ptr<Shape> clone() const override;
    std::wstring getInfo() const override;
    void changePoints(int x, int y);

private:
    POINT topLeft;
    POINT bottomRight;
};
