#pragma once
#include"Shape.h"

class Zhexian : public Shape {
public:
    void addPoint(POINT pt);
    void updateLastPoint(POINT pt);
    void parseInfoFromStream(std::stringstream& ss);
    void draw() const override;
    std::string generateLabel() const;
    RECT getBoundingBox() const override;
    void move(int dx, int dy) override;
    void zoom(double factor, POINT zoomCenter) override;
    std::shared_ptr<Shape> clone() const override;
    std::wstring getInfo() const override;
    void changePoints(int x, int y);

private:
    std::vector<POINT> points;
};
