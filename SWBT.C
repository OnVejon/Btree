#include<graphics.h> 
      main(){ 
         char str[8]={10,20,30,40,50,60,70,80}; /*�û�����ͼģ*/ 
         int gdriver,gmode,i; 
         struct fillsettingstype save; /*����һ�������洢�����Ϣ�Ľṹ����*/ 
         gdriver=DETECT; 
         initgraph(&gdriver,&gmode,"c:\\bgi"); 
         setbkcolor(BLUE); 
         cleardevice(); 
         for(i=0;i<13;i++) 
        { 
         setcolor(i+3); 
         setfillstyle(i,2+i);      /* ����������� * 
         bar(100,150,200,50);      /*�����β����*/ 
         bar3d(300,100,500,200,70,1); /* �������岢���*/ 
         pieslice(200, 300, 90, 180, 90);/*�����β����*/ 
         sector(500,300,180,270,200,100);/*����Բ���β����*/ 
         delay(1000);         /*��ʱ1��*/ 
         } 
        cleardevice(); 
        setcolor(14); 
        setfillpattern(str, RED); 
        bar(100,150,200,50); 
        bar3d(300,100,500,200,70,0); 
        pieslice(200,300,0,360,90); 
        sector(500,300,0,360,100,50); 
        getch(); 
        getfillsettings(&save);       /*����û���������ģʽ��Ϣ*/ 
        closegraph(); 
        clrscr(); 
        printf("The pattern is %d, The color of filling is %d", save.pattern, save.color);
 /*���Ŀǰ���ͼģ����ɫֵ*/ 
        getch(); 
      } 