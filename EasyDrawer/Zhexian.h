#pragma once
#include"Shape.h"

class Zhexian : public Shape {
public:
    void addPoint(POINT pt) {
        points.push_back(pt);
    }
    void updateLastPoint(POINT pt) {
        if (!points.empty()) {
            points.back() = pt;
        }
    }
    void parseInfoFromStream(std::stringstream& ss) {
        std::string token;
        ss >> token; // ����"Zhexian"

        ss >> token; // ����: 6
        //token.erase(0, wcslen(L"����: "));
        int numPoints = std::stoi(token);

        ss >> ws >> token; // �㼯 {#(974,178)#(791,438)#(1084,446)#(1050,313)#(1237,319)#(1261,154)}
        //token.erase(0, wcslen(L"�㼯 {#"));
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
        //token.erase(0, wcslen(L"������ɫ: "));
        color = std::stoi(token);

        ss >> ws >> token; // ���״̬: 0
        //token.erase(0, wcslen(L"���״̬: "));
        is_fill = (token == "1");

        ss >> ws >> token; // �����ɫ: 16733695
        //token.erase(0, wcslen(L"�����ɫ: "));
        fillcolor = std::stoi(token);

        ss >> ws >> token; // �߿�: 1
        //token.erase(0, wcslen(L"�߿�: "));
        lineWidth = std::stoi(token);

        ss >> ws >> token; // ����: 0
        //token.erase(0, wcslen(L"����: "));
        lineStyle = std::stoi(token);
    }
    void draw() const override {
        if (points.size() < 2) return;
        if (is_fill && points.size() > 2) {
            setfillcolor(fillcolor);

            solidpolygon(&points[0], points.size());
            for (size_t i = 0; i < points.size() - 1; ++i) {
                setlinecolor(color);
                setlinestyle(lineStyle, lineWidth);
                line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            }
        }
        else {
            for (size_t i = 0; i < points.size() - 1; ++i) {
                setlinecolor(color);
                setlinestyle(lineStyle, lineWidth);
                line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            }
        }
        setlinecolor(WHITE);
        setlinestyle(PS_SOLID, 1);
    }
    std::string generateLabel() const {
        std::wstringstream ss;
        ss << L"Zhexian";
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
    RECT getBoundingBox() const override {
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
    void move(int dx, int dy) override {
        for (auto& pt : points) {
            pt.x += dx;
            pt.y += dy;
        }
    }
    void zoom(double factor, POINT zoomCenter) override {
        for (auto& pt : points) {
            int dx = pt.x - zoomCenter.x;
            int dy = pt.y - zoomCenter.y;
            pt.x = static_cast<int>(zoomCenter.x + dx * factor);
            pt.y = static_cast<int>(zoomCenter.y + dy * factor);
        }
    }
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Zhexian>(*this);
    }
    std::wstring getInfo() const override {
        std::wstringstream ss;
        ss << L"����:\n Points=\n";
        //for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
  //      {
  //          if (i > 0 && (points[i].x == points[i - 1].x) && (points[i].y == points[i - 1].y)) continue;//�����ظ�
        //	ss << L"(" << points[i].x << L"," << points[i].y << L")\n";
        //}
        for (const auto& pt : points) {
            ss << L"(" << pt.x << L"," << pt.y << L")";
        }
        ss << L"\n������ɫ=" << colorToString(color);
        if (is_fill) {
            ss << L"\n�����ɫ=" << colorToString(fillcolor);
        }
        return ss.str();
    }
    void changePoints(int x, int y) {
        int index = 0, dis = 1000000;
        for (int i = 0; i < points.size(); i++) {
            POINT& it = points[i];
            if ((x - it.x) * (x - it.x) + (y - it.y) * (y - it.y) < dis) {

                dis = (x - it.x) * (x - it.x) + (y - it.y) * (y - it.y);
                index = i;

            }

            /*if ((x - it.x) * (x - it.x) + (y - it.y) * (y - it.y) <= 1000) {

                it.x = x;
                it.y = y;
                break;
            }*/
        }
        points[index].x = x;
        points[index].y = y;
    }
private:
    std::vector<POINT> points;
};