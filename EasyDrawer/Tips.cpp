#include "Tips.h"

void Tips::updateHints(const POINT& mousePos, const std::string& mode, std::string tips) {
    this->mousePos = mousePos;
    this->mode = mode;
    this->tips = tips;
    if (FRESH_WHILE_MOVEMOUSE)
    {
        DrawAllShapes();
    }
}

void Tips::displayHints() const {
    settextstyle(16, 0, _T("Arial"));
    !THEME ? settextcolor(LIGHTGRAY) : settextcolor(DARKGRAY);
    outtextxy(5, SCREEN_HEIGHT - 60, stringToLPCWSTR(("���λ��: (" + std::to_string(mousePos.x) + ", " + std::to_string(mousePos.y) + ")")));
    outtextxy(5, SCREEN_HEIGHT - 40, stringToLPCWSTR(("ģʽ: " + mode)));
    outtextxy(5, SCREEN_HEIGHT - 20, stringToLPCWSTR("��ʾ: " + tips));
}

void Tips::updatePt(POINT pt) {
    this->mousePos = pt;
    if (FRESH_WHILE_MOVEMOUSE)
    {
        DrawAllShapes();
    }
}
