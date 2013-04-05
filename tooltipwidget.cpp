#include "tooltipwidget.h"

tooltipWidget::tooltipWidget(QWidget *parent) :
    QWidget(parent,Qt::ToolTip)
{
    lbl=new QLabel(this);

}
void tooltipWidget::setText(QPoint pos){

    QString y_txt=QString::number((y_pix_size-pos.y())/y_diff+y_min_value,'f',4);
    int c=qRound((pos.x()-x_shift)/x_step)-1;
    QString x_txt=(vector[x_start+c]->date().toString("yyyy.MM.dd")+", "+vector[x_start+c]->time().toString("hh.mm"));
    lbl->setText(y_txt+", "+x_txt);
}

void tooltipWidget::Y_Axis_setDiff(double val){
    y_diff=val;
}
void tooltipWidget::Y_Axis_setMinVal(double val){
    y_min_value=val;
}
void tooltipWidget::Y_Axis_setPixSize(double val){
    y_pix_size=val;
}
// double diff=400/(max_value-min_value);
// 430-(i-min_value)*diff
//
// i=430/diff+min_value


// i-10 , 20
// int i=80; i<(date_end-date_start)*25+60;i+=25
// p.drawRect(i-10,430-(vector[date_start+c]
// c++;

// c=(x-60)/25
void tooltipWidget::setBidsVector(QVector<bid*> vec){
    vector=vec;
}
void tooltipWidget::X_Axis_setPixShift(double num){
    x_shift=num;
}
void tooltipWidget::X_Axis_setStepVal(double step){
    x_step=step;
}
void tooltipWidget::X_Axis_setStartIndice(int ind){
    x_start=ind;
}
