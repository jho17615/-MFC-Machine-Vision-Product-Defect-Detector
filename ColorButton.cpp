// ColorButton.cpp
#include "pch.h"
#include "ColorButton.h"

CColorButton::CColorButton()
    : m_textColor(RGB(0, 0, 0))
{
}

CColorButton::~CColorButton()
{
}

void CColorButton::SetTextColor(COLORREF color)
{
    m_textColor = color;
    Invalidate();
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    CDC dc;
    dc.Attach(lpDrawItemStruct->hDC);

    RECT rect = lpDrawItemStruct->rcItem;
    dc.FillSolidRect(&rect, GetSysColor(COLOR_BTNFACE));

    if (lpDrawItemStruct->itemState & ODS_SELECTED)
    {
        dc.DrawEdge(&rect, EDGE_SUNKEN, BF_RECT);
    }
    else
    {
        dc.DrawEdge(&rect, EDGE_RAISED, BF_RECT);
    }

    CString text;
    GetWindowText(text);

    dc.SetTextColor(m_textColor);
    dc.SetBkMode(TRANSPARENT);
    dc.DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    if (lpDrawItemStruct->itemState & ODS_FOCUS)
    {
        RECT focusRect = rect;
        focusRect.left += 4;
        focusRect.top += 4;
        focusRect.right -= 4;
        focusRect.bottom -= 4;
        dc.DrawFocusRect(&focusRect);
    }

    dc.Detach();
}