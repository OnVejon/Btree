#include "bintree.h"
#include<GRAPHICS.H>
#include <stdio.h>
#include <math.h>
typedef struct
{
	BinTree bt;
	int x;
	int y;
}BTreeXY;
void showTraverse(BinTree bt,char key);
void DrawBT(BinTree bt);
void FileOp(char a[]);
void ShowTree(BinTree bt);
void  FilledCircle(int x,int y,DataType cc);
void  SignFilledCircle(int x,int y,DataType cc);
void CLine(int x1, int y1, int x2, int y2,int color);
void BTreeToArr(BinTree bt,BTreeXY BTXY[]);
void GetBTArrXY(BTreeXY BTXY[]);
void showLeaf(BinTree bt);
BTreeXY BTXY[31];
int MAX_X,MAX_Y;/*屏幕宽度*/

int STATIC_X,STATIC_Y;/*线索化xy*/

int TRAVERSE_SIGN;/*线索化起始标记*/
typedef struct
{
	int x;
	int y;
}Rxy;

int main()
{
	BinTree bt,p;
	
	char a[100];
	int driver=DETECT,mode;
	MAX_X=getmaxx(),MAX_Y=getmaxy();
	initgraph(&driver,&mode,"c:\\bgi");
	settextstyle(2,0,6);
	FileOp(a);
	
	
	PreCreateBTree(&bt,a);
	ShowTree(bt);
	getch();
	/*
	showTraverse(bt,PRE);
	
	getch();
	cleardevice();
	ShowTree(bt);
	showTraverse(bt,IN);
	
	getch();
	cleardevice();
	ShowTree(bt);
	showTraverse(bt,POST);
	getch();
	*/
	InsertBiTree(bt,'n','w','r');
	
	cleardevice();
	ShowTree(bt);
	DeleteBTree(bt,'n');
	
	cleardevice();
	ShowTree(bt);
	
	showTraverse(bt,PRE);
	getch();
	
	cleardevice();
	ShowTree(bt);
	showLeaf(bt);
	getch();
	closegraph();
	return 1;
}
/*
函数名：FileOp
功能：从tree。txt中获取字符串
参数：字符串地址

*/
void FileOp(char a[])
{
	int i=0;
	FILE *fp;
	fp=fopen("tree.txt","r");
	if(fp==NULL){puts("file error");return ;}
	while((a[i++]=fgetc(fp))!=EOF);
	a[--i]='\0';
	fclose(fp);
}
void showLeaf(BinTree bt)
{
	int i,j;
	BinTree p[16];
	FindLeaf(bt,p);
	for(i=0;p[i];i++)
	{	
		j=0;
		while(p[i]!=BTXY[j].bt&&j<31)j++;
		SignFilledCircle(BTXY[j].x,BTXY[j].y,BTXY[j].bt->data);
		delay(200);
	}
	
}
void showTraverse(BinTree bt,char key)
{
	
	BTreeToArr(bt,BTXY);
	GetBTArrXY(BTXY);
	TRAVERSE_SIGN=0;
	if(key==PRE)
	{	
		
		PreOrderTraverse(bt,DrawBT);
	}else if(key==IN)
	{
		
		InOrderTraverse(bt,DrawBT);
	}else if(key==POST)
	{
		
		PostOrderTraverse(bt,DrawBT);
	}
		
	
}

void DrawBT(BinTree bt)
{
	int i=0;
	
	
	while(bt!=BTXY[i].bt&&i<31)i++;
	if(TRAVERSE_SIGN==0)
	{
		STATIC_X=BTXY[i].x;
		STATIC_Y=BTXY[i].y;
		TRAVERSE_SIGN++;
	}
	
	SignFilledCircle(BTXY[i].x,BTXY[i].y,BTXY[i].bt->data);
	CLine(STATIC_X,STATIC_Y,BTXY[i].x,BTXY[i].y,RED);
	delay(200);
	STATIC_X=BTXY[i].x;
	STATIC_Y=BTXY[i].y;
}
/*
函数名：
功能：标记圆
参数：

*/
void  SignFilledCircle(int x,int y,DataType cc)
{
	char ch[2]={0};
	ch[0]=cc;
	setfillstyle(1,RED);
	setfillstyle(1,RED);
	setcolor(RED);
	circle(x,y,15);
	floodfill(x, y, RED); 
	
	setcolor(YELLOW);
	outtextxy(x-3,y-9,ch);
	
}
/*
函数名：
功能：画圆
参数：

*/
void  FilledCircle(int x,int y,DataType cc)
{
	char ch[2]={0};
	ch[0]=cc;
	setfillstyle(1,GREEN);
	setcolor(GREEN);
	circle(x,y,12);
	
	floodfill(x, y, GREEN);
	
	setcolor(YELLOW);
	outtextxy(x-3,y-9,ch);
	
	
}
/*
函数名：
功能：画线
参数：

*/
void CLine(int x1, int y1, int x2, int y2,int color)
{
	setcolor(color);
	line(x1,y1,x2,y2);
}

/*
函数名：
功能：
参数：

*/
void ShowTree(BinTree bt)
{
	
	int i,j,old_rx,old_ry,sum=0;
	
	
	MAX_X=getmaxx(),MAX_Y=getmaxy();
	BTreeToArr(bt,BTXY);
	GetBTArrXY(BTXY);
	/*两个循环是建模时是二维数组，但实践中二维数组错误，于是用了累加 等算法来查找*/
	for(i=0;i<5;i++)
	{
		
		for(j=0;j<pow(2,i);j++)
		{	
			 if(i==0)
			{
				FilledCircle(BTXY[sum].x,BTXY[sum].y,BTXY[sum].bt->data);
			}else if(BTXY[sum].bt->data)
			{	
				old_ry=30+(i-1)*MAX_Y/7;
				old_rx=pow(-1,j)*MAX_X/pow(2,i+1)+BTXY[sum].x;
				CLine(old_rx,old_ry+10,BTXY[sum].x,BTXY[sum].y,WHITE);
				FilledCircle(BTXY[sum].x,BTXY[sum].y,BTXY[sum].bt->data);
			}
			sum++;		
		}
			
		
		
	}
}
/*
函数名：
功能：给结构体确定xy值
参数：

*/
void GetBTArrXY(BTreeXY BTXY[])
{
	int i,j;
	for(i=0;i<5;i++)
	{
			for(j=0;j<pow(2,i);j++)
			{
				if(i==0&&BTXY[0].bt!=0)
				{
					BTXY[0].x=(2*j+1)*MAX_X/pow(2,i+1);
					BTXY[0].y=30+i*MAX_Y/7;
					
				}else if(BTXY[leijia(i-1)+j].bt!=0)
				{
					BTXY[leijia(i-1)+j].x=(2*j+1)*MAX_X/pow(2,i+1);
					BTXY[leijia(i-1)+j].y=30+i*MAX_Y/7;
				}
				
			}
		
		
	}
}
/*
函数名：
功能：
参数：

*/
void BTreeToArr(BinTree bt,BTreeXY BTXY[])
{
	int i,j,k;
	BinTree newp;
	BTXY[0].bt=bt;
	for(i=0;i<5;i++)
	{
		if(i==0)
		{
			BTXY[0].bt=bt;
		}else if(i==1)
		{
			BTXY[1].bt=BTXY[0].bt->lchild;
			BTXY[2].bt=BTXY[0].bt->rchild;
		}else
		{	
			k=0;
			j=0;
			while(j<pow(2,i)&&k<pow(2,i-1))
			{
				if(BTXY[leijia(i-2)+k].bt==0)
				{
					BTXY[leijia(i-1)+j].bt=0;
					j++;
					BTXY[leijia(i-1)+j].bt=0;
					j++;
					k++;
				}else 
				{
					newp=BTXY[leijia(i-2)+k].bt;
					BTXY[leijia(i-1)+j].bt=newp->lchild;
					j++;
					BTXY[leijia(i-1)+j].bt=newp->rchild;
					j++;
					k++;
				}
				
			}
		}
		
	}
}
int leijia(int i)
{
	if(i==0)
	{
		return 1;
	}
	return pow(2,i)+leijia(i-1);
}