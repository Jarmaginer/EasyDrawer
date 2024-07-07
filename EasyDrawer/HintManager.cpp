#include "HintManager.h"

void HintManager::updateHints(const POINT& mousePos, const std::string& mode, std::string tips) {
    this->mousePos = mousePos;
    this->mode = mode;
    this->tips = tips;
    if (FRESH_WHILE_MOVEMOUSE)
    {
        DrawAllShapes();
    }
}

void HintManager::displayHints() const {
    settextstyle(16, 0, _T("Arial"));
    !THEME ? settextcolor(LIGHTGRAY) : settextcolor(DARKGRAY);
    outtextxy(5, SCREEN_HEIGHT - 60, stringToLPCWSTR(("点击位置: (" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")")));
    outtextxy(5, SCREEN_HEIGHT - 40, stringToLPCWSTR(("模式: " + mode)));
    outtextxy(5, SCREEN_HEIGHT - 20, stringToLPCWSTR("提示: " + tips));
}

void HintManager::updatePt(POINT pt) {
    this->mousePos = pt;
    if (FRESH_WHILE_MOVEMOUSE)
    {
        DrawAllShapes();
    }
}
