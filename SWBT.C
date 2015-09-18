#include<graphics.h> 
      main(){ 
         char str[8]={10,20,30,40,50,60,70,80}; /*用户定义图模*/ 
         int gdriver,gmode,i; 
         struct fillsettingstype save; /*定义一个用来存储填充信息的结构变量*/ 
         gdriver=DETECT; 
         initgraph(&gdriver,&gmode,"c:\\bgi"); 
         setbkcolor(BLUE); 
         cleardevice(); 
         for(i=0;i<13;i++) 
        { 
         setcolor(i+3); 
         setfillstyle(i,2+i);      /* 设置填充类型 * 
         bar(100,150,200,50);      /*画矩形并填充*/ 
         bar3d(300,100,500,200,70,1); /* 画长方体并填充*/ 
         pieslice(200, 300, 90, 180, 90);/*画扇形并填充*/ 
         sector(500,300,180,270,200,100);/*画椭圆扇形并填充*/ 
         delay(1000);         /*延时1秒*/ 
         } 
        cleardevice(); 
        setcolor(14); 
        setfillpattern(str, RED); 
        bar(100,150,200,50); 
        bar3d(300,100,500,200,70,0); 
        pieslice(200,300,0,360,90); 
        sector(500,300,0,360,100,50); 
        getch(); 
        getfillsettings(&save);       /*获得用户定义的填充模式信息*/ 
        closegraph(); 
        clrscr(); 
        printf("The pattern is %d, The color of filling is %d", save.pattern, save.color);
 /*输出目前填充图模和颜色值*/ 
        getch(); 
      } 