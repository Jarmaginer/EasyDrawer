#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <vector>
#include <memory>

#include <conio.h> // 使用_getch()

// 按钮类
class Button {
public:
    Button(int left, int top, int right, int bottom, const TCHAR* text)
        : left(left), top(top), right(right), bottom(bottom), text(text), isPressed(false) {}

    void draw() const {
        if (isPressed) {
            setfillcolor(LIGHTGRAY);
        }
        else {
            setfillcolor(WHITE);
        }
        solidrectangle(left, top, right, bottom);

        settextstyle(30, 0, _T("Consolas"));
        settextcolor(WHITE);
        outtextxy(left + 5, top + 10, text);
    }

    bool isInside(int x, int y) const {
        return x >= left && x <= right && y >= top && y <= bottom;
    }

    void press() {
        isPressed = true;
    }

    void release() {
        isPressed = false;
    }

private:
    int left, top, right, bottom;
    const TCHAR* text;
    bool isPressed;
};

// 基类 Shape，所有图形的抽象基类
class Shape {
public:
    virtual void draw() const = 0;
    virtual RECT getBoundingBox() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual ~Shape() {}
    int color = WHITE;
    virtual void setColor(int co) {
        this->color = co;
    }
};

// 派生类 Circle，表示圆形
class Circle : public Shape {
public:
    Circle(POINT center, int radius) : center(center), radius(radius) {}
    void draw() const override {
        setlinecolor(color);
        circle(center.x, center.y, radius);
        setlinecolor(WHITE);
    }
    RECT getBoundingBox() const override {
        return { center.x - radius, center.y - radius, center.x + radius, center.y + radius };
    }
    void move(int dx, int dy) override {
        center.x += dx;
        center.y += dy;
    }
private:
    POINT center;
    int radius;
};

// 派生类 Rect，表示矩形
class Rect : public Shape {
public:
    Rect(POINT topLeft, POINT bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}
    void draw() const override {
        setlinecolor(color);
        rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        setlinecolor(WHITE);
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
private:
    POINT topLeft;
    POINT bottomRight;
};

// 派生类 Zhexian，表示折线
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
    void draw() const override {
        if (points.size() < 2) return;
        for (size_t i = 0; i < points.size() - 1; ++i) {
            setlinecolor(color);
            line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            setlinecolor(WHITE);
        }
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
private:
    std::vector<POINT> points;
};

// 全局变量
std::vector<std::shared_ptr<Shape>> shapes;
std::shared_ptr<Zhexian> currentZhexian;
bool isDrawingCircle = false;
bool isDrawingRect = false;
bool isDrawingZhexian = false;
bool drawCircleMode = false;
bool drawRectMode = false;
bool drawZhexianMode = false;
bool selectMode = false;
POINT startPoint;
POINT endPoint;
int selectedIndex = -1;
bool isDragging = false;
POINT lastMousePos;

// 按钮
Button drawCircleButton(50, 50, 150, 100, _T("Draw Circle"));
Button drawRectButton(50, 150, 150, 200, _T("Draw Rect"));
Button drawZhexianButton(50, 250, 150, 300, _T("Draw Zhexian"));
Button selectShapeButton(50, 350, 150, 400, _T("Select Shape"));

// 绘制所有的图形和按钮
void DrawAllShapes() {
    cleardevice();

    drawCircleButton.draw();
    drawRectButton.draw();
    drawZhexianButton.draw();
    selectShapeButton.draw();

    // 绘制所有形状
    for (const auto& shape : shapes) {
        shape->draw();
    }

    // 绘制当前绘制中的形状
    if (isDrawingCircle) {
        int radius = static_cast<int>(std::sqrt(std::pow(endPoint.x - startPoint.x, 2) + std::pow(endPoint.y - startPoint.y, 2)));
        Circle tempCircle(startPoint, radius);
        tempCircle.draw();
    }
    else if (isDrawingRect) {
        Rect tempRect(startPoint, endPoint);
        tempRect.draw();
    }
    else if (isDrawingZhexian && currentZhexian) {
        currentZhexian->draw();
    }

    // 绘制选中的形状的外框
    if (selectedIndex != -1) {
        RECT bbox = shapes[selectedIndex]->getBoundingBox();
        setlinecolor(YELLOW);
        rectangle(bbox.left - 5, bbox.top - 5, bbox.right + 5, bbox.bottom + 5);
        setlinecolor(WHITE);
    }
}

int main() {
    // 初始化图形窗口
    initgraph(1200, 800);
    setbkcolor(BLACK);
    cleardevice();

    while (true) {
        // 获取鼠标消息
        MOUSEMSG msg = GetMouseMsg();

        POINT pt = { msg.x, msg.y };

        DrawAllShapes();
        switch (msg.uMsg) {
        case WM_LBUTTONDOWN:
            // 检查是否点击了按钮
            if (drawCircleButton.isInside(pt.x, pt.y)) {
                drawCircleMode = true;
                drawRectMode = false;
                drawZhexianMode = false;
                selectMode = false;
                drawCircleButton.press();
                drawRectButton.release();
                drawZhexianButton.release();
                selectShapeButton.release();
                if (isDrawingZhexian && currentZhexian) {
                    shapes.push_back(currentZhexian);
                }
                currentZhexian.reset();
            }
            else if (drawRectButton.isInside(pt.x, pt.y)) {
                drawCircleMode = false;
                drawRectMode = true;
                drawZhexianMode = false;
                selectMode = false;
                drawRectButton.press();
                drawCircleButton.release();
                drawZhexianButton.release();
                selectShapeButton.release();
                if (isDrawingZhexian && currentZhexian) {
                    shapes.push_back(currentZhexian);
                }
                currentZhexian.reset();
            }
            else if (drawZhexianButton.isInside(pt.x, pt.y)) {
                drawCircleMode = false;
                drawRectMode = false;
                drawZhexianMode = true;
                selectMode = false;
                drawZhexianButton.press();
                drawCircleButton.release();
                drawRectButton.release();
                selectShapeButton.release();
                if (!isDrawingZhexian) {
                    currentZhexian = std::make_shared<Zhexian>();
                    isDrawingZhexian = true;
                }
            }
            else if (selectShapeButton.isInside(pt.x, pt.y)) {
                drawCircleMode = false;
                drawRectMode = false;
                drawZhexianMode = false;
                selectMode = true;
                selectShapeButton.press();
                drawCircleButton.release();
                drawRectButton.release();
                drawZhexianButton.release();
                if (isDrawingZhexian && currentZhexian) {
                    shapes.push_back(currentZhexian);
                }
                currentZhexian.reset();
            }
            else if (drawCircleMode) {
                // 左键按下，开始绘制圆
                isDrawingCircle = true;
                isDrawingRect = false;
                isDrawingZhexian = false;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawRectMode) {
                // 左键按下，开始绘制矩形
                isDrawingRect = true;
                isDrawingCircle = false;
                isDrawingZhexian = false;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawZhexianMode) {
                // 左键按下，绘制折线
                if (isDrawingZhexian && currentZhexian) {
                    currentZhexian->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if (selectMode && selectedIndex != -1) {
                // 左键按下，开始拖动选中的图形
                isDragging = true;
                lastMousePos = pt;
            }
            break;

        case WM_RBUTTONDOWN:
            // 右键按下，结束折线绘制
            if (isDrawingZhexian && currentZhexian) {
                shapes.push_back(currentZhexian);
                currentZhexian.reset();
                isDrawingZhexian = false;
                DrawAllShapes();
            }
            break;

        case WM_MOUSEMOVE:
            // 鼠标移动，更新终点并重绘
            if (isDrawingCircle || isDrawingRect) {
                endPoint = pt;
                DrawAllShapes();
            }
            else if (isDrawingZhexian && currentZhexian) {
                currentZhexian->updateLastPoint(pt);
                DrawAllShapes();
            }
            else if (isDragging && selectedIndex != -1) {
                // 移动选中的图形
                int dx = pt.x - lastMousePos.x;
                int dy = pt.y - lastMousePos.y;
                shapes[selectedIndex]->move(dx, dy);
                lastMousePos = pt;
                DrawAllShapes();
            }
            break;

        case WM_LBUTTONUP:
            // 左键松开，保存图形并结束绘制
            if (isDrawingCircle) {
                isDrawingCircle = false;
                endPoint = pt;
                int radius = static_cast<int>(std::sqrt(std::pow(endPoint.x - startPoint.x, 2) + std::pow(endPoint.y - startPoint.y, 2)));
                shapes.push_back(std::make_shared<Circle>(startPoint, radius));
                DrawAllShapes();
            }
            else if (isDrawingRect) {
                isDrawingRect = false;
                endPoint = pt;
                shapes.push_back(std::make_shared<Rect>(startPoint, endPoint));
                DrawAllShapes();
            }
            else if (drawZhexianMode) {
                if (isDrawingZhexian && currentZhexian) {
                    currentZhexian->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if (isDragging && selectedIndex != -1) {
                // 停止拖动图形
                isDragging = false;
            }
            break;

        case WM_KEYDOWN:
            // 按下 ESC 键退出程序
            if (msg.mkCtrl == 1) { // 检查是否按下了 Ctrl 键
                if (isDrawingZhexian && currentZhexian) {
                    shapes.push_back(currentZhexian);
                }
                closegraph();
                return 0;
            }
            break;

        case WM_MOUSEWHEEL:
            if (selectMode) {
                short temp = msg.wheel;
                // 选择模式下，按下 a/s 键选择图形
                if (temp == 120) {
                    if (!shapes.empty()) {
                        selectedIndex = (selectedIndex - 1 + shapes.size()) % shapes.size();
                        DrawAllShapes();
                    }
                }
                else {
                    if (!shapes.empty()) {
                        selectedIndex = (selectedIndex + 1) % shapes.size();
                        DrawAllShapes();
                    }
                }
            }
        }
    }

    closegraph();
    return 0;
}
