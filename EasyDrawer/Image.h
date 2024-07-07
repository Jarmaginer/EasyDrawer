#pragma once
#include"Shape.h"

class Image : public Shape {
public:
    Image();
    bool loadImage(const std::string& filename);
    bool loadImageUsedInLoad(const std::string& filename);
    void draw() const override;
    void parseInfoFromStream(std::stringstream& ss);
    std::string generateLabel() const;
    RECT getBoundingBox() const override;
    void move(int dx, int dy) override;
    void zoom(double factor, POINT zoomCenter) override;
    std::shared_ptr<Shape> clone() const override;
    std::wstring getInfo() const override;

private:
    std::string filename;
    POINT topLeft = { 100,100 };
    int width, height;
    IMAGE m_image;
};
