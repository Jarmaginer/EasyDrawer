

#pragma once
#include"tools.h"


//std::string wstring2string(std::wstring wstr)
//{
//    std::string result;
//    //��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
//    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//    char* buffer = new char[len + 1];
//    //���ֽڱ���ת���ɶ��ֽڱ���  
//    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//    buffer[len] = '\0';
//    //ɾ��������������ֵ  
//    result.append(buffer);
//    delete[] buffer;
//    return result;
//}
//std::string ws;
//static int COLOR = WHITE;
//
//std::wstring colorToString(int color) {
//    switch (color) {
//    case BLACK:
//        return L"��ɫ";
//    case BLUE:
//        return L"��ɫ";
//    case GREEN:
//        return L"��ɫ";
//    case CYAN:
//        return L"��ɫ";
//    case RED:
//        return L"��ɫ";
//    case MAGENTA:
//        return L"Ʒ��";
//    case BROWN:
//        return L"��ɫ";
//    case LIGHTGRAY:
//        return L"ǳ��ɫ";
//    case DARKGRAY:
//        return L"���ɫ";
//    case LIGHTBLUE:
//        return L"ǳ��ɫ";
//    case LIGHTGREEN:
//        return L"ǳ��ɫ";
//    case LIGHTCYAN:
//        return L"ǳ��ɫ";
//    case LIGHTRED:
//        return L"ǳ��ɫ";
//    case LIGHTMAGENTA:
//        return L"ǳƷ��";
//    case YELLOW:
//        return L"��ɫ";
//    case WHITE:
//        return L"��ɫ";
//    default:
//        return L"ɫֵ=" + std::to_wstring(color);
//    }
//
//}
//
//
//LPCWSTR stringToLPCWSTR(std::string str)
//{
//    size_t size = str.length();
//    int wLen = ::MultiByteToWideChar(CP_UTF8,
//        0,
//        str.c_str(),
//        -1,
//        NULL,
//        0);
//    wchar_t* buffer = new wchar_t[wLen + 1];
//    memset(buffer, 0, (wLen + 1) * sizeof(wchar_t));
//    MultiByteToWideChar(CP_ACP, 0, str.c_str(), size, (LPWSTR)buffer, wLen);
//    return buffer;
//}



class Shape {
public:
    virtual void draw() const = 0;
    virtual RECT getBoundingBox() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual ~Shape() {}
    virtual std::shared_ptr<Shape> clone() const = 0;
    virtual std::string generateLabel() const = 0;
    virtual void parseInfoFromStream(std::stringstream& ss) = 0;
    int color = COLOR;
    int fillcolor = COLOR;
    bool is_fill = false;
    int lineWidth = 1; // Ĭ���߿�
    int lineStyle = PS_SOLID; // Ĭ�����ͣ�PS_SOLID��ʾʵ��
    virtual void changeLineStyle() {
        if (lineStyle == 4)
        {
            lineStyle = 0;
        }
        else
        {
            lineStyle++;
        }
    }
    virtual void addLineWidth() {
        lineWidth++;
    }
    virtual void reduceLineWidth() {
        if (lineWidth > 1) {
            lineWidth--;
        }
    }
    virtual void zoom(double factor, POINT center) = 0;
    virtual void setColor(int co) {
        this->color = co;
    }
    virtual std::wstring getInfo() const = 0;

    void setFill(bool fill) {
        this->fillcolor = COLOR;
        this->is_fill = fill;
    }
    virtual void setFillColour(int co) {
        this->fillcolor = co;
    }
    virtual void changePoints(int x, int y) {

    }
};
