#include "Button.h"
Button drawCircleButton(200, 0, 300, 50, _T("圆"));

Button drawRectButton(300, 0, 400, 50, _T("矩形"));
Button drawZhexianButton(400, 0, 500, 50, _T("折线"));
Button drawDuoButton(500, 0, 600, 50, _T("多边形"));
Button drawTuoYuanButton(600, 0, 700, 50, _T("椭圆"));
Button selectShapeButton(700, 0, 800, 50, _T("选择"));
Button zoomButton(800, 0, 900, 50, _T("缩放"));
Button fillButton(900, 0, 1000, 50, _T("填充"));
Button duplicateButton(1000, 0, 1100, 50, _T("复制"));
Button deleteButton(1100, 0, 1200, 50, _T("删除"));
Button changeLineStyleButton(1200, 0, 1300, 50, _T("改变线型"));
Button modifyLineWidthButton(1300, 0, 1400, 50, _T("修改线宽"));
Button insertImageButton(1400, 0, 1500, 50, _T("置入图片"));
Button insertButton(1400, 50, 1500, 100, _T("置入图形"));

Button layereditButton(1400, 100, 1500, 150, _T("图层编辑"));
Button clearButton(1400, 150, 1500, 200, L"清空画布");
Button saveButton(1400, 200, 1500, 250, _T("保存工程"));
Button loadButton(1400, 250, 1500, 300, _T("读取工程"));
//Button insertButton(1400, 200, 1500, 250, _T("置入对象"));
Button settingsButton(1400, 300, 1500, 350, _T("设置"));

Button copyButton(-100, -100, -25, -25, _T("拷贝"));

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


Button themeButton(888, 350, 948, 380, _T("切换主题"));
Button openTips(888, 380, 948, 410, _T("开启提示"));
Button refreshMouseMove(888, 410, 948, 440, _T("鼠标移动刷新"));
Button openDoubleClick(888, 440, 948, 470, _T("双击"));
Button openBatchDraw(888, 470, 948, 500, _T("双缓冲区"));





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

    outtextxy(705, 252, stringToLPCWSTR("设置菜单"));

    outtextxy(532, 352, stringToLPCWSTR("设置画板主题颜色"));
    outtextxy(892, 352, stringToLPCWSTR((THEME == 0) ? "黑色" : "白色"));

    outtextxy(532, 382, stringToLPCWSTR("提示系统"));
    outtextxy(892, 382, stringToLPCWSTR(OPEN_TIPS ? "开启" : "关闭"));

    outtextxy(532, 412, stringToLPCWSTR(("鼠标移动时刷新画布")));
    outtextxy(892, 412, stringToLPCWSTR(FRESH_WHILE_MOVEMOUSE ? "开启" : "关闭"));

    outtextxy(532, 442, stringToLPCWSTR(("捕获鼠标双击事件")));
    outtextxy(892, 442, stringToLPCWSTR(OPEN_DOUBLE_CLICK ? "开启" : "关闭"));

    outtextxy(532, 472, stringToLPCWSTR(("启用双缓冲区渲染优化")));
    outtextxy(892, 472, stringToLPCWSTR(OPEN_BATCH_DRAW ? "开启" : "关闭"));



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