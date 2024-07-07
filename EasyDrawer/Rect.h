#pragma once
#include"Shape.h"
class Rect : public Shape {
public:
    Rect(POINT topLeft = { 0,0 }, POINT bottomRight = { 0,0 }) : topLeft(topLeft), bottomRight(bottomRight) {}
    void draw() const override {
        setlinecolor(color);
        setlinestyle(lineStyle, lineWidth);
        if (is_fill) {
            setfillcolor(fillcolor);
            solidrectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
            rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
        else {
            rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
        setlinecolor(WHITE);
        setlinestyle(PS_SOLID, 1);
    }
    void parseInfoFromStream(std::stringstream& ss) {
        std::string token;
        ss >> token; // 忽略"Rect"

        ss >> token; // 左上点: (463,188)
        //token.erase(0, wcslen(L"左上点: ("));
        token.pop_back(); // 移除')'
        token.erase(0, wcslen(L"(")); // 移除'('
        std::stringstream coordStream(token);
        coordStream >> topLeft.x;
        coordStream.ignore(1, L',');
        coordStream >> topLeft.y;

        ss >> ws >> token; // 右下点: (684,474)
        //token.erase(0, wcslen(L"右下点: ("));
        token.pop_back(); // 移除')'
        token.erase(0, wcslen(L"(")); // 移除'('
        coordStream.str(token);
        coordStream.clear();
        coordStream >> bottomRight.x;
        coordStream.ignore(1, L',');
        coordStream >> bottomRight.y;

        ss >> ws >> token; // 线条颜色: 5636095
        //token.erase(0, wcslen(L"线条颜色: "));
        color = std::stoi(token);

        ss >> ws >> token; // 填充状态: 0
        //token.erase(0, wcslen(L"填充状态: "));
        is_fill = (token == "1");

        ss >> ws >> token; // 填充颜色: 5636095
        //token.erase(0, wcslen(L"填充颜色: "));
        fillcolor = std::stoi(token);

        ss >> ws >> token; // 线宽: 6
        //token.erase(0, wcslen(L"线宽: "));
        lineWidth = std::stoi(token);

        ss >> ws >> token; // 线型: 0
        //token.erase(0, wcslen(L"线型: "));
        lineStyle = std::stoi(token);
    }

    std::string generateLabel() const {
        std::wstringstream ss;
        ss << L"Rect";
        ss << L" 左上点: (" << topLeft.x << L"," << topLeft.y << L")";
        ss << L" 右下点: (" << bottomRight.x << L"," << bottomRight.y << L")";
        ss << L" 线条颜色: " << color;
        ss << L" 填充状态: " << (int)is_fill;
        ss << L" 填充颜色: " << fillcolor;
        ss << L" 线宽: " << lineWidth << L" 线型: " << lineStyle;
        return wstring2string(ss.str());
    }
    RECT getBoundingBox() const override {
        return { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
    }
    void move(int dx, int dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
        bottomRight.x += dx;
        bottomRight.y += dy;
    }
    void zoom(double factor, POINT zoomCenter) override {
        int dx1 = topLeft.x - zoomCenter.x;
        int dy1 = topLeft.y - zoomCenter.y;
        int dx2 = bottomRight.x - zoomCenter.x;
        int dy2 = bottomRight.y - zoomCenter.y;
        topLeft.x = static_cast<int>(zoomCenter.x + dx1 * factor);
        topLeft.y = static_cast<int>(zoomCenter.y + dy1 * factor);
        bottomRight.x = static_cast<int>(zoomCenter.x + dx2 * factor);
        bottomRight.y = static_cast<int>(zoomCenter.y + dy2 * factor);
    }
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Rect>(*this);
    }
    std::wstring getInfo() const override {
        std::wstringstream ss;
        ss << L"矩形: \n左上点=(" << topLeft.x << L"," << topLeft.y << L")\n右下点=(" << bottomRight.x << L"," << bottomRight.y;
        ss << L"\n线条颜色=" << colorToString(color);
        if (is_fill) {
            ss << L"\n填充颜色=" << colorToString(fillcolor);
        }
        return ss.str();
    }
    void changePoints(int x, int y) {
        {
            bottomRight.x = x;
            bottomRight.y = y;
        }
    }
private:
    POINT topLeft;
    POINT bottomRight;
};
