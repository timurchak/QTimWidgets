#ifndef QDYNAMICGRIDLAYOUT_H
#define QDYNAMICGRIDLAYOUT_H

#include <QObject>
#include <QGridLayout>
#include <QMap>
#include <QWidget>
#include <QDebug>

class QDynamicGridLayout : public QGridLayout
{   
    Q_OBJECT
public:
    enum class ModeGrid {FixedColumn = 0, FixedWidth, FixedHeight};
    QDynamicGridLayout(ModeGrid _mode = ModeGrid::FixedColumn, QWidget* parent = nullptr);
    bool add(QWidget* w, int r = -1, int c = -1);
    bool add(QLayoutItem* item, int r = -1, int c = -1);
    bool add(QLayout* lay, int r = -1, int c = -1);
    void setColumn(int column);
    void setWidth(int width);
    void setHeight(int height);
private:
    void editIndexes();
    void editWidth();
    void editHeight();
    void editPos();
    struct DynamicItem {
        QWidget* w = nullptr;
        QLayoutItem* li = nullptr;
        QLayout* l = nullptr;
        QSize hint = QSize(0,0);
        int r = -1;
        int c = -1;;
    };
private:        
    ModeGrid mode;
    QMap<int, QMap<int, DynamicItem>> grid;
    int maxWidth;
    int maxHeight;
    int maxColumn;
    int currentRow;
    int currentColumn;
};

#endif // QDYNAMICGRIDLAYOUT_H
