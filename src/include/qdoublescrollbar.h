#ifndef QDOUBLESCROLLBAR_H
#define QDOUBLESCROLLBAR_H

#include <QDate>
#include <QDateTime>
#include <QScrollBar>
#include <cmath>
#include <QDebug>

class QDoubleScrollBar : public QScrollBar {
    Q_OBJECT
public:
    QDoubleScrollBar(QWidget* par = nullptr);
    int getNumbAP() const;
    double getCustomValue() const;
    void setCustomValue(double val);
    void setCustomValueWithoutSignal(double val);
    void setCustomMinimum(double val);
    void setCustomMaximum(double val);
    void setCustomRange(double min, double max);

    void setNumbAP(int value);
    double getTimedt() const;
    bool getPress() const;

    void setPress(bool value);

public slots:
    void requestCustomValue(int val);
    void requestSliderReleased();
    void requestSliderPressed();
private slots:

private:
    int numbAP;
    double timedt;
    double decimal;
    bool press = false;
signals:
    void valueChangedCustom(double);
    void sliderReleasedCustom(double);
    void changePress(bool);
};

#endif // QDOUBLESCROLLBAR_H
