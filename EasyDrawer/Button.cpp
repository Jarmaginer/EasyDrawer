#include "Button.h"
Button drawCircleButton(200, 0, 300, 50, _T("Բ"));

Button drawRectButton(300, 0, 400, 50, _T("����"));
Button drawZhexianButton(400, 0, 500, 50, _T("����"));
Button drawDuoButton(500, 0, 600, 50, _T("�����"));
Button drawTuoYuanButton(600, 0, 700, 50, _T("��Բ"));
Button selectShapeButton(700, 0, 800, 50, _T("ѡ��"));
Button zoomButton(800, 0, 900, 50, _T("����"));
Button fillButton(900, 0, 1000, 50, _T("���"));
Button duplicateButton(1000, 0, 1100, 50, _T("����"));
Button deleteButton(1100, 0, 1200, 50, _T("ɾ��"));
Button changeLineStyleButton(1200, 0, 1300, 50, _T("�ı�����"));
Button modifyLineWidthButton(1300, 0, 1400, 50, _T("�޸��߿�"));
Button insertImageButton(1400, 0, 1500, 50, _T("����ͼƬ"));
Button insertButton(1400, 50, 1500, 100, _T("����ͼ��"));

Button layereditButton(1400, 100, 1500, 150, _T("ͼ��༭"));
Button clearButton(1400, 150, 1500, 200, L"��ջ���");
Button saveButton(1400, 200, 1500, 250, _T("���湤��"));
Button loadButton(1400, 250, 1500, 300, _T("��ȡ����"));
//Button insertButton(1400, 200, 1500, 250, _T("�������"));
Button settingsButton(1400, 300, 1500, 350, _T("����"));

Button copyButton(-100, -100, -25, -25, _T("����"));

Button WhiteButton(0, 0, 25, 25, _T(""));
Button RedButton(25, 0, 50, 25, _T(""));
Button GreenButton(50, 0, 75, 25, _T(""));
Button BlueButton(75, 0, 100, 25, _T(""));
Button MagentaButton(100, 0, 125, 25, _T(""));
Button BrownButton(125, 0, 150, 25, _T(""));
Button LightGrayButton(150, 0, 175, 25, _T(""));
Button DarkGrayButton(175, 0, 200, 25, _T(""));
Button LightBlueButton(0, 25, 25, 50, _T(""));
Button LightGreenButton(25, 25, 50, 50, _T(""));
Button LightCyanButton(50, 25, 75, 50, _T(""));
Button LightRedButton(75, 25, 100, 50, _T(""));
Button LightMagentaButton(100, 25, 125, 50, _T(""));
Button CyanButton(125, 25, 150, 50, _T(""));
Button YellowButton(150, 25, 175, 50, _T(""));
Button BlackButton(175, 25, 200, 50, _T(""));


Button themeButton(888, 350, 948, 380, _T("�л�����"));
Button openTips(888, 380, 948, 410, _T("������ʾ"));
Button refreshMouseMove(888, 410, 948, 440, _T("����ƶ�ˢ��"));
Button openDoubleClick(888, 440, 948, 470, _T("˫��"));
Button openBatchDraw(888, 470, 948, 500, _T("˫������"));





void drawButton() {
    BeginBatchDraw();
    clearButton.draw();
    drawCircleButton.draw();
    drawRectButton.draw();
    drawZhexianButton.draw();
    drawDuoButton.draw();
    drawTuoYuanButton.draw();
    selectShapeButton.draw();
    zoomButton.draw();
    duplicateButton.draw();
    deleteButton.draw();
    fillButton.draw();
    layereditButton.draw();
    insertImageButton.draw();

    changeLineStyleButton.draw();
    modifyLineWidthButton.draw();
    saveButton.draw();
    loadButton.draw();
    insertButton.draw();
    settingsButton.draw();

    BlackButton.drawColorButtom(BLACK);
    RedButton.drawColorButtom(RED);
    GreenButton.drawColorButtom(GREEN);
    BlueButton.drawColorButtom(BLUE);
    MagentaButton.drawColorButtom(MAGENTA);
    BrownButton.drawColorButtom(BROWN);
    LightGrayButton.drawColorButtom(LIGHTGRAY);
    DarkGrayButton.drawColorButtom(DARKGRAY);
    LightBlueButton.drawColorButtom(LIGHTBLUE);
    LightGreenButton.drawColorButtom(LIGHTGREEN);
    LightCyanButton.drawColorButtom(LIGHTCYAN);
    LightRedButton.drawColorButtom(LIGHTRED);
    LightMagentaButton.drawColorButtom(LIGHTMAGENTA);
    CyanButton.drawColorButtom(CYAN);
    YellowButton.drawColorButtom(YELLOW);
    WhiteButton.drawColorButtom(WHITE);

    EndBatchDraw();
}

void displaySettings() {
    BeginBatchDraw();
    settextstyle(30, 0, _T("Arial"));
    settextcolor(WHITE);
    setlinecolor(WHITE);
    !THEME ? setfillcolor(DARKGRAY) : setfillcolor(LIGHTBLUE);

    !THEME ? fillrectangle(449, 245, 1064, 633) : fillroundrect(449, 245, 1064, 633, 30, 30);

    outtextxy(705, 252, stringToLPCWSTR("���ò˵�"));

    outtextxy(532, 352, stringToLPCWSTR("���û���������ɫ"));
    outtextxy(892, 352, stringToLPCWSTR((THEME == 0) ? "��ɫ" : "��ɫ"));

    outtextxy(532, 382, stringToLPCWSTR("��ʾϵͳ"));
    outtextxy(892, 382, stringToLPCWSTR(OPEN_TIPS ? "����" : "�ر�"));

    outtextxy(532, 412, stringToLPCWSTR(("����ƶ�ʱˢ�»���")));
    outtextxy(892, 412, stringToLPCWSTR(FRESH_WHILE_MOVEMOUSE ? "����" : "�ر�"));

    outtextxy(532, 442, stringToLPCWSTR(("�������˫���¼�")));
    outtextxy(892, 442, stringToLPCWSTR(OPEN_DOUBLE_CLICK ? "����" : "�ر�"));

    outtextxy(532, 472, stringToLPCWSTR(("����˫��������Ⱦ�Ż�")));
    outtextxy(892, 472, stringToLPCWSTR(OPEN_BATCH_DRAW ? "����" : "�ر�"));



    //themeButton.draw();
    //refreshMouseMove.draw();
    //openTips.draw();
    //openDoubleClick.draw();

    EndBatchDraw();
}

Button* buttons[10] = {
    &drawCircleButton,
    &drawRectButton,
    &drawZhexianButton,
    &drawDuoButton,
    &drawTuoYuanButton,
    &selectShapeButton,
    &zoomButton,
    &layereditButton,
    &modifyLineWidthButton,
    &settingsButton
};

Button* colourbuttons[16] = {
    &BlackButton,
    &RedButton,
    &GreenButton,
    &BlueButton,
    &MagentaButton,
    &BrownButton,
    &LightGrayButton,
    &DarkGrayButton,
    &LightBlueButton,
    &LightGreenButton,
    &LightCyanButton,
    &LightRedButton,
    &LightMagentaButton,
    &CyanButton,
    &YellowButton,
    &WhiteButton

};