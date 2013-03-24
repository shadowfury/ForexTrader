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

    layout->addWidget(scroll,0,0,1,2);
    layout->addWidget(bids,1,0,1,2);


    date_start=0;
    date_end=0;

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

    QPainter p(img);
    p.setPen(QPen(Qt::black));

    //drawing  price Axis
    p.drawLine(40,40,40,430);
    p.drawLine(40,40,35,45);
    p.drawLine(40,40,45,45);
    for (double i=2; i>0;i=i-0.10){
        p.drawLine(37,i*200+30,44,i*200+30);
        p.drawText(QPoint(10,i*200.0+35), QString::number(2-i,'f',1));
    }

    //drawing time Axis
    p.drawLine(40,430,(date_end-date_start)*25+40,430);
    p.drawLine((date_end-date_start)*25+40,430,(date_end-date_start)*25+35,425);
    p.drawLine((date_end-date_start)*25+40,430,(date_end-date_start)*25+35,435);

    int c=0;
    for (int i=60; i<(date_end-date_start)*25+40;i+=25){
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
    for (int i=60; i<(date_end-date_start)*25+40;i+=25){
        // top and bottom
        p.drawLine((double)i,vector[date_start+c]->low()*200.0+30.0,(double)i,vector[date_start+c]->open()*200.0+30.0);
        p.drawLine((double)i,vector[date_start+c]->close()*200.0+30.0,(double)i,vector[date_start+c]->high()*200.0+30.0);
        // candle body
        if (vector[date_start+c]->open()>=vector[date_start+c]->close()){
            p.drawRect(i-10,vector[date_start+c]->close()*200.0+30.0,20,qAbs(vector[date_start+c]->open()-vector[date_start+c]->close())*200.0);
            p.fillRect(i-10,vector[date_start+c]->close()*200.0+30.0,20,qAbs(vector[date_start+c]->open()-vector[date_start+c]->close())*200.0,Qt::SolidPattern);
        }
        else p.drawRect(i-10,vector[date_start+c]->close()*200.0+30.0,20,qAbs(vector[date_start+c]->open()-vector[date_start+c]->close())*200.0);
        c++;
    }




    picLabel->setPixmap(QPixmap::fromImage(*img));
}
void outputWidget::drawDeal(int num,QString txt){

}


void outputWidget::printText(QString txt){
    bids->append(txt);
}
void outputWidget::savePicture(){
    picLabel->pixmap()->save(QDate::currentDate().toString("dd.MM.yyyy")+"_"+QTime::currentTime().toString("HH.mm")+".jpg");
}
