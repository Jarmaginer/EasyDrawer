#include "Circle.h"

Circle::Circle(POINT center, int radius) : center(center), radius(radius) {}


void Circle::draw() const {
    setlinecolor(color);
    setlinestyle(lineStyle, lineWidth);
    if (is_fill) {
        setfillcolor(fillcolor);
        solidcircle(center.x, center.y, radius);
        circle(center.x, center.y, radius);
    }
    else {
        circle(center.x, center.y, radius);
    }
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 1);
}


void Circle::parseInfoFromStream(std::stringstream& ss) {
    std::string token;
    ss >> token;

    ss >> token;
    token.pop_back(); // �Ƴ�')'
    token.erase(0, wcslen(L"(")); // �Ƴ�'('
    std::stringstream coordStream(token);
    coordStream >> center.x;
    coordStream.ignore(1, L',');
    coordStream >> center.y;

    ss >> ws >> token; // �뾶: 118
    radius = std::stoi(token);

    ss >> ws >> token; // ������ɫ: 5636095
    color = std::stoi(token);

    ss >> ws >> token; // ���״̬: 1
    is_fill = (token == "1");

    ss >> ws >> token; // �����ɫ: 16733695
    fillcolor = std::stoi(token);

    ss >> ws >> token; // �߿�: 1
    lineWidth = std::stoi(token);

    ss >> ws >> token; // ����: 0
    lineStyle = std::stoi(token);
}

// generateLabel() ��Ա����ʵ��
std::string Circle::generateLabel() const {
    std::wstringstream ss;
    ss << L"Circle";
    ss << L" Բ��: (" << center.x << L"," << center.y << L")";
    ss << L" �뾶: " << radius;
    ss << L" ������ɫ: " << color;
    ss << L" ���״̬: " << (int)is_fill;
    ss << L" �����ɫ: " << fillcolor;
    ss << L" �߿�: " << lineWidth << L" ����: " << lineStyle;
    return wstring2string(ss.str());
}


RECT Circle::getBoundingBox() const {
    return { center.x - radius, center.y - radius, center.x + radius, center.y + radius };
}


void Circle::move(int dx, int dy) {
    center.x += dx;
    center.y += dy;
}


void Circle::zoom(double factor, POINT zoomCenter) {
    int dx = center.x - zoomCenter.x;
    int dy = center.y - zoomCenter.y;
    center.x = static_cast<int>(zoomCenter.x + dx * factor);
    center.y = static_cast<int>(zoomCenter.y + dy * factor);
    radius = static_cast<int>(radius * factor);
}


std::wstring Circle::getInfo() const {
    std::wstringstream ss;
    ss << L"Բ: \n�뾶=" << radius << L"\nԲ��=(" << center.x << L"," << center.y << L")";
    ss << L"\n������ɫ=" << colorToString(color);
    if (is_fill) {
        ss << L"\n�����ɫ=" << colorToString(fillcolor);
    }
    return ss.str();
}


std::shared_ptr<Shape> Circle::clone() const {
    return std::make_shared<Circle>(*this);
}