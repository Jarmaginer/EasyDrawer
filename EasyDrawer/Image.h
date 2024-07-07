#pragma once
#include"Shape.h"


class Image : public Shape {
public:
    Image() : Shape(), filename("") {}

    // 从文件加载图片
    bool loadImage(const std::string& filename) {
        this->filename = filename;
        loadimage(&m_image, stringToLPCWSTR(filename));
        if (&m_image != NULL) {
            width = m_image.getwidth();
            height = m_image.getheight();
            return true;
        }
        return false;
    }
    bool loadImageUsedInLoad(const std::string& filename) {
        this->filename = filename;
        loadimage(&m_image, stringToLPCWSTR(filename), width, height);
        if (&m_image != NULL) {
            return true;
        }
        return false;
    }
    // 绘制图片
    void draw() const override {
        putimage(topLeft.x, topLeft.y, width, height, &m_image, 0, 0);
    }
    void parseInfoFromStream(std::stringstream& ss) {
        std::string token;
        ss >> token; // 忽略"左上点: "

        ss >> token; // (151,358)
        // 移除')'
        token.pop_back();
        // 移除'('
        token.erase(0, wcslen(L"("));
        std::stringstream coordStream(token);
        coordStream >> topLeft.x;
        coordStream.ignore(1, L',');
        coordStream >> topLeft.y;

        ss >> ws >> token; // 宽度: 642

        width = std::stoi(token);

        ss >> ws >> token; // 高度: 303
        height = std::stoi(token);

        ss >> ws >> token; // 文件名: C:\Users\23258\Pictures\1.png
        filename = token;

        loadImageUsedInLoad(filename);
    }
    std::string generateLabel() const {
        std::wstringstream ss;
        ss << L"Image";
        ss << L" 左上点: (" << topLeft.x << L"," << topLeft.y << L")";
        ss << L" 宽度: " << width;
        ss << L" 高度: " << height;
        ss << L" 文件名: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
        return wstring2string(ss.str());
    }

    // 获取边界框
    RECT getBoundingBox() const override {
        return { topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height };
    }

    // 移动图片
    void move(int dx, int dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
    }

    // 缩放图片
    void zoom(double factor, POINT zoomCenter) override {
        int dx = topLeft.x - zoomCenter.x;
        int dy = topLeft.y - zoomCenter.y;
        topLeft.x = static_cast<int>(zoomCenter.x + dx * factor);
        topLeft.y = static_cast<int>(zoomCenter.y + dy * factor);
        width = static_cast<int>(width * factor);
        height = static_cast<int>(height * factor);
        loadimage(&m_image, stringToLPCWSTR(filename), width, height);
    }

    // 克隆图片
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Image>(*this);
    }

    // 获取图片信息
    std::wstring getInfo() const override {
        std::wstringstream ss;
        ss << L"图片: \n左上点=(" << topLeft.x << L"," << topLeft.y << L")\n宽度=" << width << L"\n高度=" << height;
        ss << L"\n文件名=" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
        return ss.str();
    }

private:
    std::string filename;
    POINT topLeft = { 100,100 };
    int width, height;
    IMAGE m_image;
};
