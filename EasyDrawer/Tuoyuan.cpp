#include "Tuoyuan.h"

Tuoyuan::Tuoyuan(POINT topLeft, POINT bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}

void Tuoyuan::draw() const {
    setlinecolor(color);
    setlinestyle(lineStyle, lineWidth);
    if (is_fill) {
        setfillcolor(fillcolor);
        solidellipse(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        ellipse(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }
    else {
        ellipse(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
    }
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 1);
}

void Tuoyuan::parseInfoFromStream(std::stringstream& ss) {
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
    token.erase(0, wcslen(L"("));
    token.pop_back();
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

std::string Tuoyuan::generateLabel() const {
    std::wstringstream ss;
    ss << L"Tuoyuan";
    ss << L" ���ϵ�: (" << topLeft.x << L"," << topLeft.y << L")";
    ss << L" ���µ�: (" << bottomRight.x << L"," << bottomRight.y << L")";
    ss << L" ������ɫ: " << color;
    ss << L" ���״̬: " << (int)is_fill;
    ss << L" �����ɫ: " << fillcolor;
    ss << L" �߿�: " << lineWidth << L" ����: " << lineStyle;
    return wstring2string(ss.str());
}

RECT Tuoyuan::getBoundingBox() const {
    return { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
}

void Tuoyuan::move(int dx, int dy) {
    topLeft.x += dx;
    topLeft.y += dy;
    bottomRight.x += dx;
    bottomRight.y += dy;
}

void Tuoyuan::zoom(double factor, POINT zoomCenter) {
    int dx1 = topLeft.x - zoomCenter.x;
    int dy1 = topLeft.y - zoomCenter.y;
    int dx2 = bottomRight.x - zoomCenter.x;
    int dy2 = bottomRight.y - zoomCenter.y;
    topLeft.x = static_cast<int>(zoomCenter.x + dx1 * factor);
    topLeft.y = static_cast<int>(zoomCenter.y + dy1 * factor);
    bottomRight.x = static_cast<int>(zoomCenter.x + dx2 * factor);
    bottomRight.y = static_cast<int>(zoomCenter.y + dy2 * factor);
}

std::shared_ptr<Shape> Tuoyuan::clone() const {
    return std::make_shared<Tuoyuan>(*this);
}

std::wstring Tuoyuan::getInfo() const {
    std::wstringstream ss;
    ss << L"��Բ: \n���ϵ�=(" << topLeft.x << L"," << topLeft.y << L")\n���µ�=(" << bottomRight.x << L"," << bottomRight.y;
    ss << L"\n������ɫ=" << colorToString(color);
    if (is_fill) {
        ss << L"\n�����ɫ=" << colorToString(fillcolor);
    }
    return ss.str();
}

void Tuoyuan::changePoints(int x, int y) {
    bottomRight.x = x;
    bottomRight.y = y;
}
