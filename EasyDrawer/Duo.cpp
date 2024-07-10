#include "Duo.h"


void Duo::addPoint(POINT pt) {
    points.push_back(pt);
}

void Duo::updateLastPoint(POINT pt) {
    if (!points.empty()) {
        points.back() = pt;
    }
}

void Duo::draw() const {
    setlinecolor(color);
    setlinestyle(lineStyle, lineWidth);
    if (points.size() == 2) {
        line(points[0].x, points[0].y, points[1].x, points[1].y);
    }
    if (points.size() < 3) return;

    if (is_fill) {
        setfillcolor(fillcolor);
        solidpolygon(&points[0], points.size());
        polygon(&points[0], points.size());
    }
    else {
        polygon(&points[0], points.size());
    }
    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 1);
}

void Duo::parseInfoFromStream(std::stringstream& ss) {
    std::string token;
    ss >> token; // ����"Duo"

    ss >> token; // ����: 4
    int numPoints = std::stoi(token);

    ss >> ws >> token; // �㼯 {#(216,569)#(170,756)#(574,808)#(450,621)}
    token.pop_back(); // �Ƴ�'}'
    token.erase(0, wcslen(L"{#")); // �Ƴ�'{#'
    std::stringstream pointStream(token);
    std::string pointToken;
    while (std::getline(pointStream, pointToken, '#')) {
        if (!pointToken.empty()) {
            pointToken.erase(0, wcslen(L"("));
            pointToken.pop_back(); // �Ƴ�')'
            std::stringstream pointCoordStream(pointToken);
            POINT pt;
            pointCoordStream >> pt.x;
            pointCoordStream.ignore(1, L',');
            pointCoordStream >> pt.y;
            points.push_back(pt);
        }
    }

    ss >> ws >> token; // ������ɫ: 16733695
    color = std::stoi(token);

    ss >> ws >> token; // ���״̬: 1
    is_fill = (token == "1");

    ss >> ws >> token; // �����ɫ: 21930
    fillcolor = std::stoi(token);

    ss >> ws >> token; // �߿�: 7
    lineWidth = std::stoi(token);

    ss >> ws >> token; // ����: 0
    lineStyle = std::stoi(token);
}

std::string Duo::generateLabel() const {
    std::wstringstream ss;
    ss << L"Duo";
    ss << L" ����: " << points.size();
    ss << L" �㼯 {";
    for (const auto& pt : points) {
        ss << L"#(" << pt.x << L"," << pt.y << L")";
    }
    ss << L"}";
    ss << L" ������ɫ: " << color;
    ss << L" ���״̬: " << (int)is_fill;
    ss << L" �����ɫ: " << fillcolor;
    ss << L" �߿�: " << lineWidth << L" ����: " << lineStyle;
    return wstring2string(ss.str());
}

RECT Duo::getBoundingBox() const {
    if (points.empty()) return { 0, 0, 0, 0 };
    int minX = points[0].x, maxX = points[0].x, minY = points[0].y, maxY = points[0].y;
    for (const auto& pt : points) {
        if (pt.x < minX) minX = pt.x;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.y > maxY) maxY = pt.y;
    }
    return { minX, minY, maxX, maxY };
}

void Duo::move(int dx, int dy) {
    for (auto& pt : points) {
        pt.x += dx;
        pt.y += dy;
    }
}

void Duo::zoom(double factor, POINT zoomCenter) {
    for (auto& pt : points) {
        int dx = pt.x - zoomCenter.x;
        int dy = pt.y - zoomCenter.y;
        pt.x = static_cast<int>(zoomCenter.x + dx * factor);
        pt.y = static_cast<int>(zoomCenter.y + dy * factor);
    }
}

void Duo::changePoints(int x, int y) {
    int index = 0, dis = 1000000;
    for (int i = 0; i < points.size(); i++) {
        POINT& it = points[i];
        if ((x - it.x) * (x - it.x) + (y - it.y) * (y - it.y) < dis) {
            dis = (x - it.x) * (x - it.x) + (y - it.y) * (y - it.y);
            index = i;
        }
    }
    points[index].x = x;
    points[index].y = y;
}

std::shared_ptr<Shape> Duo::clone() const {
    return std::make_shared<Duo>(*this);
}

std::wstring Duo::getInfo() const {
    std::wstringstream ss;
    ss << L"�����: \nPoints=\n";
    for (const auto& pt : points) {
        ss << L"(" << pt.x << L"," << pt.y << L")";
    }
    ss << L"\n������ɫ=" << colorToString(color);
    if (is_fill) {
        ss << L"\n�����ɫ=" << colorToString(fillcolor);
    }
    return ss.str();
}