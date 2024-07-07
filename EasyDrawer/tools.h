#pragma once
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

std::string wstring2string(std::wstring wstr);
extern std::string ws;
extern int selectedIndex;
extern int COLOR;

std::wstring colorToString(int color);


LPCWSTR stringToLPCWSTR(std::string str);


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

extern int THEME; // 0Ϊ��ɫ���⣬1Ϊ��ɫ����
extern bool FRESH_WHILE_MOVEMOUSE; // ����ƶ�ʱ�Ƿ�ˢ�»���
extern bool OPEN_TIPS; // �Ƿ����ʾ
extern bool OPEN_DOUBLE_CLICK; // �Ƿ�˫��
extern bool OPEN_BATCH_DRAW;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;


extern bool isDrawingCircle;
extern bool isDrawingRect;
extern bool isDrawingZhexian;
extern bool isDrawingDuo;
extern bool isDrawingTuoyuan;
extern bool isRDraging;
extern POINT startPoint;
extern POINT endPoint;
extern bool isDragging;
extern POINT lastMousePos;


void changeTheme();

// ��ť��


void displaySettings();


// �л�����ĺ���


void CopyTextToClipboard(const std::string& text);


void DrawAllShapes();
std::string convertTCharToString(TCHAR* tcharStr);
void TcharToChar(const TCHAR* tchar, char* _char);