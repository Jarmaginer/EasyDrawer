#include "Image.h"
Image::Image() : Shape(), filename("") {}

bool Image::loadImage(const std::string& filename) {
    this->filename = filename;
    loadimage(&m_image, stringToLPCWSTR(filename));
    if (&m_image != NULL) {
        width = m_image.getwidth();
        height = m_image.getheight();
        return true;
    }
    return false;
}

bool Image::loadImageUsedInLoad(const std::string& filename) {
    this->filename = filename;
    loadimage(&m_image, stringToLPCWSTR(filename), width, height);
    if (&m_image != NULL) {
        return true;
    }
    return false;
}

void Image::draw() const {
    putimage(topLeft.x, topLeft.y, width, height, &m_image, 0, 0);
}

void Image::parseInfoFromStream(std::stringstream& ss) {
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

std::string Image::generateLabel() const {
    std::wstringstream ss;
    ss << L"Image";
    ss << L" 左上点: (" << topLeft.x << L"," << topLeft.y << L")";
    ss << L" 宽度: " << width;
    ss << L" 高度: " << height;
    ss << L" 文件名: " << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
    return wstring2string(ss.str());
}

RECT Image::getBoundingBox() const {
    return { topLeft.x, topLeft.y, topLeft.x + width, topLeft.y + height };
}

void Image::move(int dx, int dy) {
    topLeft.x += dx;
    topLeft.y += dy;
}

void Image::zoom(double factor, POINT zoomCenter) {
    int dx = topLeft.x - zoomCenter.x;
    int dy = topLeft.y - zoomCenter.y;
    topLeft.x = static_cast<int>(zoomCenter.x + dx * factor);
    topLeft.y = static_cast<int>(zoomCenter.y + dy * factor);
    width = static_cast<int>(width * factor);
    height = static_cast<int>(height * factor);
    loadimage(&m_image, stringToLPCWSTR(filename), width, height);
}

std::shared_ptr<Shape> Image::clone() const {
    return std::make_shared<Image>(*this);
}

std::wstring Image::getInfo() const {
    std::wstringstream ss;
    ss << L"图片: \n左上点=(" << topLeft.x << L"," << topLeft.y << L")\n宽度=" << width << L"\n高度=" << height;
    ss << L"\n文件名=" << std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(filename);
    return ss.str();
}
