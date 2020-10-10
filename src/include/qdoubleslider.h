#ifndef QDOUBLESLIDER_H
#define QDOUBLESLIDER_H

#include <QObject>
#include <QSlider>

class QDoubleSlider : public QSlider
{
    Q_OBJECT
public:
    QDoubleSlider(QWidget* par = nullptr);
public slots:
    void setDoubleVal(double val);
    void notifyValueChanged(int val);
    void setMinimumDouble(int val);
    void setMaximumDouble(int val);
    double getVal() const;
private:
    double val;
signals:
    void doubleValueChange(double);

};

#endif // QDOUBLESLIDER_H
