//
// Created by iXasthur on 04.10.2020.
//

#ifndef RESIZABLE_TABLE_TABLEDRAWER_H
#define RESIZABLE_TABLE_TABLEDRAWER_H

#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <vector>
#include <string>
#include "TableCell.h"

class TableDrawer {
private:
    std::vector<TableCell>
    calculateCells(Gdiplus::Graphics *graphics, const Gdiplus::Font &font, Gdiplus::RectF drawRect) {
        Gdiplus::REAL cellWidth = drawRect.Width / (Gdiplus::REAL) columnCount;

        std::vector<TableCell> cells = {};

        for (const std::wstring &string: strings) {
            TableCell cell = TableCell(graphics, string, font, cellWidth, drawRect.Height);
            cells.emplace_back(cell);
        }

        int emptyCellsToAdd = abs((int) strings.size() % columnCount - columnCount) % columnCount;
        for (int i = 0; i < emptyCellsToAdd; ++i) {
            TableCell cell = TableCell(graphics, L"", font, cellWidth, drawRect.Height);
            cells.emplace_back(cell);
        }

        int rowCount = (int) cells.size() / columnCount;
        Gdiplus::REAL rowHeights[rowCount];
        for (int i = 0; i < rowCount; ++i) {
            Gdiplus::REAL maxHeight = 0;
            for (int j = 0; j < columnCount; ++j) {
                Gdiplus::REAL height = cells[i * columnCount + j].bounds.Height;
                if (height > maxHeight) {
                    maxHeight = height;
                }
            }
            rowHeights[i] = maxHeight;

            for (int j = 0; j < columnCount; ++j) {
                cells[i * columnCount + j].bounds.Height = rowHeights[i];
            }

            Gdiplus::REAL offsetY = 0;
            for (int q = 0; q < i; ++q) {
                offsetY += rowHeights[q];
            }

            for (int j = 0; j < columnCount; ++j) {
                cells[i * columnCount + j].bounds.X = cellWidth * (Gdiplus::REAL) j + drawRect.X;
                cells[i * columnCount + j].bounds.Y = offsetY + drawRect.Y;
            }
        }

        return cells;
    }

    void drawCells(Gdiplus::Graphics *graphics, const std::vector<TableCell> &cells, const Gdiplus::Font &font) {
        for (const TableCell &cell: cells) {
            Gdiplus::Pen pen = Gdiplus::Pen(Gdiplus::Color::Black, 2);
            Gdiplus::SolidBrush solidBrush(Gdiplus::Color::Black);
            graphics->DrawString(cell.string.c_str(), -1, &font, cell.bounds, nullptr, &solidBrush);
            graphics->DrawRectangle(&pen, cell.bounds);
        }
    }

public:
    int columnCount = 0;
    std::vector<std::wstring> strings = {};

    explicit TableDrawer(int columnCount) noexcept {
        this->columnCount = columnCount;
    }

    void draw(Gdiplus::Graphics *graphics, Gdiplus::RectF drawRect) {
        if (columnCount > 0 && !strings.empty()) {
            const Gdiplus::FontFamily fontFamily = Gdiplus::FontFamily(L"Arial");
            const Gdiplus::REAL fontSize = 12;
            const Gdiplus::FontStyle fontStyle = Gdiplus::FontStyleBold;
            const Gdiplus::Unit fontUnit = Gdiplus::UnitPoint;
            const Gdiplus::Font font = Gdiplus::Font(&fontFamily, fontSize, fontStyle, fontUnit);

            drawCells(graphics, calculateCells(graphics, font, drawRect), font);
        }
    }

};


#endif //RESIZABLE_TABLE_TABLEDRAWER_H
