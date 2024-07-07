
#pragma once
#include "tools.h"
#include <easyx.h>
#include <graphics.h>
#include <cmath>
#include <vector>
#include <memory>
#include <conio.h>
#include <string>
#include <codecvt>
#include <locale>
#include <sstream>
#include <algorithm>
#include <CommCtrl.h>
#include <CommDlg.h>
#include <Shlobj.h>
#include <tchar.h>
#include <fstream>
#include <iostream>
#include <map>
#include <functional>

std::string wstring2string(std::wstring wstr)
{
    std::string result;
    //获取缓冲区大小，并申请空间，缓冲区大小事按字节计算的  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //宽字节编码转换成多字节编码  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //删除缓冲区并返回值  
    result.append(buffer);
    delete[] buffer;
    return result;
}
std::string ws;
int selectedIndex = -1;
int COLOR = WHITE;

std::wstring colorToString(int color) {
    switch (color) {
    case BLACK:
        return L"黑色";
    case BLUE:
        return L"蓝色";
    case GREEN:
        return L"绿色";
    case CYAN:
        return L"青色";
    case RED:
        return L"红色";
    case MAGENTA:
        return L"品红";
    case BROWN:
        return L"棕色";
    case LIGHTGRAY:
        return L"浅灰色";
    case DARKGRAY:
        return L"深灰色";
    case LIGHTBLUE:
        return L"浅蓝色";
    case LIGHTGREEN:
        return L"浅绿色";
    case LIGHTCYAN:
        return L"浅青色";
    case LIGHTRED:
        return L"浅红色";
    case LIGHTMAGENTA:
        return L"浅品红";
    case YELLOW:
        return L"黄色";
    case WHITE:
        return L"白色";
    default:
        return L"色值=" + std::to_wstring(color);
    }

}


LPCWSTR stringToLPCWSTR(std::string str)
{
    size_t size = str.length();
    int wLen = ::MultiByteToWideChar(CP_UTF8,
        0,
        str.c_str(),
        -1,
        NULL,
        0);
    wchar_t* buffer = new wchar_t[wLen + 1];
    memset(buffer, 0, (wLen + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), size, (LPWSTR)buffer, wLen);
    return buffer;
}


#define drawCircleMode drawCircleButton.isPressed
#define drawRectMode drawRectButton.isPressed
#define drawZhexianMode drawZhexianButton.isPressed
#define drawDuoMode drawDuoButton.isPressed
#define drawTuoyuanMode drawTuoYuanButton.isPressed
#define selectMode selectShapeButton.isPressed
#define zoomMode zoomButton.isPressed
#define layerEditMode layereditButton.isPressed
#define modifyLineWidthMode modifyLineWidthButton.isPressed
#define settingsMode settingsButton.isPressed

#define canBeSelected (selectMode || zoomMode || layerEditMode || modifyLineWidthMode || settingsMode)

int THEME = 0; // 0为黑色主题，1为白色主题
bool FRESH_WHILE_MOVEMOUSE = false; // 鼠标移动时是否刷新画布
bool OPEN_TIPS = true; // 是否打开提示
bool OPEN_DOUBLE_CLICK = true; // 是否双击
bool OPEN_BATCH_DRAW = true;

int SCREEN_WIDTH = 1600;
int SCREEN_HEIGHT = 900;


bool isDrawingCircle = false;
bool isDrawingRect = false;
bool isDrawingZhexian = false;
bool isDrawingDuo = false;
bool isDrawingTuoyuan = false;
bool isRDraging = false;
POINT startPoint;
POINT endPoint;
bool isDragging = false;
POINT lastMousePos;


void changeTheme()
{
    if (THEME == 0)
    {
        THEME = 1;
        setbkcolor(WHITE);
    }
    else
    {
        THEME = 0;
        setbkcolor(BLACK);
    }
}


// 按钮类


void displaySettings();


// 切换主题的函数


void CopyTextToClipboard(const std::string& text) {
    if (!OpenClipboard(NULL)) {
        return;
    }
    EmptyClipboard();
    HGLOBAL hglb = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
    if (hglb) {
        memcpy(GlobalLock(hglb), text.c_str(), text.size() + 1);
        GlobalUnlock(hglb);
        SetClipboardData(CF_TEXT, hglb);
    }
    CloseClipboard();
}


std::string convertTCharToString(TCHAR* tcharStr)
{
    std::string result;
    // 如果项目使用Unicode，需要从宽字符字符串转换
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    result = myconv.to_bytes(tcharStr);
    return result;
}

void TcharToChar(const TCHAR* tchar, char* _char) {
    int iLength;
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
