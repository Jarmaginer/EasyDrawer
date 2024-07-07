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

#include "Button.h"
#include "tools.h"
#include "Shape.h"
#include "Circle.h"
#include "Rect.h"
#include "Zhexian.h"
#include "Duo.h"
#include "Tuoyuan.h"
#include "Tips.h"


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

class Tips;

void DrawAllShapes();


