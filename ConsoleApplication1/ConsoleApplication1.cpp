#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <vector>
#include <memory>
#include <conio.h>
#include <string>
#include <codecvt>
#include <locale>

#define drawCircleMode drawCircleButton.isPressed
#define drawRectMode drawRectButton.isPressed
#define drawZhexianMode drawZhexianButton.isPressed
#define drawDuoMode drawDuoButton.isPressed
#define drawTuoyuanMode drawTuoYuanButton.isPressed
#define selectMode selectShapeButton.isPressed
#define zoomMode zoomButton.isPressed


// 按钮类
class Button {
public:
    Button(int left, int top, int right, int bottom, const TCHAR* text)
        : left(left), top(top), right(right), bottom(bottom), text(text), isPressed(false) {}

    void draw() const {
        if (isPressed) {
            setfillcolor(RED);
        }
        else {
            setfillcolor(BLUE);
        }
        setlinecolor(YELLOW);
        fillrectangle(left, top, right, bottom);

        settextstyle(24, 0, _T("Consolas"));
        settextcolor(WHITE);
        outtextxy((left + right) / 2 - 5 * sizeof(text), top + 13, text);
        setlinecolor(WHITE);
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
    bool isPressed;
private:
    int left, top, right, bottom;
    const WCHAR* text;

};
Button drawCircleButton(200, 0, 300, 50, _T("圆"));
Button drawRectButton(300, 0, 400, 50, _T("长方形"));
Button drawZhexianButton(400, 0, 500, 50, _T("折线"));
Button drawDuoButton(500, 0, 600, 50, _T("多边形"));
Button drawTuoYuanButton(600, 0, 700, 50, _T("椭圆"));
Button selectShapeButton(700, 0, 800, 50, _T("选择"));
Button zoomButton(800, 0, 900, 50, _T("缩放"));
Button fillButton(900, 0, 1000, 50, _T("填充"));
Button copyButton(1000, 0, 1100, 50, _T("复制"));
Button deleteButton(1100, 0, 1200, 50, _T("删除"));

// 定义一个按钮数组，包含所有需要分组的按钮
Button* buttons[] = {
    &drawCircleButton,
    &drawRectButton,
    &drawZhexianButton,
    &drawDuoButton,
    &drawTuoYuanButton,
    &selectShapeButton,
    &zoomButton
};

// 定义一个函数来更新按钮组状态
void updateButtonGroup(Button* targetButton) {
    for (auto button : buttons) {
        if (button != targetButton) {
            button->release(); // 如果不是目标按钮，释放它
        }
        else {
            button->press();   // 如果是目标按钮，按下去
        }
    }
}



void drawButton() {
    BeginBatchDraw();
    drawCircleButton.draw();
    drawRectButton.draw();
    drawZhexianButton.draw();
    drawDuoButton.draw();
    drawTuoYuanButton.draw();
    selectShapeButton.draw();
    zoomButton.draw();
    copyButton.draw();
    deleteButton.draw();
    fillButton.draw();
    EndBatchDraw();
}


// 基类 Shape，所有图形的抽象基类
class Shape {
public:
    virtual void draw() const = 0;
    virtual RECT getBoundingBox() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual ~Shape() {}
    virtual std::shared_ptr<Shape> clone() const = 0;
    int color = WHITE;
    bool is_fill = false; // 新增成员变量
    virtual void zoom(double factor, POINT center) = 0;
    virtual void setColor(int co) {
        this->color = co;
    }

    void setFill(bool fill) {
        this->is_fill = fill;
    }
};

// 派生类 Circle，表示圆形
class Circle : public Shape {
public:
    Circle(POINT center, int radius) : center(center), radius(radius) {}
    void draw() const override {
        setlinecolor(color);
        if (is_fill) {
            setfillcolor(RED);
            solidcircle(center.x, center.y, radius);
        }
        else {
            circle(center.x, center.y, radius);
        }
        setlinecolor(WHITE);
    }
    RECT getBoundingBox() const override {
        return { center.x - radius, center.y - radius, center.x + radius, center.y + radius };
    }
    void move(int dx, int dy) override {
        center.x += dx;
        center.y += dy;
    }
    void zoom(double factor, POINT zoomCenter) override {
        int dx = center.x - zoomCenter.x;
        int dy = center.y - zoomCenter.y;
        center.x = static_cast<int>(zoomCenter.x + dx * factor);
        center.y = static_cast<int>(zoomCenter.y + dy * factor);
        radius = static_cast<int>(radius * factor);
    }
    std::shared_ptr<Shape> clone() const override {
        return std::make_shared<Circle>(*this);
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
        if (is_fill) {
            setfillcolor(RED);
            solidrectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
        else {
            rectangle(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
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
        return std::make_shared<Rect>(*this);
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
        if (is_fill && points.size() > 2) {
            setfillcolor(RED);
            solidpolygon(&points[0], points.size());
        }
        else {
            for (size_t i = 0; i < points.size() - 1; ++i) {
                setlinecolor(color);
                line(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            }
        }
        setlinecolor(WHITE);
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
private:
    std::vector<POINT> points;
};

class Tuoyuan : public Shape {
public:
    Tuoyuan(POINT topLeft, POINT bottomRight) : topLeft(topLeft), bottomRight(bottomRight) {}
    void draw() const override {
        setlinecolor(color);
        if (is_fill) {
            setfillcolor(RED);
            solidellipse(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
        else {
            ellipse(topLeft.x, topLeft.y, bottomRight.x, bottomRight.y);
        }
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
private:
    POINT topLeft;
    POINT bottomRight;
};



// 派生类 Duo，表示多边形
class Duo : public Shape {
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
        if (points.size() < 3) return;
        setlinecolor(color);
        if (is_fill) {
            setfillcolor(RED);
            solidpolygon(&points[0], points.size());
        }
        else {
            polygon(&points[0], points.size());
        }
        setlinecolor(WHITE);
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
        return std::make_shared<Duo>(*this);
    }
private:
    std::vector<POINT> points;
};

// 全局变量
std::vector<std::shared_ptr<Shape>> shapes;
std::shared_ptr<Zhexian> currentZhexian;
std::shared_ptr<Duo> currentDuo;
bool isDrawingCircle = false;
bool isDrawingRect = false;
bool isDrawingZhexian = false;
bool isDrawingDuo = false;
bool isDrawingTuoyuan = false;
POINT startPoint;
POINT endPoint;
int selectedIndex = -1;
bool isDragging = false;
POINT lastMousePos;

// 绘制所有的图形
void DrawAllShapes() {
    BeginBatchDraw();
    cleardevice();
    drawButton();
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
    else if (isDrawingDuo && currentDuo) {
        currentDuo->draw();
    }
    else if (isDrawingTuoyuan) {
        Tuoyuan tempTuoyuan(startPoint, endPoint);
        tempTuoyuan.draw();
    }


    // 绘制选中的形状的外框
    if (selectedIndex != -1) {
        RECT bbox = shapes[selectedIndex]->getBoundingBox();
        setlinecolor(YELLOW);
        rectangle(bbox.left - 5, bbox.top - 5, bbox.right + 5, bbox.bottom + 5);
        setlinecolor(WHITE);
    }
    EndBatchDraw();
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
        if (!selectMode && !zoomMode) { selectedIndex = -1; }
        drawButton();
        switch (msg.uMsg) {
        case WM_LBUTTONDOWN:
            if (drawCircleButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&drawCircleButton);
                continue;
            }
            else if (drawRectButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&drawRectButton);
                continue;
            }
            else if (drawZhexianButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&drawZhexianButton);
                continue;
            }
            else if (drawDuoButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&drawDuoButton);
                continue;
            }
            else if (selectShapeButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&selectShapeButton);
                continue;
            }
            else if (drawTuoYuanButton.isInside(msg.x, msg.y)) {
                updateButtonGroup(&drawTuoYuanButton);
                continue;
            }
            else if (zoomButton.isInside(msg.x, msg.y)) {
                if (selectedIndex == -1) {
                    HWND hnd = GetHWnd();

                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                    continue;
                }
                drawCircleButton.release();
                drawRectButton.release();
                drawZhexianButton.release();
                drawDuoButton.release();
                selectShapeButton.release();
                drawTuoYuanButton.release();
                zoomButton.press();
                continue;
            }
            else if (copyButton.isInside(msg.x, msg.y)) {
                if (selectedIndex != -1) {
                    // 复制选定的形状
                    std::shared_ptr<Shape> copiedShape = shapes[selectedIndex]->clone(); // 假设Shape类有clone方法
                    // 将复制的形状移动到窗口左上角
                    copiedShape->move(10, 10); // 或者根据需要设置具体位置
                    // 添加复制的形状到shapes向量
                    shapes.push_back(copiedShape);
                    // 更新selectedIndex以选中新复制的形状
                    selectedIndex = shapes.size() - 1;
                    // 重新绘制所有形状
                    DrawAllShapes();
                }
            }
            else if (deleteButton.isInside(msg.x, msg.y)) {
                if (selectedIndex != -1) {
                    // 删除选中的形状
                    shapes.erase(shapes.begin() + selectedIndex);
                    // 清除selectedIndex
                    selectedIndex = -1;
                    // 重新绘制所有形状
                    DrawAllShapes();
                }
            }
            else if (fillButton.isInside(msg.x, msg.y)) {
				if (selectedIndex != -1) {
					shapes[selectedIndex]->setFill(!shapes[selectedIndex]->is_fill);
					DrawAllShapes();
				}
            }
            if (selectMode && isDragging == 0) {
                for (size_t i = 0; i < shapes.size(); ++i) {
                    RECT bbox = shapes[i]->getBoundingBox();
                    if (pt.x >= bbox.left && pt.x <= bbox.right &&
                        pt.y >= bbox.top && pt.y <= bbox.bottom) {
                        selectedIndex = static_cast<int>(i);
                        isDragging = true;
                        lastMousePos = pt;
                        break;
                    }
                }
            }

            if (drawCircleMode) {
                // 左键按下，开始绘制圆
                isDrawingCircle = true;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawRectMode) {
                // 左键按下，开始绘制矩形
                isDrawingRect = true;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawTuoyuanMode) {
                startPoint = { msg.x, msg.y };
                isDrawingTuoyuan = true;
            }
            else if (drawZhexianMode) {
                // 左键按下，绘制折线
                if (!isDrawingZhexian) {
                    isDrawingZhexian = true;
                    currentZhexian = std::make_shared<Zhexian>();
                    currentZhexian->addPoint(pt);
                }
                else if (isDrawingZhexian && currentZhexian) {
                    currentZhexian->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if (drawDuoMode) {
                // 左键按下，绘制多边形
                if (!isDrawingDuo) {
                    isDrawingDuo = true;
                    currentDuo = std::make_shared<Duo>();
                    currentDuo->addPoint(pt);
                }
                else if (isDrawingDuo && currentDuo) {
                    currentDuo->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if ((selectMode || zoomMode) && selectedIndex != -1) {
                // 左键按下，开始拖动选中的图形
                isDragging = true;
                lastMousePos = pt;
            }
            break;

        case WM_RBUTTONDOWN:
            // 右键按下，结束折线绘制或多边形绘制
            if (isDrawingZhexian && currentZhexian) {
                shapes.push_back(currentZhexian);
                currentZhexian.reset();
                isDrawingZhexian = false;
                DrawAllShapes();
            }
            else if (isDrawingDuo && currentDuo) {
                shapes.push_back(currentDuo);
                currentDuo.reset();
                isDrawingDuo = false;
                DrawAllShapes();
            }
            break;

        case WM_MOUSEMOVE:
            // 鼠标移动，更新终点并重绘
            if (isDrawingCircle || isDrawingRect || isDrawingTuoyuan) {
                endPoint = pt;
                DrawAllShapes();
            }
            else if (isDrawingZhexian && currentZhexian) {
                currentZhexian->updateLastPoint(pt);
                DrawAllShapes();
            }
            else if (isDrawingDuo && currentDuo) {
                currentDuo->updateLastPoint(pt);
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
            else if (drawDuoMode) {
                if (isDrawingDuo && currentDuo) {
                    currentDuo->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if (isDrawingTuoyuan) {
                shapes.push_back(std::make_shared<Tuoyuan>(startPoint, endPoint));
                isDrawingTuoyuan = false;
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
                if (isDrawingDuo && currentDuo) {
                    shapes.push_back(currentDuo);
                }
                closegraph();
                return 0;
            }
            break;

        case WM_MOUSEWHEEL:
            if (selectMode) {
                short temp = msg.wheel;
                // 选择模式下，鼠标滚轮选择图形
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
            if (zoomMode && selectedIndex != -1) {
                double factor = msg.wheel > 0 ? 1.1 : 0.9;
                shapes[selectedIndex]->zoom(factor, pt);
                DrawAllShapes();
            }
            break;

        case WM_MBUTTONDOWN:
            // 中键按下，将选中的图形设为填充
            if (selectMode && selectedIndex != -1) {
                shapes[selectedIndex]->setFill(!shapes[selectedIndex]->is_fill);
                DrawAllShapes();
            }
            break;
        }
    }

    closegraph();
    return 0;
}