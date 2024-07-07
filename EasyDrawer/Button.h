#pragma once
#include"tools.h"

class Button {
public:
    Button(int left, int top, int right, int bottom, const TCHAR* text)
        : left(left), top(top), right(right), bottom(bottom), text(text), isPressed(false) {}
    //下面这个构造函数是为了实现按钮的回调函数 绑定事件对象
    Button(int left, int top, int right, int bottom, const TCHAR* text, bool (*callback)(bool))
        : left(left), top(top), right(right), bottom(bottom), text(text), isPressed(false), callback(callback) {}
    void drawColorButtom(int color)
    {
        if (isPressed) {
            setlinecolor(RED);
        }
        else
        {
            setlinecolor(WHITE);
        }
        setfillcolor(color);
        fillrectangle(left, top, right, bottom);

        if (isPressed) {
            setlinecolor(RED);
            line(left, top, right, bottom);
            line(left, bottom, right, top);
        }

    }
    void drawcopyButton(int left, int top, int right, int bottom) {
        this->bottom = bottom;
        this->left = left;
        this->right = right;
        this->top = top;

        THEME == 0 ? setfillcolor(DARKGRAY) : setfillcolor(LIGHTGRAY);
        fillrectangle(left, top, right, bottom);
        THEME == 0 ? setlinecolor(YELLOW) : setlinecolor(BLACK);
        rectangle(left, top, right, bottom);

        settextstyle(21, 0, _T("Arial"));
        THEME == 0 ? settextcolor(YELLOW) : settextcolor(BLACK);
        outtextxy((left + right) / 2 - 5 * 4 + 3, top + 6, _T("拷贝"));
        THEME == 0 ? setlinecolor(YELLOW) : setlinecolor(WHITE);
    }
    void draw() const {
        if (isPressed) {
            if (THEME == 0)
                setfillcolor(RED);

            else {
                setfillcolor(LIGHTRED);
            }
        }
        else {
            if (THEME == 0)
                setfillcolor(BLUE);

            else {
                setfillcolor(LIGHTBLUE);
            }
        }
        setlinecolor(YELLOW);
        if (THEME == 0)
            fillrectangle(left, top, right, bottom);
        else
            fillroundrect(left, top, right, bottom, 10, 10);

        settextstyle(24, 0, _T("Arial"));
        settextcolor(WHITE);
        outtextxy((left + right) / 2 - 5 * sizeof(text), top + 13, text);
        setlinecolor(WHITE);
    }

    bool isInside(int x, int y) const {
        if (x >= left && x <= right && y >= top && y <= bottom) {
            setfillcolor(LIGHTRED);
            fillrectangle(left, top, right, bottom);
            Sleep(50);
            return true;
        }
        else {
            return false;
        }
    }

    void press() {
        isPressed = true;
    }

    void release() {
        isPressed = false;
    }
    bool isPressed;
    bool (*callback)(bool);
private:
    int left, top, right, bottom;
    const WCHAR* text;
    int color;

};


extern Button drawCircleButton;
extern Button drawRectButton;
extern Button drawZhexianButton;
extern Button drawDuoButton;
extern Button drawTuoYuanButton;
extern Button selectShapeButton;
extern Button zoomButton;
extern Button duplicateButton;
extern Button deleteButton;
extern Button fillButton;
extern Button layereditButton;
extern Button insertImageButton;
extern Button changeLineStyleButton;
extern Button modifyLineWidthButton;
extern Button saveButton;
extern Button loadButton;
extern Button insertButton;
extern Button settingsButton;
extern Button clearButton;

extern Button BlackButton;
extern Button RedButton;
extern Button GreenButton;
extern Button BlueButton;
extern Button MagentaButton;
extern Button BrownButton;
extern Button LightGrayButton;

extern Button DarkGrayButton;
extern Button LightBlueButton;
extern Button LightGreenButton;
extern Button LightCyanButton;
extern Button LightRedButton;
extern Button LightMagentaButton;
extern Button CyanButton;
extern Button YellowButton;
extern Button WhiteButton;

extern Button openDoubleClick;
extern Button openTips;
extern Button refreshMouseMove;
extern Button openBatchDraw;

extern Button copyButton;

extern Button themeButton;



extern Button* buttons[10];

extern Button* colourbuttons[16];


void drawButton();

void displaySettings();
