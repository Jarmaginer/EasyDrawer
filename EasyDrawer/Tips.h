#pragma once
#include"Shape.h"
#include "tools.h"

class Tips {
public:
    void updateHints(const POINT& mousePos, const std::string& mode, std::string tips);
    void displayHints() const;
    void updatePt(POINT pt);

private:
    POINT mousePos;
    std::string mode;
    std::string tips;
};
