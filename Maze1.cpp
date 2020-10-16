#include<iostream>
using namespace std;

#define MaxSize 9999
#define M 8
#define N 8



int mg[10][10] =
{
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,1,0,0,0,1,0,1},
    {1,0,0,0,0,1,1,0,0,1},
    {1,0,1,1,1,0,0,0,0,1},
    {1,0,0,0,1,0,0,0,0,1},
    {1,0,1,0,0,0,1,0,0,1},
    {1,0,1,1,1,0,1,1,0,1},
    {1,1,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};


typedef struct
{
    int i,j;     //方块的位置
    int pre;     //本路径中上一方块在队列中的下标
}Box;
typedef struct
{
    Box data[MaxSize];
    int front,rear;      //队头指针和队尾指针
}QuType;

int print(QuType qu,int a)
{
    int result[MaxSize],p=0,q=0;
    while(a!=-1)
    {
        result[p++]=a;
        a=qu.data[a].pre;
    }

    while(--p>=0)
    {
         printf("\t(%d,%d)",qu.data[result[p]].i,qu.data[result[p]].j);
         if(p%3==0)
            printf("\n");
    }
    return 0;
}


bool mgpath1(int xi,int yi,int xe,int ye)
//搜索路径为：(xi,yi)->(xe,ye)
{
    int i,j,find = 0,di;
    QuType qu;
    qu.front = qu.rear = -1;
    qu.rear++;
    qu.data[qu.rear].i=xi;qu.data[qu.rear].j=yi;
    qu.data[qu.rear].pre = -1;
    mg[xi][yi]=-1; //避免重复搜索

    while(qu.front!=qu.rear && !find)
    {
        qu.front++;
        i=qu.data[qu.front].i;j=qu.data[qu.front].j;
        if(i==xe&&j==ye)
        {
            find = 1;
            printf("迷宫路径如下：\n");
            print(qu,qu.front);
            return true;
        }

        for(di =0;di<4;di++)
        {
            switch(di)
            {
                case 0: i=qu.data[qu.front].i-1;
                        j=qu.data[qu.front].j;break;
                case 1: i=qu.data[qu.front].i;
                        j=qu.data[qu.front].j+1;break;
                case 2:i=qu.data[qu.front].i+1;
                        j=qu.data[qu.front].j;break;
                case 3:i=qu.data[qu.front].i;
                        j=qu.data[qu.front].j-1;break;
            }
            if(mg[i][j]==0)
            {
                qu.rear++;
                qu.data[qu.rear].i = i;qu.data[qu.rear].j=j;
                qu.data[qu.rear].pre = qu.front; mg[i][j] = -1;
            }
        }
    }
    return false;
}

int main()
{
    if(!mgpath1(1,1,M,N))
        printf("没有途径！");
    return 0;
}
