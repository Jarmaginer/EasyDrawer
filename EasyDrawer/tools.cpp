
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
    //��ȡ��������С��������ռ䣬��������С�°��ֽڼ����  
    int len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), NULL, 0, NULL, NULL);
    char* buffer = new char[len + 1];
    //���ֽڱ���ת���ɶ��ֽڱ���  
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), wstr.size(), buffer, len, NULL, NULL);
    buffer[len] = '\0';
    //ɾ��������������ֵ  
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
        return L"��ɫ";
    case BLUE:
        return L"��ɫ";
    case GREEN:
        return L"��ɫ";
    case CYAN:
        return L"��ɫ";
    case RED:
        return L"��ɫ";
    case MAGENTA:
        return L"Ʒ��";
    case BROWN:
        return L"��ɫ";
    case LIGHTGRAY:
        return L"ǳ��ɫ";
    case DARKGRAY:
        return L"���ɫ";
    case LIGHTBLUE:
        return L"ǳ��ɫ";
    case LIGHTGREEN:
        return L"ǳ��ɫ";
    case LIGHTCYAN:
        return L"ǳ��ɫ";
    case LIGHTRED:
        return L"ǳ��ɫ";
    case LIGHTMAGENTA:
        return L"ǳƷ��";
    case YELLOW:
        return L"��ɫ";
    case WHITE:
        return L"��ɫ";
    default:
        return L"ɫֵ=" + std::to_wstring(color);
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

int THEME = 0; // 0Ϊ��ɫ���⣬1Ϊ��ɫ����
bool FRESH_WHILE_MOVEMOUSE = false; // ����ƶ�ʱ�Ƿ�ˢ�»���
bool OPEN_TIPS = true; // �Ƿ����ʾ
bool OPEN_DOUBLE_CLICK = true; // �Ƿ�˫��
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


// ��ť��


void displaySettings();


// �л�����ĺ���


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
    // �����Ŀʹ��Unicode����Ҫ�ӿ��ַ��ַ���ת��
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    result = myconv.to_bytes(tcharStr);
    return result;
}

void TcharToChar(const TCHAR* tchar, char* _char) {
    int iLength;
    iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
}
