#ifndef QDOUBLESCROLLBAR_H
#define QDOUBLESCROLLBAR_H

#include <QDate>
#include <QDateTime>
#include <QScrollBar>
#include <cmath>

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
public slots:
    void requestCustomValue(int val);
private slots:

private:
    int numbAP;
    double timedt;
    double decimal;
signals:
    void valueChangedCustom(double);
};

#endif // QDOUBLESCROLLBAR_H
