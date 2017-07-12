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

#define STACK_INIT_SIZE  10
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
    printf("\n Empty Stack\n");
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
      printf("\n Realloc Fail\n");
      return ERROR;
    }
    S->top = S->base + S->stacksize;
    S->stacksize += STACKINCREMENT;
  }
  *S->top++ = e;
  return OK;
}

/******************************************************
Description  :check Stack is Empty
Input        :SqStack *S
OutPut       :None
Return Value :OK/ERROR(0/-1)
Calls        :
Call By      :
******************************************************/
int IsEmpty(SqStack *S)
{
  if(S->top == S->base)
  {
    return 1;
  }
  else
  {
    return 0;
  }
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
    printf("\n Empty Stack \n");
    return ERROR;
  }
  *e = --S->top;
  
  return OK;
}

/******************************************************
Description  :Clear The Stack
Input        :SqStack *S
OutPut       :None
Return Value :(OK/ERROR)
Calls        :
Call By      :
******************************************************/
int ClearStack(SqStack *S)
{
    SElemType *p;
    while(S->top)
    {
       p = S->top;
       S->top--;
       S->stacksize--;
       free(p); 
    }
    return OK;
}

/******************************************************
Description  :Destroy The Stack
Input        :SqStack *S
OutPut       :None
Return Value :
Calls        :
Call By      :
******************************************************/
void Destroy(SqStack *S)
{
  ClearStack(S);
  free(S);
  return;
}


/******************************************************
Description  :Convert decimal to 8
Input        :int value
OutPut       :None
Return Value :
Calls        :
Call By      :
******************************************************/
void Convert(int value)
{
  SqStack *pST = (SqStack *)malloc(sizeof(SqStack));
  SElemType stSlem = {0};
  SElemType *pGetTopElem = (SElemType *)malloc(sizeof(SElemType));
  int Ret = InitStack(pST);
  int Mod = 0;

  printf("%d is convert to 8 is ",value);
  
  while(value)
  {
    Mod = value % 8;
    stSlem.value = Mod;
    Push(pST,stSlem);
    value /=8;
  }
  while(!Pop(pST,&pGetTopElem))
  {
    printf("%d ",pGetTopElem->value);
  }
  printf("\n");
}


/******************************************************
Description  :Check ()[]{}if match
Input        :char *pStore
OutPut       :None
Return Value :
Calls        :
Call By      :
******************************************************/
void MatchCheck(char * pStore)
{
  SqStack *pST = (SqStack *)malloc(sizeof(SqStack));
  int Ret = 0;
  SElemType stSlem = {0};
  SElemType *pGetTopElem = (SElemType*)malloc(sizeof(SElemType));
  Ret = InitStack(pST);
  while(*pStore)
  {
    memset(&stSlem,0,sizeof(SElemType));
    strcpy(stSlem.cStr,pStore);
    switch(*pStore)
    {
      case '(':
      case '[':
      case '{':
        Ret = Push(pST,stSlem);
        pStore++;
        break;
      case ')':
      case ']':
      case '}':
        Ret = Pop(pST,&pGetTopElem);
        if((*pGetTopElem->cStr=='(' && *pStore==')')||(*pGetTopElem->cStr=='[' && *pStore==']') || (*pGetTopElem->cStr=='{' && *pStore=='}'))
        {
          pStore++;
        }
        else
        {
          printf("Not Match\n");
          return;
        }
        break;
      default:
        pStore++;
        break;
    }
  }
  if(IsEmpty(pST))
  {
    printf("Match\n");
  }
  else
  {
    printf("Not Match\n");
  }
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
  char Store[] = "[(){}]";
  Ret = InitStack(pST);
  
  for(index=0;index<STACK_INIT_SIZE;index++)
  {
    stElem.value = index;
    strcpy(stElem.cStr,strDemo);
    Ret = Push(pST,stElem);
  }
/*
  while(!Pop(pST,&getTopElem))
  {
    printf("Stack pop %s and %d \n",getTopElem->cStr,getTopElem->value);
  }

*/

  Convert(1348);
 MatchCheck(Store);
  Destroy(pST);
}








