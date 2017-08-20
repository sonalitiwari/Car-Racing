#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<graphics.h>
#include<dos.h>
#include<stdlib.h>
class graph
{
 int x,y,time,change;
 int arrx[2],arry[2];
 static int count,level,level_count,car_count;
 int last_choice,choice,total_score,level_score;
 public:
 graph()
 {
  int i;
  x=0;y=0;
  count=0;
  level_count=0;
  car_count=0;
  level_score=0;
  total_score=0;
  level=0;
  choice=0;
  last_choice=0;
  change=20;
  time=200;
  for(i=0;i<2;i++)
  {
   arrx[i]=0;
   arry[i]=0;
  }
 }
 void car(int x_cord,int y_cord)
 {
  x=x_cord;
  y=y_cord;
  setfillstyle(1,0);
  bar(x_cord-20,y_cord-60,x_cord+20,y_cord-30);
  bar(x_cord-50,y_cord-30,x_cord-20,y_cord);
  bar(x_cord+20,y_cord-30,x_cord+50,y_cord);

  bar(x_cord-20,y_cord,x_cord+20,y_cord+30);
  bar(x_cord-55,y_cord+30,x_cord-20,y_cord+60);
  bar(x_cord+20,y_cord+30,x_cord+55,y_cord+60);
  setfillstyle(1,15);
 }
 void r_car(int rc_x,int rc_y)
 {
  setfillstyle((level+2)%12,level+1);
  bar(rc_x-20,rc_y-60,rc_x+20,rc_y-30);
  bar(rc_x-50,rc_y-30,rc_x-20,rc_y);
  bar(rc_x+20,rc_y-30,rc_x+50,rc_y);

  bar(rc_x-20,rc_y,rc_x+20,rc_y+30);
  bar(rc_x-55,rc_y+30,rc_x-20,rc_y+60);
  bar(rc_x+20,rc_y+30,rc_x+55,rc_y+60);
  setfillstyle(1,15);
 }
 void random_car()
 {
  int f=0,rc_x,rc_y,i;
  if(count<2)
  {
    do
    {
     choice=random(3);
    }
    while(choice==last_choice);
    last_choice=choice;
    switch(choice)
    {
     case 0:
      rc_x=200;
      rc_y=change;
      break;
     case 1:
      rc_x=320;
      rc_y=change;
      break;
     case 2:
      rc_x=440;
      rc_y=change;
    }
    for(i=0;i<2;i++)
    {
     if(arrx[i]==0 && arry[i]==0)
     {
      arrx[i]=rc_x;
      arry[i]=rc_y;
      break;
     }
    }
    count++;
  }
  for(i=0;i<2;i++)
  {
   if(!(arrx[i]==0 && arry[i]==0))
    r_car(arrx[i],arry[i]);
  }
 }
 void cord_match()
 {
  int i,j;
  for(i=0;i<2;i++)
  {
   if(arry[i]>=y-60&&arry[i]<=480&&arrx[i]>=x-60&&arrx[i]<=x+60)
   {
    for(j=0;j<=320;j+=50)
    {
     setfillstyle(1,j);
     bar(j,0,j+50,480);
     bar(640-j,0,(640-j)-50,480);
     delay(50);
    }
    setcolor(4);
    settextstyle(1,0,5);
    outtextxy(220,220,"Game Over");
    do
    {
     sound(300);
     delay(50);
     sound(100);
     delay(100);
     sound(200);
     delay(50);
    }
    while(!kbhit());
    nosound();
    exit(0);
   }
  }
 }
 void road(int x_cord,int y_cord);
};
 void graph::road(int x_cord,int y_cord)
 {
  int x1,y1,x2,y2,i=0;
  static int flag=0;
  cleardevice();
  x1=320-180;
  x2=320+180;
  y1=0;
  y2=480;

  gotoxy(65,5);
  cprintf("Total Score");
  gotoxy(65,6);
  cprintf("(%d)",total_score);
  gotoxy(65,8);
  cprintf("Level: %d",level+1);
  gotoxy(65,9);
  cprintf("LevelScore: %d",level_score);
  setfillstyle(1,7);
  bar(x1,y1,x2,y2);
  setfillstyle(1,15);

  if(flag==0)
  {
   i=0;
   flag=1;
  }
  else
  {
   flag=0;
   i=50;
  }
  for(;i<=480;i=i+120)
  {
   bar(315,i,325,i+50);
  }
  car(x_cord,y_cord);
  random_car();
  for(i=0;i<2;i++)
  {
   if(arry[i]!=0)
    arry[i]+=change;
   if(arry[i]>480)
   {
    arrx[i]=arry[i]=0;
    sound(100);
    delay(100);
    nosound();
    count--;
    car_count++;
    level_score=car_count*((level+1)*10);
   }
  }
  cord_match();
  if(car_count==10)
  {
   total_score=total_score+level_score;
   car_count=0;
   level++;
   if(change<60)
    change+=5;
   if(time-50>0)
    time-=5;
  }
  delay(time);
 }

int graph::count=0,graph::level=0,graph::level_count=0,graph::car_count=0;
void main()
{
 clrscr();
 int gd=0,gm,errorcode;
 int i,x_cord=320,y_cord=480-60;
 char ch;
 initgraph(&gd,&gm,"c:\\turboc3\\bgi");
 errorcode = graphresult();
 if (errorcode != grOk)
 {
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);
 }
 directvideo=0;
 randomize();
 graph g;
 do
 {
  do
  {
   do
   {
    g.road(x_cord,y_cord);
   }
   while(!kbhit());
   ch=getch();
  }
  while(!(ch=='a'||ch=='A'||ch=='d'||ch=='D'||ch==13||ch==27));
  if(ch=='a'||ch=='A')
  {
   if(x_cord>=320-60)
    x_cord-=120;
  }
  else if(ch=='d'||ch=='D')
  {
   if(x_cord<=320+60)
    x_cord+=120;
  }
 }
 while(!(ch==13||ch==27));
}
