#include<stdio.h>
#include<stdlib.h>
#define TRUE   1
#define FALSE  0
#define OK     1
#define ERROR  0
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef int ElemType;
typedef struct
{
	ElemType* base;   // 栈底指针
	ElemType* top;    // 栈顶指针
	int  stacksize;      // 栈的可用最大容量
}SqStack;

Status InitStack(SqStack& S)                 //1.初始化栈：//将栈S置为一个空栈(不含任何元素)
{
	S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base)  exit(OVERFLOW); //存储分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}//InitStack

Status DestoryStack(SqStack& S)//2.销毁栈

{
	ElemType* p;
	p = S.base;
	free(p);
	S.base = NULL;
	return OK;
}

Status Push(SqStack& S, ElemType e)//3.进栈：//将元素X插入到栈S中，也称为 “入栈”、 “插入”、 “压入”。


{
	if (S.top - S.base >= S.stacksize) {//栈满，追加存储空间
		S.base = (ElemType*)realloc(S.base,
			(S.stacksize + STACK_INIT_SIZE) * sizeof(ElemType));
		if (!S.base) exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}//Push

Status Pop(SqStack& S, ElemType& e)          //4.出栈：//删除栈S中的栈顶元素，也称为”退栈”、 “删除”、 “弹出”。


{
	if (S.top == S.base) return ERROR;
	e = *--S.top;
	return OK;
}//pop

Status GetTop(SqStack S, ElemType& e)//5.取栈顶元素：//取栈S中栈顶元素。


{
	if (S.top == S.base) return ERROR;
	e = *(S.top - 1);
	return OK;
}//gettop

Status StackEmpty(SqStack S)//6.判栈空：//判断栈S是否为空，若为空，返回值为true，否则返回值为false。


{
	if (S.top == S.base)
		return TRUE;
	else
		return FALSE;
}

Status StackTraverse(SqStack S)//7.遍历栈元素//从栈底元素向栈顶元素逐个遍历


{
	ElemType* p;
	p = S.base;
	while (S.top > p)
		printf("%s", *p++);
	return OK;
}

void conversion(int a, int N[10])//非负数的十进制转八进制

{
	int i;
	ElemType e;
	SqStack S;
	InitStack(S);
	for (i = 0; i < a; i++)
	{
		while (N[i])
		{
			Push(S, N[i] % 8);
			N[i] = N[i] / 8;
		}
		printf("第%d个数转化为八进制数为：", i + 1);
		while (!StackEmpty(S))
		{
			Pop(S, e);
			printf("%d", e);
		}
		printf("\n");
	}
}//conversion

void main()
{
	printf("请输入个数：");
	int a;
	scanf("%d", &a);
	int i, n[10];
	for (i = 0; i < a; i++)
	{
		printf("请输入第%d个数字：", i + 1);
		scanf("%d", &n[i]);
	}

	conversion(a, n);
	system("pause");
}