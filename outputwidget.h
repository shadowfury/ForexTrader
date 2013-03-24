#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QTextEdit>
#include <QGridLayout>
#include <QScrollArea>

#include "bid.h"

class outputWidget : public QWidget
{
    Q_OBJECT
    QGridLayout *layout, *scrollLayout;

    QWidget *scrollWidget;
    QScrollArea *scroll;
    QImage* img;
    QLabel *picLabel;
    QTextEdit *bids;

    QVector<bid*> vector;
    int date_start,date_end;
public:
    explicit outputWidget(QWidget *parent = 0,int date_s=0,int date_e=0);
    
signals:
    
public slots:
    void setBidsVector(QVector<bid*> vec);
    void setDateStart(int date);
    void setDateEnd(int date);
    void drawGraph();
    void drawDeal(int num,QString txt);
    void printText(QString txt);
    void savePicture();
    
};

#endif // OUTPUTWIDGET_H
