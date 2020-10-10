#ifndef TPOPUP_H
#define TPOPUP_H

#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>
#include <QWidget>
#include <QWindow>
#include <QPushButton>
#include <thread>
#include <utility>

#include <iostream>
#include <sstream>
#include <string>

#include <plnlog/plnlog.h>
class TPopUp : public QWidget {
    Q_OBJECT
public:
    TPopUp(QWidget* _par, bool _autoHide = true, int _interval = 3, int _id = -1, int _typeID = -1);
    ~TPopUp();
    TPopUp() = delete;
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)

    void setPopupOpacity(float opacity);
    float getPopupOpacity() const;

    int getTypeID() const;

protected:
    void paintEvent(QPaintEvent* event);

public slots:
    void setPopupText(const QString& text, const QString& title = "");
    void show();
    void setPosOffset(int y);
    void setLivePosOffset(int y);
    void offsetForNewPosParent(int dx, int dy);
    void offsetForResizeParent(int dx);
    void setFixedPopUp(int w = -1);

private slots:
    void hideAnimation();
    void hide();
    void hideWithButton();

signals:
    void hidePopUp(int);
private:
    QWidget* par;
    QLabel* labelText;
    QLabel* labelTitle;
    QPushButton* btnClose;
    QVBoxLayout* layout;
    QPropertyAnimation* animation;
    float popupOpacity;
    QTimer* timer;
    int posOffset;
    int id;
    bool autoHide;
    int interval;
    int fixedWith;
    int typeID;
};

#endif // TPOPUP_H
