#include <GRAPHICS.H>
#define PREOD "preorder"
#define INOD "inorder"
#define POSTOD "postorder"
#define INSERT "insert "
#define DEL "del "
#define LEAF "leaf"
#define FIND "find "
#define EXIT "exit"
#define HELP "help"
int FileOp(char filename[],char retbuf[]);

void showCommand(char cmd[]);
void Flash_Input();
int KEY_STATE=0;
int FileOp(char filename[],char retbuf[])
{
	int i=0;
	FILE *fp;
	fp=fopen(filename,"r");
	if(fp==NULL){puts("file error");return 0;}
	while((retbuf[i++]=fgetc(fp))!=EOF);
	retbuf[--i]='\0';
	fclose(fp);
	return 1;
}
void GetCommand(char cmd[])
{
	int i=0,j=1;
	
	char ch='\0';
	char list[9][12]={
		"preorder",
		"inorder",
		"postorder",
		"insert ",
		"del ",
		"leaf",
		"find ",
		"exit",
		"help"
	};
	
	cmd[i]='_';
	cmd[i+1]='\0';
	setcolor(WHITE);
	outtextxy(10,getmaxy()-120,"command :");
	showCommand(cmd);
	while(ch!=0x0D)
	{
		if(!kbhit())
		{
			ch=getch();
			Flash_Input();
			if((ch>='a'&&ch<='z')||ch==' ')
			{
				cmd[i++]=ch;
				cmd[i]='_';
				cmd[i+1]='\0';
				
			}else if(ch==8&&i>0)
			{
				Flash_Input();
				cmd[--i]='_';
				cmd[i+1]='\0';
			}else if(ch==0x00)
			{
				ch=getch();
				switch(ch)
				{
				case 0x48:j--;if(j<0)j=7;break;
				case 0x50:j++;if(j>7)j=0;break;
				}
				if(ch==0x48||ch==0x50)
				{
					strcpy(cmd,list[j]);i=strlen(list[j]);
					cmd[i]='_';
					cmd[i+1]='\0';
				}else 
				{
					strcpy(cmd,list[8]);i=strlen(list[j]);
					cmd[i]='_';
					cmd[i+1]='\0';
				}
				
				
				
			}else if(ch!=0x0D)
			{
				
				strcpy(cmd,list[8]);i=strlen(list[j]);
				cmd[i]='_';
				cmd[i+1]='\0';
				showCommand(cmd);	
				if((ch=getch())==0x00)
				{
					ch=getch();
				}
			}
			
			
			showCommand(cmd);		
		}
		
	}
	cmd[i]='\0';
}
void showCommand(char cmd[])
{	
	setcolor(WHITE);
	outtextxy(50,getmaxy()-100,cmd);
}	


void Flash_Input()	
{
	int i;
	setcolor(BLACK);
	for(i=0;i<=20;i++)
	{
		line(20,getmaxy()-100+i,getmaxx(),getmaxy()-100+i);
	}
}
	
