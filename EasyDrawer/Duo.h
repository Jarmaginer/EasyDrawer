#pragma once
#include"Shape.h"

class Duo : public Shape {
public:
    void addPoint(POINT pt);
    void updateLastPoint(POINT pt);
    void draw() const override;
    void parseInfoFromStream(std::stringstream& ss);
    std::string generateLabel() const;
    RECT getBoundingBox() const override;
    void move(int dx, int dy) override;
    void zoom(double factor, POINT zoomCenter) override;
    void changePoints(int x, int y);
    std::shared_ptr<Shape> clone() const override;
    std::wstring getInfo() const override;

private:
    std::vector<POINT> points;
};