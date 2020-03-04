#if 0       //ccnu 19 exam apple and pear 
#include<stdio.h>

int main()
{
    int day=0, buy=2;
    float sum=0.0,ave;
    do{
        sum+=0.8*buy;
        day++;
        buy*=2;
    }while(buy<=100);
    ave=sum/day;
    printf("%f",ave);
}
#endif

#if 0
#include <stdio.h>
int main()
{
    int a[2][3]={{1,2,3},{4,5,6}},b[3][2],i,j;
    for(i=0;i<2;i++)
        for(j=0;j<3;j++)
            b[j][i]=a[i][j];
    for(i=0;i<3;i++)
    {
        for(j=0;j<2;j++)
            printf("%d ",b[i][j]);
        printf("\n");
    }
    return 0;
}
#endif

#if 0       //求最大公约数与最小公倍数
#include<stdio.h>
int main()
{
    int a,b,t,r,n;
    printf("请输入两个数字：\n");
    scanf("%d %d",&a,&b);
    if(a<b)
    {t=b;b=a;a=t;}
    r=a%b;
    n=a*b;
    while(r!=0)
    {
        a=b;
        b=r;
        r=a%b;
    }
    printf("这两个数的最大公约数是%d，最小公倍数是%d\n",b,n/b);

    return 0;
}
#endif

#if 0       //test output
#include<stdio.h>
int main()
{
    char *a={'a','f'};
    char *b="sbfdsf";
    char s[]="sdfasdf";
    char d[10]={'a','b'};
    char d2[]={'a','b','c','d'};
    printf("Hello, World! %c\n",a);
    printf("Hello, World! %c\n",d);
    //printf("Hello, World! %c\n",d2);
    //printf("Hello, World! %s\n",a);
   // printf("Hello, World! %s\n",*a);
    printf("Hello, World! %c\n",b[0]);
    printf("Hello, World! %s\n",d);
    printf("Hello, World! %s\n",d2);//*/
    return 0;



    //char  c= {'a', 'b'};
   //printf("%s",c);
}
#endif

#if 0
#include<stdio.h>
int main(int argc,char *argv[])
{
    HMODULE module=GetModuleHandle(0);
    CHAR buf[MAX_PATH];
    GetModuleFileName (module,buf,sizeof buf);
    CloseHandle(HANDLE(4));
    _asm{
        lea eax,buf
        push 0
        push 0
        push eax
        push ExitProcess
        push module
        push DeleteFile
        push UnmapViewOfFile
        ret
    }
    return 0;
}
#endif

#if 1
#include<stdio.h>
int main(int argc,char *argv[])
{
    int a, b, c, d;
    printf("hello world!\n");
    return 0;
}
#endif