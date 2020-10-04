//
// Created by iXasthur on 04.10.2020.
//

#ifndef RESIZABLE_TABLE_TABLECELL_H
#define RESIZABLE_TABLE_TABLECELL_H

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <utility>

class TableCell {
public:
    std::wstring string;
    Gdiplus::RectF bounds;

    TableCell(Gdiplus::Graphics *graphics, const std::wstring &str, const Gdiplus::Font &font, Gdiplus::REAL cellWidth, Gdiplus::REAL maxHeight){
        this->string = str;

        bounds = Gdiplus::RectF{0, 0, cellWidth, maxHeight};

        const wchar_t *text = string.c_str();
        Gdiplus::SolidBrush solidBrush(Gdiplus::Color(255, 0, 0, 0));
        graphics->MeasureString(text, -1, &font, bounds, &bounds);

        bounds = Gdiplus::RectF{0, 0, cellWidth, bounds.Height};
    }
};


#endif //RESIZABLE_TABLE_TABLECELL_H
