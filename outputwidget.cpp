#include "outputwidget.h"

#include "bid.h"
#include <QDebug>
#include <QPainter>
outputWidget::outputWidget(QWidget *parent,int date_s,int date_e) :
    QWidget(parent)
{
    layout=new QGridLayout(this);

    scroll=new QScrollArea(this);

    scrollWidget= new QWidget(scroll);
    scrollLayout = new QGridLayout(scrollWidget);


    //scrollWidget->setLayout(scrollLayout);

    //scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    picLabel=new QLabel(scrollWidget);
    scrollLayout->addWidget(picLabel,0,0,1,1);

    date_start=date_s;
    date_end=date_e;

    if ((date_start==0) || (date_end==0)) img=new QImage(500,450,QImage::Format_RGB32);
    else img=new QImage((date_end-date_start)*25+80,600,QImage::Format_RGB32);
    img->fill(Qt::white);

    picLabel->setPixmap(QPixmap::fromImage(*img));

    scroll->setWidget(scrollWidget);
    bids=new QTextEdit(this);
    this->setLayout(layout);

    layout->addWidget(scroll,0,0,8,2);
    layout->addWidget(bids,8,0,1,2);

    //picLabel->installEventFilter();





    //date_start=0;
    //date_end=0;

}

void outputWidget::setBidsVector(QVector<bid*> vec){
    vector=vec;
}
void outputWidget::setDateStart(int date){
    date_start=date;

}

void outputWidget::setDateEnd(int date){
    date_end=date;

}

void outputWidget::drawGraph(){

    double min_value=999,max_value=0;
    for (int i=date_start;i<date_end;i++){
        double tmp_min=qMin(qMin(vector[i]->open(),vector[i]->close()),qMin(vector[i]->high(),vector[i]->low()));
        double tmp_max=qMax(qMax(vector[i]->open(),vector[i]->close()),qMax(vector[i]->high(),vector[i]->low()));
        if (min_value >= tmp_min) min_value=tmp_min;
        if (max_value <= tmp_max) max_value=tmp_max;
    }
    double diff=400/(max_value-min_value);
    QImage tmp_img=picLabel->pixmap()->toImage();
    QPainter p(&tmp_img);
    p.setPen(QPen(Qt::black));

    /*
    min - 430 px - 0%   - min_value - 1.2587
    ??? -                 value     - 1.2587+(1.333-1.2587)/n
    max - 45  px - 100% - max_value - 1.3333
    */

    //drawing  price Axis
    p.drawLine(60,30,60,430);
    p.drawLine(60,30,55,35);
    p.drawLine(60,30,65,35);
    for (double i=min_value; i<max_value;i=i+(max_value-min_value)/30){

        p.drawLine(57,430-(i-min_value)*diff,64,430-(i-min_value)*diff);
        p.drawText(QPoint(10,435-(i-min_value)*diff), QString::number(i,'f',4));
    }

    //drawing time Axis
    p.drawLine(60,430,(date_end-date_start)*25+60,430);
    p.drawLine((date_end-date_start)*25+60,430,(date_end-date_start)*25+55,425);
    p.drawLine((date_end-date_start)*25+60,430,(date_end-date_start)*25+55,435);

    int c=0;
    for (int i=80; i<(date_end-date_start)*25+60;i+=25){
       p.save();
       p.translate(QPoint(i-6,440));
       p.rotate(90);
       p.drawText(0,0,QString(vector[date_start+c]->date().toString("yyyy.MM.dd")+" "+vector[date_start+c]->time().toString("hh.mm")));
       p.restore();
       p.drawLine(i,427,i,434);

       c++;
    }
    c=0;
    // drawing candles
    // line low-open
    // line close - high
    // rect open - close
    // open >= close = black
    // 430-(i-min_value)*diff
    for (int i=80; i<(date_end-date_start)*25+60;i+=25){
        // top and bottom
        p.drawLine((double)i,430-(vector[date_start+c]->low()-min_value)*diff,(double)i,430-(vector[date_start+c]->open()-min_value)*diff);
        p.drawLine((double)i,430-(vector[date_start+c]->close()-min_value)*diff,(double)i,430-(vector[date_start+c]->high()-min_value)*diff);
        // candle body
        if (vector[date_start+c]->open()>=vector[date_start+c]->close()){
            p.setPen(QPen(Qt::red));
            p.drawRect(i-10,430-(vector[date_start+c]->open()-min_value)*diff ,20,qAbs(430-(vector[date_start+c]->open()-min_value)*diff-(430-(vector[date_start+c]->close()-min_value)*diff)));
            p.fillRect(i-10,430-(vector[date_start+c]->open()-min_value)*diff,20,qAbs(430-(vector[date_start+c]->open()-min_value)*diff-(430-(vector[date_start+c]->close()-min_value)*diff)),QColor(255,0,0));
        }
        else{
            p.setPen(QPen(Qt::blue));
            p.drawRect(i-10,430-(vector[date_start+c]->close()-min_value)*diff,20,qAbs(430-(vector[date_start+c]->open()-min_value)*diff-(430-(vector[date_start+c]->close()-min_value)*diff)));
        }
        //qDebug()<<vector[date_start+c]->date().toString("yyyy.MM.dd")<<vector[date_start+c]->time().toString("hh.mm")<<vector[date_start+c]->low()<<vector[date_start+c]->open()<<vector[date_start+c]->close()<<vector[date_start+c]->high();
        c++;
        p.setPen(QPen(Qt::black));
    }
    p.end();
    picLabel->setPixmap(QPixmap::fromImage(tmp_img));



    // adding tooltip widget
    eventfilter *hoverFilter = new eventfilter(this);

    tooltipWidget *tw= new tooltipWidget();
    tw->Y_Axis_setPixSize(430);
    tw->Y_Axis_setMinVal(min_value);
    tw->Y_Axis_setDiff(diff);
    tw->X_Axis_setPixShift(60);
    tw->X_Axis_setStartIndice(date_start);
    tw->X_Axis_setStepVal(25);
    tw->setBidsVector(vector);
    tw->hide();
    hoverFilter->setToolTipWidget(tw);

    picLabel->setMouseTracking(true);
    picLabel->installEventFilter(hoverFilter);
}
void outputWidget::drawDeal(int num,QString txt, QColor color){
    QImage tmp_img=picLabel->pixmap()->toImage();
    QPainter p(&tmp_img);
    p.setPen(QPen(color));
    p.drawText(45+(num-date_start)*25-5,15,txt);

    p.setBrush(QBrush(color));
    p.drawEllipse(80+(num-date_start)*25-5,20,10,10);

    p.end();
    picLabel->setPixmap(QPixmap::fromImage(tmp_img));


}

void outputWidget::repaintBlankImage(){
    QImage *tmp_img=new QImage((date_end-date_start)*25+80,600,QImage::Format_RGB32);
    tmp_img->fill(Qt::white);
    picLabel->setPixmap(QPixmap::fromImage(*tmp_img));
}

void outputWidget::printText(QString txt){
    bids->append(txt);
}
void outputWidget::savePicture(){
    picLabel->pixmap()->save(QDate::currentDate().toString("dd.MM.yyyy")+"_"+QTime::currentTime().toString("HH.mm")+".jpg");
}
