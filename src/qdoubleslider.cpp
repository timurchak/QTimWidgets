#include "qdoubleslider.h"

QDoubleSlider::QDoubleSlider(QWidget *par)
    : QSlider(par)
    , val(0)
{
    connect(this, &QDoubleSlider::valueChanged, this, &QDoubleSlider::notifyValueChanged);
}

void QDoubleSlider::setDoubleVal(double val)
{
    int nval = qRound(val * 10);
    setValue(nval);
}

void QDoubleSlider::notifyValueChanged(int val)
{
    emit doubleValueChange(static_cast<double>(val / 10.0));
}

void QDoubleSlider::setMinimumDouble(int val)
{
    setMinimum(val * 10);
}

void QDoubleSlider::setMaximumDouble(int val)
{
    setMaximum(val * 10);
}

double QDoubleSlider::getVal() const
{
    return value() / 10.0;
}
