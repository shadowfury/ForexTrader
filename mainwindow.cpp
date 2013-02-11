#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

void funk(char *,char);

float mp (float*,float*,int);
float sma(float*,float*,int,int);
float ao(float*,float*,int);

mainwindow::mainwindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    ui->dateEdit->setAcceptDrops(true);
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDisplayFormat("yyyy.MM.dd");
    /*bool flag=true;
    int koma[6],k=0,i1,i2,i3,i4,i,j,c,massize=155,dot=0,coma=0,twodot=0,number=0,enter=0,lenght=0;
    int year_lo,month_lo,day_lo,hour_lo,year_to,month_to,day_to,hour_to,year_lc,month_lc,day_lc,hour_lc,year_tc,month_tc,day_tc,hour_tc;
    int open_l,close_l,open_t,close_t;
    char temp[10],str[200];
    char char1[1],char2[1],dot1=46,coma1=44,twodot1=58,enter1=10,y_n;
    int* mas_year,*mas_month,*mas_day,*mas_hour;
    float* mas_open,*mas_high,*mas_low,*mas_close;
    float** mas_ao;
    float a1=1,a2=1,a3=1,a4=1,profit,profit_max=0,w1_max,w2_max,w3_max,w4_max,d=0;
    //граници обучения и торговли
    //year_lo=2010;month_lo=1;day_lo=1;hour_lo=0;year_lc=2010;month_lc=3;day_lc=1;hour_lc=0;
    //year_to=2010;month_to=3;day_to=1;hour_to=0;year_tc=2010;month_tc=4;day_tc=30;hour_tc=0;

    printf("Input training start date\n");
    printf("Input year: ");
    scanf("%d",&year_lo);
    printf("Input month: ");
    scanf("%d",&month_lo);
    printf("Input day: ");
    scanf("%d",&day_lo);
    printf("Input hour: ");
    scanf("%d",&hour_lo);
    printf("Input training end date\n");
    printf("Input year: ");
    scanf("%d",&year_lc);
    printf("Input month: ");
    scanf("%d",&month_lc);
    printf("Input day: ");
    scanf("%d",&day_lc);
    printf("Input hour: ");
    scanf("%d",&hour_lc);
     while (flag){
            printf("Do you want set trading parameters now? (Y/N) ");
            scanf("%s",&y_n);
            if ((y_n=='y')||(y_n=='Y')||(y_n=='n')||(y_n=='N')) flag=false;
      }
      flag=true;
  if ((y_n=='y')||(y_n=='Y')){
    printf("Input trading start date\n");
    printf("Input year: ");
    scanf("%d",&year_to);
    printf("Input month: ");
    scanf("%d",&month_to);
    printf("Input day: ");
    scanf("%d",&day_to);
    printf("Input hour: ");
    scanf("%d",&hour_to);
    printf("Input trading end date\n");
    printf("Input year: ");
    scanf("%d",&year_tc);
    printf("Input month: ");
    scanf("%d",&month_tc);
    printf("Input day: ");
    scanf("%d",&day_tc);
    printf("Input hour: ");
    scanf("%d",&hour_tc);
  }//
    FILE *test=fopen("EURUSD60.csv","r");
    //считывание с файла


    i=0;
    number=0;
    while (fscanf(test, "%s", str) != EOF){
          number++;
          //printf("%s\n",str);
    }
    fclose(test);
    printf("n=%d\n",number);
    massize=number;
    char** str_file=(char**)calloc(massize,sizeof(char*));
    for(i=0;i<massize;i++) str_file[i]=(char*)calloc(100,sizeof(char));
    number=0;
    test=fopen("EURUSD60.csv","r");
    for(i=0;i<massize;i++) fgets(str_file[i],100,test);

    //for (i=0;i<massize;i++)printf("%s",str_file[i]);
    //генерация  динамических массивов
      mas_year=(int*)calloc(massize,sizeof(int));
      mas_month=(int*)calloc(massize,sizeof(int));
      mas_day=(int*)calloc(massize,sizeof(int));
      mas_hour=(int*)calloc(massize,sizeof(int));
      mas_low=(float*)calloc(massize,sizeof(float));
      mas_high=(float*)calloc(massize,sizeof(float));
      mas_open=(float*)calloc(massize,sizeof(float));
      mas_close=(float*)calloc(massize,sizeof(float));
      mas_ao=(float**)calloc(massize,sizeof(float*));
      for(i=0;i<massize;i++){
          mas_ao[i]=(float*)calloc(4,sizeof(float));
      }
    //

    //Перевод из чаров в инты и флоат
    for (i=0;i<massize;i++){
        mas_year[i]=0;
        mas_month[i]=0;
        mas_day[i]=0;
        mas_hour[i]=0;
        mas_low[i]=0;
        mas_high[i]=0;
        mas_open[i]=0;
        mas_close[i]=0;
    }

      for (i=0;i<massize;i++){
        coma=0;
        for (j=0;j<4;j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_year[i]=atoi(temp);

        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=5;j<7;j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_month[i]=atoi(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=8;j<10;j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_day[i]=atoi(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=11;j<13;j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_hour[i]=atoi(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=16;j<100;j++) if (str_file[i][j]==coma1) koma[coma++]=j;
        for (j=koma[0]+1;j<koma[1];j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_open[i]=atof(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=koma[1]+1;j<koma[2];j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_high[i]=atof(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=koma[2]+1;j<koma[3];j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_low[i]=atof(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
        for (j=koma[3]+1;j<koma[4];j++){
            char1[0]=str_file[i][j];
            funk(temp,char1[0]);
            mas_close[i]=atof(temp);
        }
        for(k=0;k<10;k++)temp[k]='\0';
    }
    //

    //for (i=0;i<massize;i++) printf("%d %d %d %d %d %f %f %f %f\n",i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_open[i],mas_high[i],mas_low[i],mas_close[i]);
    fclose(test);
     printf("L open %d %d %d %d\n",year_lo,month_lo,day_lo,hour_lo);
     printf("L close %d %d %d %d\n",year_lc,month_lc,day_lc,hour_lc);
     printf("T open %d %d %d %d\n",year_to,month_to,day_to,hour_to);
     printf("T close %d %d %d %d\n",year_tc,month_tc,day_tc,hour_tc);
    //Задаем граници обучения и торговли
     //Открытие обучения
     flag=true; c=0;
     for (i=0;i<massize;i++){
         if ((year_lo==mas_year[i])&&(month_lo==mas_month[i])&&(day_lo==mas_day[i])&&(hour_lo==mas_hour[i])){
            open_l=i;
            flag=false;
         }

     }
     for (c=-4;c<4;c++){
         if (flag==true){
           for (i=0;i<massize;i++){
               if ((year_lo==mas_year[i])&&(month_lo==mas_month[i])&&(day_lo==mas_day[i]+c)&&(hour_lo==mas_hour[i])){
                  open_l=i;
                  day_lo=mas_day[i]+c;
                  flag=false;
               }

           }
         }
     }
     //Открытие трейда
     for (i=0;i<massize;i++){
         if ((year_to==mas_year[i])&&(month_to==mas_month[i])&&(day_to==mas_day[i])&&(hour_to==mas_hour[i])){
            open_t=i;
            flag=false;
         }

     }
     for (c=-4;c<4;c++){
         if (flag==true){
           for (i=0;i<massize;i++){
               if ((year_to==mas_year[i])&&(month_to==mas_month[i])&&(day_to==mas_day[i]+c)&&(hour_to==mas_hour[i])){
                  open_t=i;
                  day_to=mas_day[i]+c;
                  flag=false;
               }

           }
         }
     }
     //Закрытие обучения
     flag=true; c=0;
     for (i=0;i<massize;i++){
         if ((year_lc==mas_year[i])&&(month_lc==mas_month[i])&&(day_lc==mas_day[i])&&(hour_lc==mas_hour[i])){
            close_l=i;
            flag=false;
         }

     }
     for (c=-4;c<4;c++){
         if (flag==true){
           for (i=0;i<massize;i++){
               if ((year_lc==mas_year[i])&&(month_lc==mas_month[i])&&(day_lc==mas_day[i]-c)&&(hour_lc==mas_hour[i])){
                  close_l=i;
                  day_lc=mas_day[i]-c;
                  flag=false;
               }

           }
         }
     }
     //Закрытие трейда
     flag=true; c=0;
     for (i=0;i<massize;i++){
         if ((year_tc==mas_year[i])&&(month_tc==mas_month[i])&&(day_tc==mas_day[i])&&(hour_tc==mas_hour[i])){
            close_t=i;
            flag=false;
         }

     }
     for (c=-4;c<4;c++){
         if (flag==true){
           for (i=0;i<massize;i++){
               if ((year_tc==mas_year[i])&&(month_tc==mas_month[i])&&(day_tc==mas_day[i]-c)&&(hour_tc==mas_hour[i])){
                  close_t=i;
                  day_tc=mas_day[i]-c;
                  flag=false;
               }

           }
         }
     }
     //
     flag=true;//
     printf("L open %d %d %d %d\n",year_lo,month_lo,day_lo,hour_lo);
     printf("L close %d %d %d %d\n",year_lc,month_lc,day_lc,hour_lc);
     printf("T open %d %d %d %d\n",year_to,month_to,day_to,hour_to);
     printf("T close %d %d %d %d\n",year_tc,month_tc,day_tc,hour_tc);
    // Защита от дурачьков.
     printf("B_C open_l=%d close_l=%d open_t=%d close_t=%d\n",open_l,close_l,open_t,close_t);
      if (close_l<open_l){
         int temp1;
         temp1=open_l;
         open_l=close_l;
         close_l=temp1;
      }
      if (close_t<open_t){
         int temp1;
         temp1=open_t;
         open_t=close_t;
         close_t=temp1;
      }
      if(open_l<55) open_l=56;
      if(open_t<55) open_t=56;
      if(close_l>=massize) close_l=massize-1;
      if(close_t>=massize) close_t=massize-1;
      //
      printf("A_C open_l=%d close_l=%d open_t=%d close_t=%d\n",open_l,close_l,open_t,close_t);

      //Освобождаем память от ненужных массивов перед запуском цикла обучения
      for(i=0;i<massize;i++) free(str_file[i]);
      free(str_file);
      //free(mas_year);
      //free(mas_month);
      //free(mas_day);
      //free(mas_hour);
      //
     //нахождение всех необходимы коефициетвов осцилляторов для обучения
     for (i=open_l;i<=close_l;i++){
         mas_ao[i][0]=ao(mas_low,mas_high,i);
         mas_ao[i][1]=ao(mas_low,mas_high,i-7);
         mas_ao[i][2]=ao(mas_low,mas_high,i-14);
         mas_ao[i][3]=ao(mas_low,mas_high,i-21);
         //printf("a1= %f a2= %f a3= %f a4= %f i= %d\n",mas_ao[i][0],mas_ao[i][1],mas_ao[i][2],mas_ao[i][3],i);
     }
    //обучение(подбор весовых коефициентов, при которых профит максимальный)
    //FILE* output_l=fopen("output_l.txt","w+");
    bool open=true,close=false;
    for (i1=1;i1<=100;i1++){
        printf("%d",i1-1);
        for (i2=1;i2<=100;i2++){
            for (i3=1;i3<=100;i3++){
                for (i4=1;i4<=100;i4++){
                    //c=0;
                    profit=0;
                    open=true;
                    close=false;
                    //fprintf(output_l,"==========================\nCoefficients: w1=%d w2=%d w3=%d w4=%d\n===========================\n",i1,i2,i3,i4);
                    for (i=open_l;i<=close_l;i++){
                        a1=mas_ao[i][0];
                        a2=mas_ao[i][1];
                        a3=mas_ao[i][2];
                        a4=mas_ao[i][3];
                        d=a1*i1+a2*i2+a3*i3+a4*i4;
                        if (open==true){
                           if (d>0){
                              //c++;
                              profit=profit-mas_open[i];
                              open=false;
                              close=true;
                              //fprintf(output_l,"--------------------------------------------\nDeal id= %d:\nOpen number in a file of quotations %d %dy %dm %dd %dh open price= %f profit= %f\n",c,i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_open[i],profit);
                           }
                        }
                        if (close==true){
                           if (d<0){
                              profit=profit+mas_close[i];
                              close=false;
                              open=true;
                              //fprintf(output_l,"Close number in a file of quotations %d %dy %dm %dd %dh close price= %f profit= %f\n",i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_close[i],profit);
                           }
                        }
                        if ((close==true)&&(i==close_l)){
                            profit=profit+mas_close[i];
                            close=false;
                            open=true;
                        }

                        if (profit>profit_max){
                           profit_max=profit;
                           w1_max=i1;
                           w2_max=i2;
                           w3_max=i3;
                           w4_max=i4;
                        }
                    }
                }
            }
        }
    }//
    //fclose(output_l);
    printf("\nTraining complete.\n w1=%f  w2=%f w3=%f w4=%f profit_max=%f\n",w1_max,w2_max,w3_max,w4_max,profit_max);
    printf("You were training from %dy %dm %dd %dh to %dy %dm %dd %dh\n",year_lo,month_lo,day_lo,hour_lo,year_lc,month_lc,day_lc,hour_lc);
    if ((y_n=='n')||(y_n=='N')){
    printf("Input trading start date\n");
    printf("Input year: ");
    scanf("%d",&year_to);
    printf("Input month: ");
    scanf("%d",&month_to);
    printf("Input day: ");
    scanf("%d",&day_to);
    printf("Input hour: ");
    scanf("%d",&hour_to);
    printf("Input trading end date\n");
    printf("Input year: ");
    scanf("%d",&year_tc);
    printf("Input month: ");
    scanf("%d",&month_tc);
    printf("Input day: ");
    scanf("%d",&day_tc);
    printf("Input hour: ");
    scanf("%d",&hour_tc);
  }
    //нахождение всех необходимы коефициетвов осцилляторов для торговли
     for (i=open_t;i<=close_t;i++){
         mas_ao[i][0]=ao(mas_low,mas_high,i);
         mas_ao[i][1]=ao(mas_low,mas_high,i-7);
         mas_ao[i][2]=ao(mas_low,mas_high,i-14);
         mas_ao[i][3]=ao(mas_low,mas_high,i-21);
         //printf("a1= %f a2= %f a3= %f a4= %f i= %d\n",mas_ao[i][0],mas_ao[i][1],mas_ao[i][2],mas_ao[i][3],i);
     }
    //Торговля
    FILE* output_t=fopen("output_t.txt","w+");
    profit=0;
    open=true,close=false;
    c=0;
    fprintf(output_t,"==========================\nCoefficients: w1=%f w2=%f w3=%f w4=%f\n===========================\n",w1_max,w2_max,w3_max,w4_max);
    for (i=open_t;i<=close_t;i++){
                        a1=mas_ao[i][0];
                        a2=mas_ao[i][1];
                        a3=mas_ao[i][2];
                        a4=mas_ao[i][3];
                        d=a1*w1_max+a2*w2_max+a3*w3_max+a4*w4_max;
                        if (open==true){
                           if (d>0){
                              c++;
                              profit=profit-mas_open[i];
                              open=false;
                              close=true;
                              fprintf(output_t,"--------------------------------------------\nDeal id= %d:\nOpen number in a file of quotations %d %dy %dm %dd %dh open price= %f profit= %f\n",c,i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_open[i],profit);
                           }
                        }
                        if (close==true){
                           if (d<0){
                              profit=profit+mas_close[i];
                              close=false;
                              open=true;
                              fprintf(output_t,"Close number in a file of quotations %d %dy %dm %dd %dh close price= %f profit= %f\n",i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_close[i],profit);
                           }
                        }
                        if ((close==true)&&(i==close_l)){
                            profit=profit+mas_close[i];
                            close=false;
                            open=true;
                            fprintf(output_t,"Close number in a file of quotations %d %dy %dm %dd %dh close price= %f profit= %f\n",i,mas_year[i],mas_month[i],mas_day[i],mas_hour[i],mas_close[i],profit);

                        }
    }
    fclose(output_t);
    printf("\nYou were trading from %dy %dm %dd %dh to %dy %dm %dd %dh\n",year_to,month_to,day_to,hour_to,year_tc,month_tc,day_tc,hour_tc);
    printf("Trading complete.\n w1=%f  w2=%f w3=%f w4=%f profit=%f",w1_max,w2_max,w3_max,w4_max,profit);
    printf("\n");//*/

}

float mp (float low,float high){
    return (low+high)/2;
}
float sma(float* mas_low,float* mas_high,int ind,int n){
    float sum=0;
    for (int i=ind-n;i<ind;i++){
        sum+=mp(mas_low[i],mas_high[i]);
    }
    return sum/n;
}
float ao(float* mas_low,float* mas_high,int ind){
    return sma(mas_low,mas_high,ind,34)-sma(mas_low,mas_high,ind,5);
}
void funk(char * pStr,char cByte)
{
    while(pStr[0]!=0) pStr++;
    pStr[0]=cByte;
}

mainwindow::~mainwindow()
{
    delete ui;
}
