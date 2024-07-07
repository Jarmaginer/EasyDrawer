#include "Zhexian.h"

void Zhexian::addPoint(POINT pt) {
    points.push_back(pt);
}

void Zhexian::updateLastPoint(POINT pt) {
    if (!points.empty()) {
        points.back() = pt;
    }
}

void Zhexian::parseInfoFromStream(std::stringstream& ss) {
    std::string token;
    ss >> token;

    ss >> token;
    int numPoints = std::stoi(token);

    ss >> ws >> token;
    token.pop_back();
    token.erase(0, wcslen(L"{#"));
    std::stringstream pointStream(token);
    std::string pointToken;
    while (std::getline(pointStream, pointToken, '#')) {
        if (!pointToken.empty()) {
            pointToken.erase(0, wcslen(L"("));
            pointToken.pop_back();
            std::stringstream pointCoordStream(pointToken);
            POINT pt;
            pointCoordStream >> pt.x;
            pointCoordStream.ignore(1, L',');
            pointCoordStream >> pt.y;
            points.push_back(pt);
        }
    }

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

void Zhexian::draw() const {
    if (points.size() < 2) return;

    setlinecolor(color);
    setlinestyle(lineStyle, lineWidth);

    if (is_fill && points.size() > 2) {
        setfillcolor(fillcolor);
        solidpolygon(&points[0], points.size());
    }

    for (size_t i = 0; i < points.size() - 1; ++i) {
        line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }

    setlinecolor(WHITE);
    setlinestyle(PS_SOLID, 1);
}

std::string Zhexian::generateLabel() const {
    std::wstringstream ss;
    ss << L"Zhexian";
    ss << L" 点数: " << points.size();
    ss << L" 点集 {";
    for (const auto& pt : points) {
        ss << L"#(" << pt.x << L"," << pt.y << L")";
    }
    ss << L"}";
    ss << L" 线条颜色: " << color;
    ss << L" 填充状态: " << (int)is_fill;
    ss << L" 填充颜色: " << fillcolor;
    ss << L" 线宽: " << lineWidth << L" 线型: " << lineStyle;
    return wstring2string(ss.str());
}

RECT Zhexian::getBoundingBox() const {
    if (points.empty()) return { 0, 0, 0, 0 };

    int minX = points[0].x, maxX = points[0].x;
    int minY = points[0].y, maxY = points[0].y;

    for (const auto& pt : points) {
        if (pt.x < minX) minX = pt.x;
        if (pt.x > maxX) maxX = pt.x;
        if (pt.y < minY) minY = pt.y;
        if (pt.y > maxY) maxY = pt.y;
    }

    return { minX, minY, maxX, maxY };
}

void Zhexian::move(int dx, int dy) {
    for (auto& pt : points) {
        pt.x += dx;
        pt.y += dy;
    }
}

void Zhexian::zoom(double factor, POINT zoomCenter) {
    for (auto& pt : points) {
        int dx = pt.x - zoomCenter.x;
        int dy = pt.y - zoomCenter.y;
        pt.x = static_cast<int>(zoomCenter.x + dx * factor);
        pt.y = static_cast<int>(zoomCenter.y + dy * factor);
    }
}

std::shared_ptr<Shape> Zhexian::clone() const {
    return std::make_shared<Zhexian>(*this);
}

std::wstring Zhexian::getInfo() const {
    std::wstringstream ss;
    ss << L"折线:\n Points=\n";
    for (const auto& pt : points) {
        ss << L"(" << pt.x << L"," << pt.y << L")";
    }
    ss << L"\n线条颜色=" << colorToString(color);
    if (is_fill) {
        ss << L"\n填充颜色=" << colorToString(fillcolor);
    }
    return ss.str();
}

void Zhexian::changePoints(int x, int y) {
    int index = 0, dis = 1000000;

    for (int i = 0; i < points.size(); ++i) {
        POINT& pt = points[i];
        int distance = (x - pt.x) * (x - pt.x) + (y - pt.y) * (y - pt.y);

        if (distance < dis) {
            dis = distance;
            index = i;
        }
    }

    points[index].x = x;
    points[index].y = y;
}
