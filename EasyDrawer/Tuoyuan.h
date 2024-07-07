#pragma once
#include"Shape.h"


class Tuoyuan : public Shape {
public:
    Tuoyuan(POINT topLeft = { 0,0 }, POINT bottomRight = { 0,0 }) : topLeft(topLeft), bottomRight(bottomRight) {}
    void draw() const override {
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
    void parseInfoFromStream(std::stringstream& ss) {
        std::string token;
        ss >> token; // ����"Tuoyuan"

        ss >> token; // ���ϵ�: (862,555)
        //token.erase(0, wcslen(L"���ϵ�: ("));
        token.pop_back(); // �Ƴ�')'
        token.erase(0, wcslen(L"(")); // �Ƴ�'('
        std::stringstream coordStream(token);
        coordStream >> topLeft.x;
        coordStream.ignore(1, L',');
        coordStream >> topLeft.y;

        ss >> ws >> token; // ���µ�: (1340,818)
        token.erase(0, wcslen(L"("));
        token.pop_back(); // �Ƴ�')'
        coordStream.str(token);
        coordStream.clear();
        coordStream >> bottomRight.x;
        coordStream.ignore(1, L',');
        coordStream >> bottomRight.y;

        ss >> ws >> token; // ������ɫ: 21930
        //token.erase(0, wcslen(L"������ɫ: "));
        color = std::stoi(token);

        ss >> ws >> token; // ���״̬: 0
        //token.erase(0, wcslen(L"���״̬: "));
        is_fill = (token == "1");

        ss >> ws >> token; // �����ɫ: 21930
        //token.erase(0, wcslen(L"�����ɫ: "));
        fillcolor = std::stoi(token);

        ss >> ws >> token; // �߿�: 1
        //token.erase(0, wcslen(L"�߿�: "));
        lineWidth = std::stoi(token);

        ss >> ws >> token; // ����: 0
        //token.erase(0, wcslen(L"����: "));
        lineStyle = std::stoi(token);
    }
    std::string generateLabel() const {
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
        return std::make_shared<Tuoyuan>(*this);
    }
    std::wstring getInfo() const override {
        std::wstringstream ss;
        ss << L"��Բ: \n���ϵ�=(" << topLeft.x << L"," << topLeft.y << L")\n���µ�=(" << bottomRight.x << L"," << bottomRight.y;
        ss << L"\n������ɫ=" << colorToString(color);
        if (is_fill) {
            ss << L"\n�����ɫ=" << colorToString(fillcolor);
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
