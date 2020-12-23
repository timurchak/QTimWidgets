#include "qdoublescrollbar.h"

QDoubleScrollBar::QDoubleScrollBar(QWidget* par)
    : QScrollBar(par)
    , numbAP(0)
    , timedt(0)
    , decimal(10)
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

    double newvalue = (timedt + static_cast<double>(value()) / decimal);
    return newvalue;
}

void QDoubleScrollBar::setCustomValue(double val)
{
    int newvalue = static_cast<int>(std::round((val - timedt) * decimal));
    if(value() != newvalue) {
        setValue(newvalue);
    }
}

void QDoubleScrollBar::setCustomValueWithoutSignal(double val)
{
    QSignalBlocker block(this);
    int newvalue = static_cast<int>(std::round((val - timedt) * decimal));
    if(value() != newvalue) {
        setValue(newvalue);
    }
    block.unblock();
}

void QDoubleScrollBar::setCustomMinimum(double val)
{
    double newvalue = ((val - timedt) * decimal);
    setMinimum(static_cast<int>(floor(newvalue)));
}

void QDoubleScrollBar::setCustomMaximum(double val)
{
    double newvalue = (val - timedt) * decimal;
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
    double newvalue = (timedt + static_cast<double>(val / decimal));
    emit valueChangedCustom(newvalue);
}
