

#pragma once
#include"tools.h"


//std::string wstring2string(std::wstring wstr)
//{
//    std::string result;
//    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
//    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
//    char* buffer = new char[len + 1];
//    //宽字节编码转换成多字节编码  
//    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
//    buffer[len] = '\0';
//    //删除缓冲区并返回值  
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
//        return L"黑色";
//    case BLUE:
//        return L"蓝色";
//    case GREEN:
//        return L"绿色";
//    case CYAN:
//        return L"青色";
//    case RED:
//        return L"红色";
//    case MAGENTA:
//        return L"品红";
//    case BROWN:
//        return L"棕色";
//    case LIGHTGRAY:
//        return L"浅灰色";
//    case DARKGRAY:
//        return L"深灰色";
//    case LIGHTBLUE:
//        return L"浅蓝色";
//    case LIGHTGREEN:
//        return L"浅绿色";
//    case LIGHTCYAN:
//        return L"浅青色";
//    case LIGHTRED:
//        return L"浅红色";
//    case LIGHTMAGENTA:
//        return L"浅品红";
//    case YELLOW:
//        return L"黄色";
//    case WHITE:
//        return L"白色";
//    default:
//        return L"色值=" + std::to_wstring(color);
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
    int lineWidth = 1; // 默认线宽
    int lineStyle = PS_SOLID; // 默认线型，PS_SOLID表示实线
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
