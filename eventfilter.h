#ifndef EVENTFILTER_H
#define EVENTFILTER_H

#include <QObject>
#include "QEvent"
#include "QWidget"
#include "QLabel"
#include "QDebug"
#include "tooltipwidget.h"
class eventfilter : public QObject
{
    Q_OBJECT
    tooltipWidget* tw;
protected:
     bool eventFilter(QObject *obj, QEvent *event);
public:
    explicit eventfilter(QObject *parent = 0);
    void setToolTipWidget(tooltipWidget* tool_widget);
signals:

};

#endif // EVENTFILTER_H
