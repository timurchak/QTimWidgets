#include "qdynamicgridlayout.h"

QDynamicGridLayout::QDynamicGridLayout(ModeGrid _mode, QWidget* parent)
    : QGridLayout(parent)
    , mode(_mode)
    , grid()
    , maxColumn(0)
    , currentRow(0)
    , currentColumn(0)
{
}

bool QDynamicGridLayout::add(QWidget* w, int r, int c)
{
    if (r < 0 || c < 0) {
        editPos();
        grid[currentRow][currentColumn].w = w;
        grid[currentRow][currentColumn].hint = w->sizeHint();
        addWidget(w, currentRow, currentColumn);
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        //editPos();
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addWidget(w, r, c);        
        grid[currentRow][currentColumn].w = w;
        grid[currentRow][currentColumn].hint = w->sizeHint();
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        return true;
    }
}

bool QDynamicGridLayout::add(QLayoutItem* item, int r, int c)
{
    if (r < 0 || c < 0) {
        editPos();
        addItem(item, currentRow, currentColumn);

        grid[currentRow][currentColumn].li = item;
        grid[currentRow][currentColumn].hint = item->sizeHint();
        addItem(item, currentRow, currentColumn);
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        //editPos();
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addItem(item, r, c);        
        grid[currentRow][currentColumn].li = item;
        grid[currentRow][currentColumn].hint = item->sizeHint();
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        return true;
    }
}

bool QDynamicGridLayout::add(QLayout* lay, int r, int c)
{
    if (r < 0 || c < 0) {
        editPos();
        addLayout(lay, currentRow, currentColumn);        
        grid[currentRow][currentColumn].l = lay;
        grid[currentRow][currentColumn].hint = lay->sizeHint();
        addLayout(lay, currentRow, currentColumn);
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        return true;
    } else {
        if (itemAtPosition(r, c) == nullptr) {
            return false;
        }
        addLayout(lay, r, c);        
        grid[currentRow][currentColumn].l = lay;
        grid[currentRow][currentColumn].hint = lay->sizeHint();
        grid[currentRow][currentColumn].c = currentColumn;
        grid[currentRow][currentColumn].r = currentRow;
        return true;
    }
}

void QDynamicGridLayout::setColumn(int column)
{
    mode = ModeGrid::FixedColumn;
    maxColumn = column;
    int i = 0;
    grid.clear();
    QList<QLayoutItem*> list;
    while (itemAt(i) != nullptr) {
        list.push_back(itemAt(i));
        i++;
    }
    currentRow = 0;
    currentColumn = 0;
    auto it = list.begin();
    while (it != list.end()) {
        add(*it);
        ++it;
    }
}

void QDynamicGridLayout::setWidth(int width)
{
    mode = ModeGrid::FixedWidth;
    maxWidth = width;
    int i = 0;
    grid.clear();
    QList<QLayoutItem*> list;
    while (itemAt(i) != nullptr) {
        list.push_back(itemAt(i));
        i++;
    }
    currentRow = 0;
    currentColumn = 0;
    auto it = list.begin();
    while (it != list.end()) {
        add(*it);
        ++it;
    }
}

void QDynamicGridLayout::setHeight(int height)
{
    mode = ModeGrid::FixedHeight;
    maxHeight = height;
    int i = 0;
    grid.clear();
    QList<QLayoutItem*> list;
    while (itemAt(i) != nullptr) {
        list.push_back(itemAt(i));
        i++;
    }

    currentRow = 0;
    currentColumn = 0;
    auto it = list.begin();
    while (it != list.end()) {
        add(*it);
        ++it;
    }
}

void QDynamicGridLayout::editIndexes()
{
    // currentColumn++;
    if (currentColumn == maxColumn) {
        currentRow++;
        currentColumn = 0;
    }
}

void QDynamicGridLayout::editWidth()
{
    int sum = 0;
    for (auto& item : grid[currentRow]) {
        sum += item.hint.width();
    }
    if (sum > maxWidth) {
        currentRow++;
        currentColumn = 0;
    }
    qDebug() << "sum = " << sum << "maxW" << maxWidth;
    qDebug() << "cr = " << currentRow << "cc = " << currentColumn;
    qDebug() << "sizeRow = " << grid.size();
}

void QDynamicGridLayout::editHeight(){

    int sum = 0;
    for (auto& item : grid[currentRow]) {
        sum += item.hint.height();
    }
    if (sum > maxHeight) {
        currentRow++;
        currentColumn = 0;
    }
}

void QDynamicGridLayout::editPos()
{
    switch (mode) {
    case ModeGrid::FixedColumn:
        editIndexes();
        break;
    case ModeGrid::FixedHeight:
        editHeight();
        break;
    case ModeGrid::FixedWidth:
        editWidth();
        break;
    }
    currentColumn++;
}
