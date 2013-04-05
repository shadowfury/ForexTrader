#include "eventfilter.h"

eventfilter::eventfilter(QObject *parent) :
    QObject(parent)
{

}
bool eventfilter::eventFilter(QObject *obj, QEvent *event)
 {
    if (event->type() == QEvent::MouseMove) {
        QLabel *tmp=(QLabel*)obj;
        QPoint pos=tmp->mapFromGlobal(tmp->cursor().pos());
        tw->move(tmp->cursor().pos().x()+15,tmp->cursor().pos().y()+15);


        tw->setText(pos);

        tw->show();
        //delete tmp;

    }
    else{
        tw->hide();
    }


    return QObject::eventFilter(obj, event);
 }
void eventfilter::setToolTipWidget(tooltipWidget* tool_widget){
    tw=tool_widget;
}
