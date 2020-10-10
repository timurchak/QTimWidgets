#include "qdoublescrollbar.h"

QDoubleScrollBar::QDoubleScrollBar(QWidget* par)
    : QScrollBar(par)
    , numbAP(0)
    , timedt(0)
{
    int year = QDate::currentDate().year();
    QDateTime dt;
    dt.setDate(QDate(year, 1, 1));
    timedt = static_cast<double>(dt.toTime_t());
    connect(this, &QDoubleScrollBar::valueChanged, this, &QDoubleScrollBar::requestCustomValue);
}

int QDoubleScrollBar::getNumbAP() const { return numbAP; }

double QDoubleScrollBar::getCustomValue() const
{

    double newvalue = (timedt + static_cast<double>(value()) / 10.0);
    return newvalue;
}

void QDoubleScrollBar::setCustomValue(double val)
{
    int newvalue = static_cast<int>((val - timedt) * 10);
    if(value() != newvalue) {
        setValue(newvalue);
    }
}

void QDoubleScrollBar::setCustomMinimum(double val)
{
    double newvalue = ((val - timedt) * 10);
    setMinimum(static_cast<int>(floor(newvalue)));
}

void QDoubleScrollBar::setCustomMaximum(double val)
{
    double newvalue = (val - timedt) * 10;
    setMaximum(static_cast<int>(ceil(newvalue)));
}

void QDoubleScrollBar::setCustomRange(double min, double max)
{
    setCustomMinimum(min);
    setCustomMaximum(max);
}

void QDoubleScrollBar::setNumbAP(int value) { numbAP = value; }

double QDoubleScrollBar::getTimedt() const { return timedt; }

void QDoubleScrollBar::requestCustomValue(int val)
{
    double newvalue = (timedt + static_cast<double>(val / 10.0));
    emit valueChangedCustom(newvalue);
}
