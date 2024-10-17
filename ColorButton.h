// ColorButton.h
#pragma once

class CColorButton : public CButton
{
public:
    CColorButton();
    virtual ~CColorButton();

    void SetTextColor(COLORREF color);

protected:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
    COLORREF m_textColor;
};