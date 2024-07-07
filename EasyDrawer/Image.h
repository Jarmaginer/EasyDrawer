#pragma once
#include"Shape.h"


class Image : public Shape {
public:
    Image() : Shape(), filename("") {}

    // ���ļ�����ͼƬ
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
    // ����ͼƬ
    void draw() const override {
        putimage(topLeft.x, topLeft.y, width, height, &m_image, 0, 0);
    }
    void parseInfoFromStream(std::stringstream& ss) {
        std::string token;
        ss >> token; // ����"���ϵ�: "

        ss >> token; // (151,358)
        // �Ƴ�')'
        token.pop_back();
        // �Ƴ�'('
        token.erase(0, wcslen(L"("));
        std::stringstream coordStream(token);
        coordStream >> topLeft.x;
        coordStream.ignore(1, L',');
        coordStream >> topLeft.y;

        ss >> ws >> token; // ���: 642

        width = std::stoi(token);

        ss >> ws >> token; // �߶�: 303
        height = std::stoi(token);

        ss >> ws >> token; // �ļ���: C:\Users\23258\Pictures\1.png
        filename = token;

        loadImageUsedInLoad(filename);
    }
    std::string generateLabel() const {
        std::wstringstream ss;
        ss << L"Image";
        ss << L" ���ϵ�: (" << topLeft.x << L"," << topLeft.y << L")";
        ss << L" ���: " << width;
        ss << L" �߶�: " << height;
        ss << L" �ļ���: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
        return wstring2string(ss.str());
    }

    // ��ȡ�߽��
    RECT getBoundingBox() const override {
        return { topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height };
    }

    // �ƶ�ͼƬ
    void move(int dx, int dy) override {
        topLeft.x += dx;
        topLeft.y += dy;
    }

    // ����ͼƬ
    void zoom(double factor, POINT zoomCenter) override {
        int dx = topLeft.x - zoomCenter.x;
        int dy = topLeft.y - zoomCenter.y;
        topLeft.x = static_cast<int>(zoomCenter.x + dx * factor);
        topLeft.y = static_cast<int>(zoomCenter.y + dy * factor);
        width = static_cast<int>(width * factor);
        height = static_cast<int>(height * factor);
        loadimage(&m_image, stringToLPCWSTR(filename), width, height);
    }

    // ��¡ͼƬ
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Image>(*this);
    }

    // ��ȡͼƬ��Ϣ
    std::wstring getInfo() const override {
        std::wstringstream ss;
        ss << L"ͼƬ: \n���ϵ�=(" << topLeft.x << L"," << topLeft.y << L")\n���=" << width << L"\n�߶�=" << height;
        ss << L"\n�ļ���=" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
        return ss.str();
    }

private:
    std::string filename;
    POINT topLeft = { 100,100 };
    int width, height;
    IMAGE m_image;
};
