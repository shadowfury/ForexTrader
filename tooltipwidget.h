#ifndef TOOLTIPWIDGET_H
#define TOOLTIPWIDGET_H

#include <QWidget>
#include "QLabel"
#include "bid.h"
class tooltipWidget : public QWidget
{
    Q_OBJECT
    QLabel* lbl;
    double y_diff,y_min_value,y_pix_size,x_shift,x_step,x_start;
    QVector<bid*> vector;
public:
    explicit tooltipWidget(QWidget *parent = 0);
    
signals:
    
public slots:
    void setText(QPoint pos);
    void Y_Axis_setDiff(double val);
    void Y_Axis_setMinVal(double val);
    void Y_Axis_setPixSize(double val);
    void setBidsVector(QVector<bid*> vec);
    void X_Axis_setPixShift(double num);
    void X_Axis_setStepVal(double step);
    void X_Axis_setStartIndice(int ind);
};

#endif // TOOLTIPWIDGET_H
