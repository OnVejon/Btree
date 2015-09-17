#ifndef _BINTREE.H
#define _BINTREE.H

#include <stdlib.h>
#include <malloc.h>
#include<GRAPHICS.H>
#include <dos.h>
typedef char DataType;

typedef struct node
{
	DataType data;
	struct node *rchild,*lchild;
}BinNode,*BinTree;
#define PRE 'p'
#define IN 'i'
#define POST 'l'
void PreCreateBTree(BinTree *bt,DataType a[]);

void BTFindNode(BinTree bt,BinTree *p,DataType data,char key,void (*fp)(BinTree));

int BTFindLeaf(BinTree bt,BinTree p[]);

int InsertBiTree(BinTree bt,DataType z,DataType w,char ch);

void DeleteBTree(BinTree *bt,DataType x);

int GetDepth(BinTree bt);

void PreOrderTraverse(BinTree bt,void (*fp)(BinTree));

void InOrderTraverse(BinTree bt,void (*fp)(BinTree));

void PostOrderTraverse(BinTree bt,void (*fp)(BinTree ));

/*
1)若二叉树空，返回空；
2)若不空，取先序序列第一个元素，建立根节点；
3)在中序序列中查找根节点，以此确定左右子树的先序序列和中序序列；
4)递归调用自己，建左子树；
5)递归调用自己，建右子树。
*/
static int PRE_I=0;/*创建函数准备变量*/
static int FIND_NODE=0;/*查找函数准备参数*/
static int FIND_LEAF=0;/*查找函数准备参数*/
/*
函数名：PreCreateBT(私有)
功能：前序创建二叉树
参数：返回二叉树根指针，创建二叉树数据组
返回值：1成功，0失败
*/
void PreCreateBT(BinTree *bt,DataType a[])
{
	
	if(a[PRE_I]=='\0')
		*bt=0;
	else if(a[PRE_I]=='.')
	{
		*bt=0;
		PRE_I++;
	}	
	else
	{
		*bt=(BinTree)malloc(sizeof(BinNode));
		if(!(*bt)){puts(" Not enough memory");exit(0);}
		(*bt)->data=a[PRE_I++];
		PreCreateBT(&((*bt)->lchild),a);
		PreCreateBT(&((*bt)->rchild),a);
	}
}
/*
函数名：PreCreateBTee（公开）
功能：前序创建二叉树
参数：返回二叉树根指针，创建二叉树数据组
返回值：1成功，0失败
*/
void PreCreateBTree(BinTree *bt,DataType a[])
{
	PRE_I=0;
	PreCreateBT(bt,a);
	if(GetDepth(*bt)>5){puts("TREE DEPTH ERROR!");exit(0);}
		
}

/*
函数：FindNode(私有)
功能：先序遍历查找节点
参数：传入节点、返回节点、查找节点数据
FNBegin初始化参数函数
*/
void FindNode(BinTree bt,BinTree *p,DataType data,char key,void (*fp)(BinTree))
{
	
	if(bt)
	{
		if(IN==key)
		{
			
			FindNode(bt->lchild,p,data,key,fp);
			if(FIND_NODE==0)
			{
				*p=bt;
				if(fp)
					fp(bt);
				if(bt->data==data)
					FIND_NODE++;
			}
			FindNode(bt->rchild,p,data,key,fp);
		}else if(POST==key)
		{
			FindNode(bt->lchild,p,data,key,fp);
			FindNode(bt->rchild,p,data,key,fp);
			if(FIND_NODE==0)
			{
				*p=bt;
				if(fp)
					fp(bt);
				if(bt->data==data)
					FIND_NODE++;
			}
			
		}else
		{
			if(FIND_NODE==0)
			{
				*p=bt;
				if(fp)
					fp(bt);
				if(bt->data==data)
					FIND_NODE++;
			}
			FindNode(bt->lchild,p,data,key,fp);
			FindNode(bt->rchild,p,data,key,fp);
		}
			
		
	}
}
/*
函数：BTFindNode（开放）
功能：先序遍历查找节点
参数：传入节点、返回节点、查找节点数据
FNBegin初始化参数函数
*/
void BTFindNode(BinTree bt,BinTree *p,DataType data,char key,void (*fp)(BinTree))
{
	FIND_NODE=0;
	FindNode(bt,p,data,key,fp);
}
/*
函数：FindParent(私有)
功能：先序遍历查找节点
参数：传入节点、返回节点、查找节点数据
FNBegin初始化参数函数
*/
void FindParent(BinTree bt,BinTree *p,DataType data,char key)
{
	
	if(bt)
	{
		
		if((bt->lchild->data==data||bt->rchild->data==data)&&(FIND_NODE==0))
		{
			
			*p=bt;
			FIND_NODE++;
		}
		FindParent(bt->lchild,p,data,key);
		FindParent(bt->rchild,p,data,key);
		
			
		
	}
}
/*
函数：BTFindParent（开放）
功能：先序遍历查找节点的父母
参数：传入节点、返回节点、查找节点数据
FNBegin初始化参数函数
*/
int BTFindParent(BinTree bt,BinTree *p,DataType data,char key)
{
	FIND_NODE=0;
	FindParent(bt,p,data,key);
	if((*p)->lchild->data==data)
		return 1;
	else if((*p)->rchild->data==data)
		return 2;
	else
		return 0;
}
/*
函数：DeleteBT
功能：后序遍历free节点
参数：传入节点
*/

void DeleteBT(BinTree *bt)
{
	if(*bt)
	{
		DeleteBT(&((*bt)->lchild));
		DeleteBT(&((*bt)->rchild));
		free(*bt);
	
	}
}
/*
函数：DeleteBTree
功能：后序遍历free节点
参数：传入root、节点数据
*/


void DeleteBTree(BinTree *bt,DataType x)
{
	
	int i;
	BinTree p;
	
	if((*bt)->data==x)
	{
		DeleteBT(bt);
		*bt=0;
	}else
	{
		i=BTFindParent(*bt,&p,x,PRE);
	
		if(i==1)
		{
			DeleteBT(&(p->lchild));
			p->lchild=0;
		}else if(i==2)
		{
			DeleteBT(&(p->rchild));
			p->rchild=0;
		}
	
	}
	
}
/*
函数：FindLeaf
功能：先序遍历查找节点
参数：传入节点、返回节点、查找节点数据
*/

void FindLeaf(BinTree bt,BinTree p[])
{
	if(bt)
	{
		
		if((bt->lchild==0)&&(bt->rchild==0))
		{
			p[FIND_LEAF++]=bt;
			
		}
		FindLeaf(bt->lchild,p);
		FindLeaf(bt->rchild,p);
	}
}
/*
函数：BTFindLeaf
功能：先序遍历查找节点
参数：传入节点、返回节点、查找节点数据
*/
int BTFindLeaf(BinTree bt,BinTree p[])
{
	FIND_LEAF=0;
	FindLeaf(bt,p);
	return FIND_LEAF;
}

/*
函数：InsertBiTree
功能：z(插入位置) w(插入内容) l/r(插入位置：l左子树，r右子树，二选一)
参数：传入节点、返回节点、查找节点数据
返回值：0失败 1成功，
*/
int InsertBiTree(BinTree bt,DataType z,DataType w,char ch)
{
	BinTree p,newp;
	
	BTFindNode(bt,&p,z,'p',0);
	
	newp=(BinTree)malloc(sizeof(BinNode));
	newp->data=w;
	
	if(ch=='l')
	{
		newp->lchild=p->lchild;
		newp->rchild=0;
		p->lchild=newp;
		if(GetDepth(bt)>5)
		{
			p->lchild=newp->lchild;
			free(newp);
			return 0;
		}
	}else if(ch=='r')
	{
		newp->rchild=p->rchild;
		newp->lchild=0;
		p->rchild=newp;
		if(GetDepth(bt)>5)
		{
			p->rchild=newp->rchild;
			free(newp);
			return 0;
		}
	}
	return 1;
}



/*
函数：GetDepth
功能：遍历求树高
参数：传入root
*/
int GetDepth(BinTree bt)
{
	int depthLeft,depthRight;
	if(bt == 0) 
		return 0;
	depthLeft = GetDepth(bt->lchild);
	depthRight = GetDepth(bt->rchild);
	return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1); 
}
void PreOrderTraverse(BinTree bt,void (*fp)(BinTree))
{
	if(bt)
	{
		fp(bt);
		PreOrderTraverse(bt->lchild,fp);
		PreOrderTraverse(bt->rchild,fp);
	}
}

void InOrderTraverse(BinTree bt,void (*fp)(BinTree))
{
	if(bt)
	{
		InOrderTraverse(bt->lchild,fp);
		fp(bt);
		InOrderTraverse(bt->rchild,fp);
	}
}

void PostOrderTraverse(BinTree bt,void (*fp)(BinTree ))
{
	if(bt)
	{
		PostOrderTraverse(bt->lchild,fp);
		PostOrderTraverse(bt->rchild,fp);
		fp(bt);
	}
}
#endif