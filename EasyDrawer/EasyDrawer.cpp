#include"Circle.h"
#include"Rect.h"
#include"Duo.h"
#include"Zhexian.h"
#include"Tuoyuan.h"
#include "Button.h"
#include"Tips.h"
#include"Image.h"

Tips hintManager;
std::vector<std::shared_ptr<Shape>> shapes;
std::shared_ptr<Zhexian> currentZhexian;
std::shared_ptr<Duo> currentDuo;



int loadProject(const std::string& filePath, std::vector<std::shared_ptr<Shape>>& shapes, bool needClear = true) {
    int count = 0;
    std::fstream file(filePath);
    if (!file) {
        std::wcerr << L"文件打开失败！" << std::endl;
        return -1;
    }
    if (needClear) shapes.clear();
    selectedIndex = -1;
    std::string line;
    std::map<std::string, std::function<std::shared_ptr<Shape>()>> shapeCreators = {
        { "Circle", []() -> std::shared_ptr<Shape> { return std::make_shared<Circle>(); } },
        { "Rect", []() -> std::shared_ptr<Shape> { return std::make_shared<Rect>(); } },
        { "Zhexian", []() -> std::shared_ptr<Shape> { return std::make_shared<Zhexian>(); } },
        { "Duo", []() -> std::shared_ptr<Shape> { return std::make_shared<Duo>(); } },
        { "Tuoyuan", []() -> std::shared_ptr<Shape> { return std::make_shared<Tuoyuan>(); } },
        { "Image", []() -> std::shared_ptr<Shape> { return std::make_shared<Image>(); } }
    };

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string shapeType;
        ss >> shapeType;

        if (shapeCreators.find(shapeType) != shapeCreators.end()) {
            std::shared_ptr<Shape> shape = shapeCreators[shapeType]();
            shape->parseInfoFromStream(ss);
            shapes.push_back(shape);
            count++;
        }
    }
    return count;
}

bool saveProject(const std::vector<std::shared_ptr<Shape>>& shapes) {
    OPENFILENAME ofn;
    TCHAR szFileName[MAX_PATH] = { 0 };

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_EXPLORER | OFN_ENABLESIZING;
    ofn.lpstrFilter = _T("Text文件 (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = _T(".");

    if (GetSaveFileName(&ofn)) {
        std::ofstream file(ofn.lpstrFile);
        if (!file) {
            return false;
        }

        for (const auto& shape : shapes) {
            file << (shape->generateLabel()) << "\n";
        }

        return true;
        file.close();
    }

    return false;
}


void DrawAllShapes() {

    if (OPEN_BATCH_DRAW) BeginBatchDraw();
    cleardevice();
    if (OPEN_TIPS) hintManager.displayHints();
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
    if (selectedIndex != -1) {
        RECT bbox = shapes[selectedIndex]->getBoundingBox();
        THEME == 0 ? setlinecolor(YELLOW) : setlinecolor(DARKGRAY);
        rectangle(bbox.left - 5, bbox.top - 5, bbox.right + 5, bbox.bottom + 5);
        setlinecolor(WHITE);

        // 显示信息
        std::wstring info = shapes[selectedIndex]->getInfo();
        settextstyle(18, 0, _T("Arial")); // 设置字体样式
        THEME == 0 ? settextcolor(YELLOW) : settextcolor(DARKGRAY);
        //outtextxy(bbox.right - 200, bbox.bottom + 10, info.c_str()); // 在外框右下角显示信息
        int y = bbox.bottom + 10; // 初始y坐标
        for (size_t pos = 0; pos < info.length(); ) {
            size_t next_pos = info.find(L'\n', pos);
            if (next_pos == std::wstring::npos) {
                next_pos = info.length();
            }
            outtextxy(bbox.left, y, info.substr(pos, next_pos - pos).c_str());
            y += 20; // 调整y坐标以适应下一行
            pos = next_pos + 1;
        }

        copyButton.drawcopyButton(bbox.right - 40, bbox.bottom + 10, bbox.right, bbox.bottom + 40);

        for (const auto& shape : shapes) {
            // 如果图形被选中
            if (selectedIndex != -1 && shape.get() == shapes[selectedIndex].get()) {
                // 计算层级信息的字符串
                std::wstring layerInfo = L"层级: " + std::to_wstring(selectedIndex);
                std::wstring lineInfo = L"线宽: " + std::to_wstring(shape->lineWidth) + L"  线型: " + std::to_wstring(shape->lineStyle);

                // 设置字体和颜色
                settextstyle(18, 0, _T("Arial")); // 或者选择合适的字体大小和样式
                THEME == 0 ? settextcolor(YELLOW) : settextcolor(DARKGRAY);

                // 计算位置
                int posX = bbox.left; // 距离图形右边界5个单位
                int posY = bbox.top - 30; // 距离图形顶部5个单位

                // 输出层级信息
                outtextxy(posX, posY, layerInfo.c_str());

                posX = bbox.right - 100; // 距离图形右边界5个单位
                posY = bbox.top - 30; // 距离图形顶部5个单位
                outtextxy(posX, posY, lineInfo.c_str());
            }
        }
    }

    // 绘制选中的形状的外框

    if (OPEN_BATCH_DRAW) EndBatchDraw();
}

void pressButton(Button* targetButton) {
    for (auto button : buttons) {
        if (button != targetButton) {
            button->release(); // 如果不是目标按钮，释放它
        }
        else {
            button->press();   // 如果是目标按钮，按下去
        }
    }
    DrawAllShapes();
}

void pressColourButtom(Button* targetButton) {
    for (auto button : colourbuttons) {
        if (button != targetButton) {
            button->release(); // 如果不是目标按钮，释放它
        }
        else {
            button->press();   // 如果是目标按钮，按下去
            if (selectedIndex != -1) {
                shapes[selectedIndex]->setColor(COLOR);
                DrawAllShapes();
            }
        }
    }
}

int main() {
    OPEN_DOUBLE_CLICK ? initgraph(1500, 900, EX_SHOWCONSOLE | EX_DBLCLKS) : initgraph(1500, 900, EX_SHOWCONSOLE);
    setbkmode(TRANSPARENT);
    cleardevice();
    drawButton();
    if (OPEN_TIPS) { hintManager.updateHints({ 0, 0 }, "绘圆", "左键确定圆心，拖拽确定半径"); hintManager.displayHints(); }
    drawCircleButton.press();
    WhiteButton.press();
    while (true) {

        MOUSEMSG msg = GetMouseMsg();
        drawButton();
        POINT pt = { msg.x, msg.y };
        if (THEME == 1)
        {
            setbkcolor(WHITE);
        }
        else
        {
            setbkcolor(BLACK);
        }
        if (OPEN_TIPS) hintManager.updatePt(pt);
        if (!canBeSelected) { selectedIndex = -1; }
        if (OPEN_DOUBLE_CLICK && msg.uMsg == WM_LBUTTONDBLCLK)
        {
            if (OPEN_TIPS) hintManager.updateHints(pt, "选择图形", "左键点击选择图形，拖动移动，滚轮选择图形，右键修改图形参数");
            pressButton(&selectShapeButton);
            for (size_t i = 0; i < shapes.size(); ++i) {
                RECT bbox = shapes[i]->getBoundingBox();
                if (pt.x >= bbox.left && pt.x <= bbox.right &&
                    pt.y >= bbox.top && pt.y <= bbox.bottom) {
                    selectedIndex = static_cast<int>(i);

                    break;
                }
            }
            isDragging = true;
            lastMousePos = pt;
            DrawAllShapes();
        }
        if (settingsMode)
        {
            displaySettings();
        }

        switch (msg.uMsg) {
        case WM_DESTROY: 
            closegraph();
            PostQuitMessage(0);
            return 0;

        case WM_LBUTTONDOWN:
            if (settingsMode) {
                if (themeButton.isInside(msg.x, msg.y))
                {
                    THEME = 1 - THEME;
                    if (THEME == 1)
                    {
                        setbkcolor(WHITE);
                    }
                    else
                    {
                        setbkcolor(BLACK);
                    }
                    DrawAllShapes();
                }
                else if (refreshMouseMove.isInside(msg.x, msg.y)) {
                    FRESH_WHILE_MOVEMOUSE = 1 - FRESH_WHILE_MOVEMOUSE;

                    DrawAllShapes();
                }
                else if (openTips.isInside(msg.x, msg.y))
                {
                    OPEN_TIPS = 1 - OPEN_TIPS;
                    DrawAllShapes();
                }
                else if (openDoubleClick.isInside(msg.x, msg.y))
                {
                    OPEN_DOUBLE_CLICK = 1 - OPEN_DOUBLE_CLICK;
                    OPEN_DOUBLE_CLICK ? initgraph(1500, 900, EX_SHOWCONSOLE | EX_DBLCLKS) : initgraph(1500, 900, EX_SHOWCONSOLE);
                    setbkmode(TRANSPARENT);
                    DrawAllShapes();
                }
                else if (openBatchDraw.isInside(msg.x, msg.y))
                {
                    OPEN_BATCH_DRAW = 1 - OPEN_BATCH_DRAW;
                    DrawAllShapes();
                }
                else if (!(msg.x >= 449 && msg.x <= 1064 && msg.y >= 245 && msg.y <= 633))
                {
                    settingsMode = 0;
                    DrawAllShapes();
                }
            }
            if (insertImageButton.isInside(msg.x, msg.y)) {
                OPENFILENAME ofn;
                TCHAR szFile[260] = { 0 };
                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = GetHWnd();
                ofn.lpstrFile = szFile;
                ofn.nMaxFile = sizeof(szFile);
                ofn.lpstrFilter = _T("图像文件(*.bmp;*.jpg;*.png)\0*.bmp;*.jpg;*.png\0");
                ofn.nFilterIndex = 1;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

                if (GetOpenFileName(&ofn)) {
                    std::string filePath = convertTCharToString(szFile);
                    std::shared_ptr<Image> image = std::make_shared<Image>();
                    if (image->loadImage(filePath)) {
                        shapes.push_back(image);
                        DrawAllShapes();
                    }
                    else {
                        HWND hnd = GetHWnd();
                        MessageBox(hnd, _T("无法加载图片"), _T("错误"), MB_OK);
                    }
                }
            }
            else if (settingsButton.isInside(msg.x, msg.y)) {
                pressButton(&settingsButton);
            }
            else if (saveButton.isInside(msg.x, msg.y)) {
                if (saveProject(shapes)) {
                    MessageBox(GetHWnd(), _T("保存成功"), _T("提示"), MB_OK);
                }
                else {
                    MessageBox(GetHWnd(), _T("保存失败"), _T("错误"), MB_OK);
                }

            }
            else if (loadButton.isInside(msg.x, msg.y)) {
                OPENFILENAME ofn;
                TCHAR szFileName[MAX_PATH] = { 0 };

                ZeroMemory(&ofn, sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER;
                ofn.lpstrFilter = _T("Text文件 (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
                ofn.nFilterIndex = 1;
                ofn.lpstrInitialDir = _T(".");

                if (GetOpenFileName(&ofn)) {
                    std::string filePath = convertTCharToString(szFileName);
                    loadProject(filePath, shapes);
                    DrawAllShapes();
                }
            }
            else if (insertButton.isInside(msg.x, msg.y)) {
                HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
                AttachConsole(ATTACH_PARENT_PROCESS);
                //SetConsoleActiveProcess(GetCurrentProcessId());

                // 接收多行输入
                std::cout << "输入对象标签(输入end结束):" << std::endl;
                std::string input;

                std::map<std::string, std::function<std::shared_ptr<Shape>()>> shapeCreators = {
                    { "Circle", []() -> std::shared_ptr<Shape> { return std::make_shared<Circle>(); } },
                    { "Rect", []() -> std::shared_ptr<Shape> { return std::make_shared<Rect>(); } },
                    { "Zhexian", []() -> std::shared_ptr<Shape> { return std::make_shared<Zhexian>(); } },
                    { "Duo", []() -> std::shared_ptr<Shape> { return std::make_shared<Duo>(); } },
                    { "Tuoyuan", []() -> std::shared_ptr<Shape> { return std::make_shared<Tuoyuan>(); } },
                    { "Image", []() -> std::shared_ptr<Shape> { return std::make_shared<Image>(); } }
                };
                int count = 0;
                while (std::getline(std::cin, input) && input != "end") {
                    std::stringstream ss(input);
                    std::string shapeType;
                    ss >> shapeType;

                    if (shapeCreators.find(shapeType) != shapeCreators.end()) {
                        std::shared_ptr<Shape> shape = shapeCreators[shapeType]();
                        shape->parseInfoFromStream(ss);
                        shapes.push_back(shape);

                        count++;
                    }
                }
                std::cout << "成功置入" << count << "个对象" << std::endl;
                MessageBox(GetHWnd(), stringToLPCWSTR(("成功置入" + std::to_string(count) + "个对象")), _T("提示"), MB_OK);
                FreeConsole();
                DrawAllShapes();
            }
            else if (modifyLineWidthButton.isInside(msg.x, msg.y))
            {
                pressButton(&modifyLineWidthButton);
                if (OPEN_TIPS) hintManager.updateHints(pt, "修改线宽", "滚轮上下滚动增减线宽");
                continue;
            }
            else if (layereditButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "图层编辑", "滚轮上下滚动改变层级");
                pressButton(&layereditButton);
                continue;
            }
            else if (clearButton.isInside(msg.x, msg.y))
            {
                shapes.clear();
                selectedIndex = -1;
                DrawAllShapes();
                continue;
            }
            else if (copyButton.isInside(msg.x, msg.y)) {
                std::string label = shapes[selectedIndex]->generateLabel();
                CopyTextToClipboard(label);
                MessageBox(GetHWnd(), _T("已将标签拷贝到剪贴板"), _T("提示"), MB_OK);
                DrawAllShapes();
            }
            else if (BlackButton.isInside(msg.x, msg.y)) {
                COLOR = BLACK;
                pressColourButtom(&BlackButton);

                continue;
            }
            else if (BlueButton.isInside(msg.x, msg.y)) {
                COLOR = BLUE;
                pressColourButtom(&BlueButton);

                continue;

            }
            else if (GreenButton.isInside(msg.x, msg.y)) {
                COLOR = GREEN;
                pressColourButtom(&GreenButton);

                continue;
            }
            else if (CyanButton.isInside(msg.x, msg.y)) {
                COLOR = CYAN;
                pressColourButtom(&CyanButton);

                continue;
            }
            else if (RedButton.isInside(msg.x, msg.y)) {
                COLOR = RED;
                pressColourButtom(&RedButton);

                continue;
            }
            else if (MagentaButton.isInside(msg.x, msg.y)) {
                COLOR = MAGENTA;
                pressColourButtom(&MagentaButton);

                continue;
            }
            else if (BrownButton.isInside(msg.x, msg.y)) {
                COLOR = BROWN;
                pressColourButtom(&BrownButton);

                continue;
            }
            else if (LightGrayButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTGRAY;
                pressColourButtom(&LightGrayButton);

                continue;
            }
            else if (DarkGrayButton.isInside(msg.x, msg.y)) {
                COLOR = DARKGRAY;
                pressColourButtom(&DarkGrayButton);

                continue;
            }
            else if (LightBlueButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTBLUE;
                pressColourButtom(&LightBlueButton);

                continue;
            }
            else if (LightGreenButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTGREEN;
                pressColourButtom(&LightGreenButton);

                continue;
            }
            else if (LightCyanButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTCYAN;
                pressColourButtom(&LightCyanButton);

                continue;
            }
            else if (LightRedButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTRED;
                pressColourButtom(&LightRedButton);

                continue;
            }
            else if (LightMagentaButton.isInside(msg.x, msg.y)) {
                COLOR = LIGHTMAGENTA;
                pressColourButtom(&LightMagentaButton);

                continue;
            }
            else if (YellowButton.isInside(msg.x, msg.y)) {
                COLOR = YELLOW;
                pressColourButtom(&YellowButton);

                continue;
            }
            else if (WhiteButton.isInside(msg.x, msg.y)) {
                COLOR = WHITE;
                pressColourButtom(&WhiteButton);

                continue;
            }
            else if (drawCircleButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "绘制圆", "拖拽画圆");
                pressButton(&drawCircleButton);
                continue;
            }
            else if (drawRectButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "绘制矩形", "拖拽画矩形");
                pressButton(&drawRectButton);
                continue;
            }
            else if (drawZhexianButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "绘制折线", "左键点击确定第一个点，点击左键确定下一个点，右键结束");
                pressButton(&drawZhexianButton);
                continue;
            }
            else if (drawDuoButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "绘制多边形", "左键点击确定第一个点，点击左键确定下一个点，右键结束");
                pressButton(&drawDuoButton);
                continue;
            }
            else if (selectShapeButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "选择图形", "左键点击选择图形，拖动移动，滚轮选择图形，右键修改图形参数");
                pressButton(&selectShapeButton);
                continue;
            }
            else if (drawTuoYuanButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "绘制椭圆", "拖拽画椭圆");
                pressButton(&drawTuoYuanButton);
                continue;
            }
            else if (zoomButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "缩放", "滚轮上下滚动缩放图形");
                pressButton(&zoomButton);
                continue;
            }
            else if (duplicateButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "复制", "复制选中的图形");
                if (selectedIndex == -1) {
                    HWND hnd = GetHWnd();

                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                    continue;
                }
                if (selectedIndex != -1) {
                    std::shared_ptr<Shape> copiedShape = shapes[selectedIndex]->clone();
                    copiedShape->move(10, 10);
                    shapes.push_back(copiedShape);
                    selectedIndex = shapes.size() - 1;
                    DrawAllShapes();
                }
            }
            else if (deleteButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "删除", "删除选中的图形");
                if (selectedIndex == -1) {
                    HWND hnd = GetHWnd();

                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                    continue;
                }
                if (selectedIndex != -1) {
                    shapes.erase(shapes.begin() + selectedIndex);
                    selectedIndex--;
                    DrawAllShapes();
                }
            }
            else if (fillButton.isInside(msg.x, msg.y)) {
                if (OPEN_TIPS) hintManager.updateHints(pt, "填充", "填充选中的图形");
                if (selectedIndex != -1) {
                    shapes[selectedIndex]->setFill(!shapes[selectedIndex]->is_fill);
                    shapes[selectedIndex]->setFillColour(COLOR);
                    DrawAllShapes();
                }
                else {
                    HWND hnd = GetHWnd();

                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                    continue;
                }
            }
            else if (changeLineStyleButton.isInside(msg.x, msg.y)) {
                if (selectedIndex != -1) {
                    shapes[selectedIndex]->changeLineStyle();
                    DrawAllShapes();
                }
                else {
                    HWND hnd = GetHWnd();

                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                    continue;
                }
            }

            else if (canBeSelected) {
                for (size_t i = 0; i < shapes.size(); ++i) {
                    RECT bbox = shapes[shapes.size() - i - 1]->getBoundingBox();
                    if (pt.x >= bbox.left && pt.x <= bbox.right &&
                        pt.y >= bbox.top && pt.y <= bbox.bottom) {
                        selectedIndex = static_cast<int>(shapes.size() - i - 1);

                        break;
                    }
                }
                isDragging = true;
                lastMousePos = pt;
                DrawAllShapes();
            }
            else if (drawCircleMode) {
                isDrawingCircle = true;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawRectMode) {
                isDrawingRect = true;
                startPoint = pt;
                endPoint = startPoint;
            }
            else if (drawTuoyuanMode) {
                startPoint = { msg.x, msg.y };
                isDrawingTuoyuan = true;
            }
            else if (drawZhexianMode) {
                if (!isDrawingZhexian) {
                    isDrawingZhexian = true;
                    currentZhexian = std::make_shared<Zhexian>();
                    currentZhexian->addPoint(pt);
                }
                else if (isDrawingZhexian && currentZhexian) {
                    //currentZhexian->addPoint(pt);
                    DrawAllShapes();
                }
            }
            else if (drawDuoMode) {
                if (!isDrawingDuo) {
                    isDrawingDuo = true;
                    currentDuo = std::make_shared<Duo>();
                    currentDuo->addPoint(pt);
                }
                else if (isDrawingDuo && currentDuo) {
                    //currentDuo->addPoint(pt);
                    DrawAllShapes();
                }
            }

            break;


        case WM_RBUTTONDOWN:
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
            else if (canBeSelected) {

                isRDraging = true;
            }
            break;

        case WM_MOUSEMOVE:
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
                int dx = pt.x - lastMousePos.x;
                int dy = pt.y - lastMousePos.y;
                shapes[selectedIndex]->move(dx, dy);
                lastMousePos = pt;
                DrawAllShapes();
            }
            else if (isRDraging && selectedIndex != -1) {
                shapes[selectedIndex]->changePoints(msg.x, msg.y);
                DrawAllShapes();
            }
            break;

        case WM_LBUTTONUP:
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
                isDragging = false;
            }
            break;

        case WM_MOUSEWHEEL:
            if (selectMode) {
                short temp = msg.wheel;
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
            if (layerEditMode && selectedIndex != -1) {
                short temp = msg.wheel;
                if (temp == 120) {
                    // 上移一层
                    if (selectedIndex > 0) {
                        std::swap(shapes[selectedIndex], shapes[selectedIndex - 1]);
                        selectedIndex--;
                    }
                }
                else {
                    // 下移一层
                    if (selectedIndex < shapes.size() - 1) {
                        std::swap(shapes[selectedIndex], shapes[selectedIndex + 1]);
                        selectedIndex++;
                    }
                }
                DrawAllShapes();
            }
            if (modifyLineWidthMode) {
                if (selectedIndex == -1) {
                    HWND hnd = GetHWnd();
                    MessageBox(hnd, _T("必须先选择一个图形"), _T("提示"), MB_OK);
                }
                else {
                    short temp = msg.wheel;
                    if (temp == 120) {
                        shapes[selectedIndex]->addLineWidth();
                    }
                    else {
                        shapes[selectedIndex]->reduceLineWidth();
                    }
                    DrawAllShapes();
                }
            }
            break;

        case WM_MBUTTONDOWN:
            if (selectMode && selectedIndex != -1) {
                shapes[selectedIndex]->setFill(!shapes[selectedIndex]->is_fill);
                DrawAllShapes();
            }
            break;
        case WM_RBUTTONUP:
            if (isRDraging && selectedIndex != -1) {
                isRDraging = false;
            }
            break;

        }

    }
    closegraph();
    return 0;
}