/******************************************************
Description  :This File Tell U How To Use Stack
History      :
Date         :2017/7/7
Author       :wangzai
Modification :
******************************************************/
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define STACK_INIT_SIZE  100
#define STACKINCREMENT   10
#define STRLEN           20
#define OK               0
#define ERROR            -1

typedef struct selemtype
{
  int  value;
  char cStr[STRLEN];
}SElemType;

typedef struct sqstack
{
  SElemType * base;
  SElemType * top;
  int   stacksize;
}SqStack;

/******************************************************
Description  :Init a Stack
Input        :SqStack *S
OutPut       :None
Return Value :OK/ERROR(0/-1)
Calls        :
Call By      :
******************************************************/
int InitStack(SqStack *S)
{
  S->base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
  if(!S->base)
  {
    printf("Malloc Failed\n");
    return ERROR;
  }
  S->top = S->base;
  S->stacksize = STACK_INIT_SIZE;
  return OK;
}


/******************************************************
Description  :Get Stack Top ElemType
Input        :SqStack *S
              SElemType **e
OutPut       :None
Return Value :OK/ERROR(0/-1)
Calls        :
Call By      :
******************************************************/
int GetTop(SqStack * S,SElemType **e)
{
  if(S->base == S->top)
  {
    printf("Empty Stack\n");
    return ERROR;
  }
  *e = S->top-1;
  return OK;
}

/******************************************************
Description  :Push a Element In The Stack
Input        :SqStack *S
              SElemType e
OutPut       :None
Return Value :OK/ERROR(0/-1)
Calls        :
Call By      :
******************************************************/
int Push(SqStack *S,SElemType e)
{
  if(S->top - S->base >= S->stacksize)
  {
    S->base = (SElemType *)realloc(S->base,(S->stacksize + STACKINCREMENT)*sizeof(SElemType));
    if(!S->base)
    {
      printf("Realloc Fail\n");
      return ERROR;
    }
    S->top = S->base + S->stacksize;
    S->stacksize += STACKINCREMENT;
  }
  *S->top++ = e;
  return OK;
}


/******************************************************
Description  :Pop a Element From The Stack
Input        :SqStack *S
              SElemType **e
OutPut       :None
Return Value :OK/ERROR(0/-1)
Calls        :
Call By      :
******************************************************/
int Pop(SqStack *S,SElemType **e)
{
  if(S->top == S->base)
  {
    printf("Empty Stack\n");
    return ERROR;
  }
  *e = --S->top;
  
  return OK;
}

int main()
{
  SqStack ST   = {0};
  SqStack *pST = &ST;
  
  SElemType stElem = {0};
  SElemType *getTopElem = (SElemType *)malloc(sizeof(SElemType));

  char strDemo[] = "Hello  BAT";
  int  Ret       = 0;
  int  index     = 0;

  Ret = InitStack(pST);

  for(index=0;index<STACK_INIT_SIZE;index++)
  {
    stElem.value = index;
    strcpy(stElem.cStr,strDemo);
    Ret = Push(pST,stElem);
  }

  while(!Pop(pST,&getTopElem))
  {
    printf("Stack pop %s and %d \n",getTopElem->cStr,getTopElem->value);
  }



}







