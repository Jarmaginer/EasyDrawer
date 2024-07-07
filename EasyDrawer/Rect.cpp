#include "Rect.h"

Rect::Rect(POINT topLeft, POINT bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}

void Rect::draw() const {
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

void Rect::parseInfoFromStream(std::stringstream& ss) {
    std::string token;
    ss >> token;

    ss >> token;
    token.pop_back();
    token.erase(0, wcslen(L"("));
    std::stringstream coordStream(token);
    coordStream >> topLeft.x;
    coordStream.ignore(1, L',');
    coordStream >> topLeft.y;

    ss >> ws >> token;
    token.pop_back();
    token.erase(0, wcslen(L"("));
    coordStream.str(token);
    coordStream.clear();
    coordStream >> bottomRight.x;
    coordStream.ignore(1, L',');
    coordStream >> bottomRight.y;

    ss >> ws >> token;
    color = std::stoi(token);

    ss >> ws >> token;
    is_fill = (token == "1");

    ss >> ws >> token;
    fillcolor = std::stoi(token);

    ss >> ws >> token;
    lineWidth = std::stoi(token);

    ss >> ws >> token;
    lineStyle = std::stoi(token);
}

std::string Rect::generateLabel() const {
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

RECT Rect::getBoundingBox() const {
    return { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
}

void Rect::move(int dx, int dy) {
    topLeft.x += dx;
    topLeft.y += dy;
    bottomRight.x += dx;
    bottomRight.y += dy;
}

void Rect::zoom(double factor, POINT zoomCenter) {
    int dx1 = topLeft.x - zoomCenter.x;
    int dy1 = topLeft.y - zoomCenter.y;
    int dx2 = bottomRight.x - zoomCenter.x;
    int dy2 = bottomRight.y - zoomCenter.y;
    topLeft.x = static_cast<int>(zoomCenter.x + dx1 * factor);
    topLeft.y = static_cast<int>(zoomCenter.y + dy1 * factor);
    bottomRight.x = static_cast<int>(zoomCenter.x + dx2 * factor);
    bottomRight.y = static_cast<int>(zoomCenter.y + dy2 * factor);
}

std::shared_ptr<Shape> Rect::clone() const {
    return std::make_shared<Rect>(*this);
}

std::wstring Rect::getInfo() const {
    std::wstringstream ss;
    ss << L"矩形: \n左上点=(" << topLeft.x << L"," << topLeft.y << L")\n右下点=(" << bottomRight.x << L"," << bottomRight.y;
    ss << L"\n线条颜色=" << colorToString(color);
    if (is_fill) {
        ss << L"\n填充颜色=" << colorToString(fillcolor);
    }
    return ss.str();
}

void Rect::changePoints(int x, int y) {
    bottomRight.x = x;
    bottomRight.y = y;
}
