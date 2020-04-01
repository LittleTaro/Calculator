#include<stdio.h>
#include "Calculator.h"
#define ERROR 0

int range;    // 操作数范围
char* problem = NULL;  // 字符指针，指向生成的题目
typedef struct Frac{   //操作数   
    int Integer;   //整数部分
    int Nume;      //分子部分
    int Deno;      //分母部分
}Frac;   

typedef char (*point)[70];    //定义point为数组指针
typedef int (* point2)[10];  
typedef struct{
    int number;
    int flag;
}Order;       


typedef struct Node{
    Frac num;
    char ope;
    struct Node *prior;
    struct Node *next;
    int flag;         //1为数字          
}Node,*Link;                 



typedef struct{
    char Ops[7];
    int top;       //栈顶的位标
}Stack;            //存操作符的栈

typedef struct{
    Frac Fracs[4];
    int topn;       //栈顶元素的位置
}NumStack;           //存操作数的栈

NumStack *CreateNStack(){
    NumStack *p;
    p=(NumStack *)malloc(sizeof(NumStack));
    p->topn=-1;
    return p;
}

int PushNStack(NumStack *p,Frac x){
    if(p->topn+1==4)  return -1;
    p->topn++;
    p->Fracs[p->topn]=x;
    return 0;
}

int PopNStack(NumStack *p,Frac *e){
    if(p->topn==-1) return -1;
    *e=p->Fracs[p->topn];
    p->topn--;
    return 0;
}

Stack *CreateStack(){
    Stack *p;
    p=(Stack *)malloc(sizeof(Stack));
    p->top=-1;
    return p;
}

int EmptyStack(Stack *p){
    if(p->top==-1) return 1;
    else    
       return 0;
}

//压栈
int PushStack(Stack *p,char x){
    if(p->top+1==7)     
       return -1;
    p->top++;   
    p->Ops[p->top]=x;   
    return 0;
}

//出栈
int PopStack(Stack *p,char *x){
    if(p->top==-1)  return -1;
    *x=p->Ops[p->top--];
    return 0;
}

//销毁栈
int DeatroyStack(Stack *p){
    free(p);
    return 0;
}
//将temp.txt里的题目存到字符串数组里
point Store(int n){      //n为题目数
    FILE *fp;
    int i;
    point *p;    //用来接收每一个中缀表达式字符串的头指针
    point exp[n];   //定义一个指针数组存放各个头指针
    fp=fopen("temp.txt","r");
    if(fp==NULL) exit(-1);
    for(i=1;i<=n;i++){
        p=(point *)malloc(sizeof(point));
        fgets(p,70,fp);
        exp[i]=p;
    }
    fclose(fp);
    return exp;
}

int Priority(char a){
    if(a=='*'||a=='/') return 2;
    if(a=='+'||a=='-') return 1;
}


void PutO(Stack *p,char x,Node *Np){
    char *e;    //存放出栈的运算符
    Node *p1;
    if(EmptyStack(p)||x=='('||x=='['){  //如果为栈S为空，或字符为左括号，压栈
        if(PushStack(p,x)!=0)  return ERROR;
    }
    else{
        if(x==')'||x==']') {
          for(e=')';e!='('||e!='[';){
          if(PopStack(p,e)!=0) return ERROR;
          p1=(Node *)malloc(sizeof(Node));
          p1->flag=0;
          p1->prior=Np;
          p1->ope=e;
          Np->next=p1;
          Np=p1;
        }
    }
    else if(Priority(x)>Priority(p->Ops[p->top])){   //当前运算符优先级大则压栈
         if(PushStack(p,x)!=0)  return ERROR;
    }
    }  
    return 0; 
}

//将带分数/整数/真分数字符串转化为数字结构体
Frac inputFrac(char *exp,int *ip){
    int i=0,j,k,sum;
    int count=0,str[6];
    Frac num;
    while(1){
    if(exp[i]=='\''||exp[i]=='/'||exp[i]==' '||exp[i]==')'||exp[i]==']'){
                for(j=0;j<count;j++)
                   for(k=count-1-j;k>0;k--){      //乘以k次10
                       str[j]*=10;
                   }
                for(j=0,sum=0;j<count;j++)   
                   sum+=str[j];
                if(exp[i]=='\'') {
                    num.Integer=sum;
                    count=j=0;
                  }
                else {
                      if(exp[i]=='/') {
                      num.Nume=sum;
                      count=j=0;
                      }
                      else
                      {
                        num.Deno=sum;
                        break;         //一个数扫描结束
                      }
                    } 
                     
              }
    else {
               str[j]=exp[i];
               count++; j++;  
    }
               
               i++;*ip++;    
    }  
    return num;
}

//将exp所指向的一行字符串数组里的一条中缀表达式转化为逆波兰表达式 存到L里
Link CreateLink(point exp){
    Node *p1,*head,*p;
    head=(Node *)malloc(sizeof(Node));
    head->prior=NULL;
    head->num.Deno=1;
    head->num.Nume=head->num.Integer=0;
    int first=1;
    int i,count=0,j,k,sum,str[6];
    int *ip=&i;   //第i个字符
    Frac num;
    Stack *S=CreateStack();
      count=0;
      for(i=1;*exp[i]!='\0';i++){ 
        if(*exp[i]<'0'||*exp[i]>'9'){   //如果字符是运算符
         PutO(S,*exp[i],p);
         i++;
        }
         else
        {   
        if(first==1){                //如果是第一个出现的运算数 
        head->flag=1;
        while(1){                         
              if(*exp[i]=='\''||*exp[i]=='/'||*exp[i]==' '||*exp[i]==')'||*exp[i]==']'){
                for(j=0;j<count;j++)
                   for(k=count-1-j;k>0;k--){      //乘以k次10
                       str[j]*=10;
                   }
                for(j=0,sum=0;j<count;j++)   
                   sum+=str[j];
                if(*exp[i]=='\'') {
                    head->num.Integer=sum;
                    count=j=0;
                }
                else {
                      if(*exp[i]=='/') {
                        head->num.Nume=sum;
                        count=j=0;
                      }
                      else
                      {
                        head->num.Deno=sum;
                        first=0;
                        p=head; 
                        break;         //第一个数扫描结束
                      }
                    } 
                     
              }
              else {
                  str[j]=*exp[i];  
                  count++;j++;
                  }
               i++;                
          } }
          else{
          p1=(Node *)malloc(sizeof(Node));
          num=inputFrac(*exp[i],ip);
          p->next=p1;
          p1->prior=p;
          p=p1;
          p->flag=1;
          p->num.Deno=num.Deno;
          p->num.Nume=num.Nume;
          p->num.Integer=num.Integer;
          }
          
       }
    }
    p->next=NULL;
  return head;
}



//最大公约数
int GCD(int a,int b){
    int temp,r;
    if(a<b){
      temp=b;
      b=a;
      a=temp; 
    }
    while(b){
        r=a%b;
        a=b;
        b=r;   
    }
    return a;
}

int LCM(int a,int b){
    int x,r;
    r=GCD(a,b);
    x=a*b/r;
    return x;
}

Frac StepCal(NumStack *p,char Opera,point2 *str1,int i,int j,int *mp,int *del){ 
    Frac left,right;
    Frac result;
    int a,b,c,d,e,f;
    int k,l;
    int lcm,gcd;
    int str[3][10];
    if(!PopNStack(p,&right)&&!PopNStack(p,&left)){
       a=left.Nume;      //左操作数的分子
       b=left.Deno;      //左操作数的分母 
       c=left.Integer;
       d=right.Nume;
       e=right.Deno;
       f=right.Integer;
       a=b*c+a;         
       d=e*f+d;  
       lcm=LCM(b,e);
       a=a*(lcm/b);
       b=lcm;
       d=d*(lcm/e);     //通分  分母为最小公倍数
      switch (Opera)
      {
      case '+':
          {          
            result.Integer=(a+d)/lcm;
            a=(a+d)%lcm;
            gcd=GCD(a,lcm);
            a=a/gcd;
            b=b/gcd;
            result.Nume=a;
            result.Deno=b;
            *(*(str1[i]+j)+0)=left.Integer;
            *(*(str1[i]+j)+1)=left.Nume;
            *(*(str1[i]+j)+2)=left.Deno;
            *(*(str1[i]+j)+3)=Opera;
            *(*(str1[i]+j)+4)=right.Integer;
            *(*(str1[i]+j)+5)=right.Nume;
            *(*(str1[i]+j)+6)=right.Deno;
            *(*(str1[i]+j)+7)=result.Integer;
            *(*(str1[i]+j)+8)=result.Nume;
            *(*(str1[i]+j)+9)=result.Deno;
            return result;
            break;
          }
      case '-':{
          if(d>a){
            result.Integer=(d-a)/lcm;
            a=(d-a)%lcm;
            gcd=GCD(a,lcm);
            a=a/gcd;
            b=b/gcd;
            result.Nume=a;
            result.Deno=b;
            *(*(str1[i]+0)+0)=right.Integer;    //这一个步骤将在交换操作数后 替换原题目
            *(*(str1[i]+0)+1)=right.Nume;
            *(*(str1[i]+0)+2)=right.Deno;
            *(*(str1[i]+0)+3)=Opera;
            *(*(str1[i]+0)+4)=left.Integer;
            *(*(str1[i]+0)+5)=left.Nume;
            *(*(str1[i]+0)+6)=left.Deno;
            *(*(str1[i]+0)+7)=result.Integer;
            *(*(str1[i]+0)+8)=result.Nume;
            *(*(str1[i]+0)+9)=result.Deno;
            for(k=1;k<3;k++)
                for(l=0;l<10;l++){         //抹去除了第一步外的步骤
                    *(*(str1[i]+k)+l)=0;    
                }
            del[(*mp)++]=i;     //存错误的题目号
            return result;
          }
          else {
            result.Integer=(a-d)/lcm;
            a=(a-d)%lcm;
            gcd=GCD(a,lcm);
            a=a/gcd;
            b=b/gcd;
            result.Nume=a;
            result.Deno=b;
            *(*(str1[i]+j)+0)=left.Integer;
            *(*(str1[i]+j)+1)=left.Nume;
            *(*(str1[i]+j)+2)=left.Deno;
            *(*(str1[i]+j)+3)=Opera;
            *(*(str1[i]+j)+4)=right.Integer;
            *(*(str1[i]+j)+5)=right.Nume;
            *(*(str1[i]+j)+6)=right.Deno;
            *(*(str1[i]+j)+7)=result.Integer;
            *(*(str1[i]+j)+8)=result.Nume;
            *(*(str1[i]+j)+9)=result.Deno;
            return result;
           }
           break;
      } 
      case '*':{
          a=a*d;
          b=lcm*lcm;
          gcd=GCD(a,b);
          a=a/gcd;
          b=b/gcd;
          result.Nume=a;
          result.Deno=b;
          *(*(str1[i]+j)+0)=left.Integer;
          *(*(str1[i]+j)+1)=left.Nume;
          *(*(str1[i]+j)+2)=left.Deno;
          *(*(str1[i]+j)+3)=Opera;
          *(*(str1[i]+j)+4)=right.Integer;
          *(*(str1[i]+j)+5)=right.Nume;
          *(*(str1[i]+j)+6)=right.Deno;
          *(*(str1[i]+j)+7)=result.Integer;
          *(*(str1[i]+j)+8)=result.Nume;
          *(*(str1[i]+j)+9)=result.Deno;
          return result;
          break;
          }
      case '/':{
          if(a>=d){
              gcd=GCD(a,d);
              a=a/gcd;
              d=d/gcd;
              result.Integer=0;
              result.Nume=d;
              result.Deno=a;
            *(*(str1[i]+0)+0)=right.Integer;    //这一个步骤将在交换操作数后 替换原题目
            *(*(str1[i]+0)+1)=right.Nume;
            *(*(str1[i]+0)+2)=right.Deno;
            *(*(str1[i]+0)+3)=Opera;
            *(*(str1[i]+0)+4)=left.Integer;
            *(*(str1[i]+0)+5)=left.Nume;
            *(*(str1[i]+0)+6)=left.Deno;
            *(*(str1[i]+0)+7)=result.Integer;
            *(*(str1[i]+0)+8)=result.Nume;
            *(*(str1[i]+0)+9)=result.Deno;
              for(k=1;k<3;k++)
                for(l=0;l<10;l++){         //抹去除了第一步外的步骤
                    *(*(str1[i]+k)+l)=0;    
                }
            del[(*mp)++]=i;     //存错误的题目号   
            return result;          
          }
          else {
            gcd=GCD(a,d);
            a=a/gcd;
            d=d/gcd;
            result.Integer=0;
            result.Nume=d;
            result.Deno=a;
            *(*(str1[i]+j)+0)=left.Integer;
            *(*(str1[i]+j)+1)=left.Nume;
            *(*(str1[i]+j)+2)=left.Deno;
            *(*(str1[i]+j)+3)=Opera;
            *(*(str1[i]+j)+4)=right.Integer;
            *(*(str1[i]+j)+5)=right.Nume;
            *(*(str1[i]+j)+6)=right.Deno;
            *(*(str1[i]+j)+7)=result.Integer;
            *(*(str1[i]+j)+8)=result.Nume;
            *(*(str1[i]+j)+9)=result.Deno;
            return result;              
          }
            break;
      }
          default:exit(-1);
          break;
      }
    }
}

//计算逆波兰表达式 返回每一个表达式的计算步骤和步骤结果
int calculate(Link L,int n,int i,int *mp,point2 *step1,int *del,Frac *Ans){  //m为错误题目数-1
    Frac number;
    char ope;
    int flag=*mp,j=0;      //第i+!个题目里的第j个步骤
    Node *Np,*p1;
    point2 *str1=step1;
    str1=(point2 *)malloc(n*3*sizeof(point2));
    NumStack *p=(NumStack *)malloc(sizeof(NumStack));
    for(Np=L,p1=Np->next;Np->next!=NULL;p1=Np->next){
           if(Np->flag) PushNStack(p,Np->num);
                Np=p1;
           if(!Np->flag){              //当前所指为操作符
               number=StepCal(p,Np->ope,str1,i,j,mp,del);
               if(flag+1==*mp){         //题目不合要求 错题数增加
                    *(Ans+i)=number;
                    free(L);
                    break;
               } 
               if(PushNStack(p,number)==0)
                 Np=p1;
               else
                   exit(-1);         
           } 
           j++;
        }
        free(p);free(p1);
    }
 

//由原temp.txt.和待删除的题目号数组、新得到的题目  更新为temp2

int updateEven(int *del,point2 *step,int *mp,int *n){
    char expData[70]={0};
    int i,j,flag=0;    //flag为0表示当前待扫描行不是待覆盖的
    FILE *fp=fopen("temp.txt","r");
    FILE *fpw=fopen("temp2.txt","w");
    if(fp==NULL||fpw==NULL) return -1;
    for(i=0;i<*n;i++){
      flag=0;  
      for(j=0;j<*mp;j++)
        if(del[j]==i) flag=1;
      fgets(expData,70,fp);   
      if(!flag) {
          fputs(expData,fpw);
      } 
      else {
          if(*(*step[i*3]+0)==0){        //左操作数为0或真分数
              if(*(*step[i*3]+1)==0)
                 fprintf(fpw,"0 %c ",*(*step[i*3]+3));
               else
                fprintf(fpw,"%d/%d %c ",*(*step[i*3]+1),*(*step[i*3]+2),*(*step[i*3]+3));                 
          }
           if(!(*(*step[i*3]+1))&&(*(*step[i*3]+0)))     //左操作数为整数但不为0
                fprintf(fpw,"%d %c ",*(*step[i*3]+0),*(*step[i*3]+3));
           if((*(*step[i*3]+0))&&(*(*step[i*3]+1))) 
                fprintf(fpw,"%d'%d/%d %c ",*(*step[i*3]+0),*(*step[i*3]+1),*(*step[i*3]+2),*(*step[i*3]+3));
            
            if(*(*step[i*3]+4)==0){        //右操作数为0或真分数
              if(*(*step[i*3]+5)==0)
                 fprintf(fpw,"%d\n",*(*step[i*3]+4));
               else
                fprintf(fpw,"%d/%d\n",*(*step[i*3]+5),*(*step[i*3]+6));                 
          }
           if(!(*(*step[i*3]+5))&&(*(*step[i*3]+4)))     //右操作数为整数但不为0
                fprintf(fpw,"%d\n",*(*step[i*3]+4));
           if((*(*step[i*3]+4))&&(*(*step[i*3]+5))) 
                fprintf(fpw,"%d'%d/%d\n",*(*step[i*3]+4),*(*step[i*3]+5),*(*step[i*3]+6));    
      }
    }
    *mp=0;
    fclose(fp);
    fclose(fpw);
    return 0;
}

int updateOdd(int *del,point2 *step1,int *mp,int *n){
    char expData[70]={0};
    int i,j,flag=0;    //flag为0表示当前待扫描行不是待覆盖的
    FILE *fp=fopen("temp.txt","r");
    FILE *fpw=fopen("temp1.txt","w");
    if(fp==NULL||fpw==NULL) return -1;
    for(i=0;i<*n;i++){
      flag=0;  
      for(j=0;j<*mp;j++)
        if(del[j]==i) flag=1;
      fgets(expData,70,fp);   
      if(!flag) {
          fputs(expData,fpw);
      } 
      else {
          if(*(*step1[i*3]+0)==0){        //左操作数为0或真分数
              if(*(*step1[i*3]+1)==0)
                 fprintf(fpw,"0 %c ",*(*step1[i*3]+3));
               else
                fprintf(fpw,"%d/%d %c ",*(*step1[i*3]+1),*(*step1[i*3]+2),*(*step1[i*3]+3));                 
          }
           if(!(*(*step1[i*3]+1))&&(*(*step1[i*3]+0)))     //左操作数为整数但不为0
                fprintf(fpw,"%d %c ",*(*step1[i*3]+0),*(*step1[i*3]+3));
           if((*(*step1[i*3]+0))&&(*(*step1[i*3]+1))) 
                fprintf(fpw,"%d'%d/%d %c ",*(*step1[i*3]+0),*(*step1[i*3]+1),*(*step1[i*3]+2),*(*step1[i*3]+3));
            
            if(*(*step1[i*3]+4)==0){        //右操作数为0或真分数
              if(*(*step1[i*3]+5)==0)
                 fprintf(fpw,"%d\n",*(*step1[i*3]+4));
               else
                fprintf(fpw,"%d/%d\n",*(*step1[i*3]+5),*(*step1[i*3]+6));                 
          }
           if(!(*(*step1[i*3]+5))&&(*(*step1[i*3]+4)))     //右操作数为整数但不为0
                fprintf(fpw,"%d\n",*(*step1[i*3]+4));
           if((*(*step1[i*3]+4))&&(*(*step1[i*3]+5))) 
                fprintf(fpw,"%d'%d/%d\n",*(*step1[i*3]+4),*(*step1[i*3]+5),*(*step1[i*3]+6));    
      }
    }
    *mp=0;
    fclose(fp);
    fclose(fpw);
    return 0;
}

int  repeatEven(int n,Frac Ans[n],Frac Ans1[n],point2 step[n],point2 step1[n]){
    int count,i,j,l,k;  
    Order order[n];
    int a,b;
    char expData[70]={0};
    FILE *fp=fopen("temp2.txt","r");
    FILE *fpw=fopen("temp1.txt","w");
    for(i=0;i<n;i++) {
        order[i].number=i;
        order[i].flag=0;
    }
    for(i=0;i<n;i++)
       for(j=i+1;j<n;j++){
           if((Ans[j].Deno==Ans[i].Deno)&&(Ans[i].Nume==Ans[j].Nume)&&(Ans[i].Integer==Ans[j].Integer)){
               for(k=0;k<3;k++){
                   if((*(*step[i]+7)==*(*step[j]+7))&&(*(*step[i]+8)==*(*step[j]+8))&&(*(*step[i]+9)==*(*step[j]+9))){
                        if((*(*step[i]+3)==*(*step[j]+3))){
                             if(((*(*step[i]+0)==*(*step[j]+0))&&(*(*step[i]+1)==*(*step[j]+1))&&(*(*step[i]+2)==*(*step[j]+2)))||
                                ((*(*step[i]+0)==*(*step[j]+4))&&(*(*step[i]+1)==*(*step[j]+5))&&(*(*step[i]+2)==*(*step[j]+6)))){
                                order[j].flag=1;        //第j道题与第i题重复  要删
                                count ++;
                                }
                             else break;   
                        } 
                        else break;       
                   }
                   else break;
               }                   
           }
           else break;
       }  
       for(i=0;i<n;i++){
           fgets(expData,70,fp);
           if(!order[i].flag) 
             fprintf(fpw,"%s\n",expData);
       }  
       fclose(fp);fclose(fpw);
       for(j=0,i=0;i<n;i++){                              //把main里的Ans1里不该删除的答案整合到Ans  并初始化Ans1
           if(order[i].flag) continue;
           Ans1[j++]=Ans[i];
           Ans[i].Deno=Ans[i].Integer=Ans[i].Nume=0;    //初始化
       }
       for(j=0,i=0;i<n;i++){           //把step1整合到step
           k=0;
           if(order[i].flag){
               while (k<3)
               {
                for(l=0;l<10;l++)      
                 *(*step1[i*3]+l)=0;              
                 k++;
                 i++;
               }
               
           }
           while (k<3)
           {    
               for(l=0;l<10;l++){
               *(*step[j*3]+l)=*(*step1[i*3]+l);
               *(*step1[i*3]+l)=0;
               }
               k++;
               j++;i++;
           }
           
       }
       return count;          
}

int  repeatOdd(int n,Frac Ans[n],Frac Ans1[n],point2 step1[n],point2 step[n]){
    int count,i,j,l,k;  
    Order order[n];
    int a,b;
    char expData[70]={0};
    FILE *fp=fopen("temp1.txt","r");
    FILE *fpw=fopen("temp2.txt","w");
    for(i=0;i<n;i++) {
        order[i].number=i;
        order[i].flag=0;
    }
    for(i=0;i<n;i++)
       for(j=i+1;j<n;j++){
           if((Ans[j].Deno==Ans[i].Deno)&&(Ans[i].Nume==Ans[j].Nume)&&(Ans[i].Integer==Ans[j].Integer)){
               for(k=0;k<3;k++){
                   if((*(*step[i]+7)==*(*step[j]+7))&&(*(*step[i]+8)==*(*step[j]+8))&&(*(*step[i]+9)==*(*step[j]+9))){
                        if((*(*step[i]+3)==*(*step[j]+3))){
                             if(((*(*step[i]+0)==*(*step[j]+0))&&(*(*step[i]+1)==*(*step[j]+1))&&(*(*step[i]+2)==*(*step[j]+2)))||
                                ((*(*step[i]+0)==*(*step[j]+4))&&(*(*step[i]+1)==*(*step[j]+5))&&(*(*step[i]+2)==*(*step[j]+6)))){
                                order[j].flag=1;        //第j道题与第i题重复  要删
                                count ++;
                                }
                             else break;   
                        } 
                        else break;       
                   }
                   else break;
               }                   
           }
           else break;
       }  
       for(i=0;i<n;i++){
           fgets(expData,70,fp);
           if(!order[i].flag) 
             fprintf(fpw,"%s\n",expData);
       }  
       fclose(fp);fclose(fpw);
       for(j=0,i=0;i<n;i++){                              //把main里的Ans1里不该删除的答案整合到Ans  并初始化Ans1
           if(order[i].flag) continue;
           Ans1[j++]=Ans[i];
           Ans[i].Deno=Ans[i].Integer=Ans[i].Nume=0;    //初始化
       }
       for(j=0,i=0;i<n;i++){           //把step1整合到step
           k=0;
           if(order[i].flag){
               while (k<3)
               {
                for(l=0;l<10;l++)      
                 *(*step1[i*3]+l)=0;              
                 k++;
                 i++;
               }
               
           }
           while (k<3)
           {    
               for(l=0;l<10;l++){
               *(*step[j*3]+l)=*(*step1[i*3]+l);
               *(*step1[i*3]+l)=0;
               }
               k++;
               j++;i++;
           }
           
       }
       return count;          
}

int plusEven(int n,int N,Frac Ans[N],Frac Ans1[N],point2 step[N],point2 step1[N]){
   int j,i,k,l;
    for(j=N-n,i=0;i<n;i++){                              //把main里的Ans1里不该删除的答案整合到Ans  并初始化Ans1
           Ans[j++]=Ans1[i];
           Ans1[i].Deno=Ans1[i].Integer=Ans1[i].Nume=0;    //初始化
       }
    for(j=N-n,i=0;i<n;i++){           //把step1新生成的 整合到step
           k=0;
           while (k<3)
           {    
               for(l=0;l<10;l++){
               *(*step[j*3]+l)=*(*step1[i*3]+l);
               *(*step1[i*3]+l)=0;
               }
               k++;
               j++;i++;
           }
           
       }
    FILE *fp=fopen("temp2.txt","r");
    FILE *fpw=fopen("temp1.txt","a");
    char expData[70]={0};
    for(i=0;i<n;i++){
        fgets(expData,70,fp);
        fprintf(fpw,"%s\n",expData);
    }   
    fclose(fp);fclose(fpw);
    return 0;   
}

int plusOdd(int n,int N,Frac Ans1[N],Frac Ans[N],point2 step1[N],point2 step[N]){
   int j,i,k,l;
    for(j=N-n,i=0;i<n;i++){                              //把main里的Ans1里不该删除的答案整合到Ans  并初始化Ans1
           Ans[j++]=Ans1[i];
           Ans1[i].Deno=Ans1[i].Integer=Ans1[i].Nume=0;    //初始化
       }
    for(j=N-n,i=0;i<n;i++){           //把step1新生成的 整合到step
           k=0;
           while (k<3)
           {    
               for(l=0;l<10;l++){
               *(*step[j*3]+l)=*(*step1[i*3]+l);
               *(*step1[i*3]+l)=0;
               }
               k++;
               j++;i++;
           }
           
       }
    FILE *fp=fopen("temp1.txt","r");
    FILE *fpw=fopen("temp2.txt","a");
    char expData[70]={0};
    for(i=0;i<n;i++){
        fgets(expData,70,fp);
        fprintf(fpw,"%s\n",expData);
    }   
    fclose(fp);fclose(fpw);
    return 0;   
}

int main(int argc, char* argv[]){
    int n,N,i,m=0,del[n],k=0,flag=1,time=1;
    Frac *Ans,*Ans1;
    Link L;
    char linedata[71]={0};
    int num ;     // 生成的题目数量
	char* problem = NULL;  // 字符指针，指向生成的题目
	FILE* fp = NULL;//检查并解析参数
	if (argc != 5 || strcmp(argv[1], "-r") != 0 || strcmp(argv[3], "-n") != 0)
		printf("命令输入错误！\n 请参照以下格式输入：D:\\prj\\Test\\Debug Calculator.exe -n 10 -r 10");

	range = atoi(argv[2]);
	num = atoi(argv[4]);
		printf("请输入范围 题数：%d %d\n",range, num);
	N=num;
    int count = 0;
	while (count < num)  // 未达到指定生成数量，继续生成
	{
		problem = GeneratePro();
		// 将题目写入文件
		if(count == 0)
		fopen_s(&fp,"D:/prj/Calculator/Debug/temp.txt", "w+");
		fseek(fp, 0, SEEK_END);    // 把文件指针定位到文件末尾
		fputs(problem, fp);
		fputs("\n", fp);
		printf("the problem is: ");
		puts(problem);
		count++;	
	}
    fclose(fp); 
    n=num;
    Ans=(Frac *)malloc(n*sizeof(Frac));
    Ans1=(Frac *)malloc(n*sizeof(Frac));
    int step[n][10],step1[n][10];
    point exp=Store(n);      //把temp.txt里的题目存在字符串数组exp中
    for(i=0;i<=n;i++){
    L=CreateLink(exp+i);
    if(calculate(L,n,i,&m,step1,del,Ans1))    //m为错题数 
       exit(-1); 
    }
    updateEven(del,step1,&m,&n);      //替换错题 得temp2.txt
    while(flag){                    //当没有重复的题目时 flag为0  跳出循环  
        if (time%2){     
        num=repeatEven(N,Ans1,Ans,step,step1);
        plusEven(n,N,Ans,Ans1,step,step1);
        for(count=0;count<num;){
        problem = GeneratePro();
		// 将题目写入文件
		if(count == 0)
		fopen_s(&fp,"D:/prj/Calculator/Debug/temp.txt", "w+");
		fseek(fp, 0, SEEK_END);    // 把文件指针定位到文件末尾
		fputs(problem, fp);
		fputs("\n", fp);
		printf("the problem is: ");
		puts(problem);
		count++;	
        }
        n=num;
        if(!n) break;
        for(i=0;i<n;i++){        
        }
        exp=Store(n);      //把temp.txt里的题目存在字符串数组exp中
        for(i=0;i<=n;i++){
        L=CreateLink(exp+i);
        if(calculate(L,n,i,&m,step1,del,Ans1))
        exit(-1); 
    }
    updateEven(del,step1,&m,&n); 
    plusEven(n,N,Ans,Ans1,step,step1);
    time++;
    }
    else {     
        num=repeatOdd(N,Ans,Ans1,step1,step);
        plusOdd(n,N,Ans1,Ans,step1,step);
        for(count=0;count<num;){
        problem = GeneratePro();
		// 将题目写入文件
		if(count == 0)
		fopen_s(&fp,"D:/prj/Calculator/Debug/temp.txt", "w+");
		fseek(fp, 0, SEEK_END);    // 把文件指针定位到文件末尾
		fputs(problem, fp);
		fputs("\n", fp);
		printf("the problem is: ");
		puts(problem);
		count++;	
        }
        n=num;
        if(!0) break;
        for(i=0;i<n;i++){        
        }
        exp=Store(n);      //把temp.txt里的题目存在字符串数组exp中
        for(i=0;i<=n;i++){
        L=CreateLink(exp+i);
        if(calculate(L,n,i,&m,step,del,Ans))
        exit(-1); 
    }
    updateOdd(del,step,&m,&n); 
    plusOdd(n,N,Ans1,Ans,step1,step);
    time++;
    }
    }
    if(time%2) {    //查重了奇数次
    FILE *fpe=fopen("temp2.txt","r");
    FILE *fpew=fopen("Exercises.txt","w");
    FILE *fpaw=fopen("Answers.txt","w");
    for(i=0;i<N;i++){  
      fgets(linedata,71,fpe);
      fprintf(fpew,"%d. %s\n",i+1,linedata);
      if(Ans1[i].Nume==0)     //答案为整数
          fprintf(fpaw,"%d. %d\n",i+1,Ans1[i].Integer);
          else
          {
              if (Ans1[i].Integer==0)   //答案为真分数
               fprintf(fpaw,"%d. %d/%d\n",i+1,Ans1[i].Nume,Ans1[i].Deno);
              else
               fprintf(fpaw,"%d. %d'%d/%d\n",i+1,Ans1[i].Integer,Ans1[i].Nume,Ans1[i].Deno);  
          }
          
     }
     fclose(fpe);fclose(fpew);fclose(fpaw);
    }
    else{    //查重了偶数次
    FILE *fpe=fopen("temp1.txt","r");
    FILE *fpew=fopen("Exercises.txt","w");
    FILE *fpaw=fopen("Answers.txt","w");
    for(i=0;i<N;i++){  
      fgets(linedata,71,fpe);
      fprintf(fpew,"%d. %s\n",i+1,linedata);
      if(Ans[i].Nume==0)     //答案为整数
          fprintf(fpaw,"%d. %d\n",i+1,Ans[i].Integer);
          else
          {
              if (Ans[i].Integer==0)   //答案为真分数
               fprintf(fpaw,"%d. %d/%d\n",i+1,Ans[i].Nume,Ans[i].Deno);
              else
               fprintf(fpaw,"%d. %d'%d/%d\n",i+1,Ans[i].Integer,Ans[i].Nume,Ans[i].Deno);  
          }
          
     }
      fclose(fpe);fclose(fpew);fclose(fpaw);
    }
    return 0;
}  