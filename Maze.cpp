#include<iostream>

using namespace std;

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
    int i;    //当前方块的行号
    int j;    //当前方块的列号
    int di;   //di是下一个可走相邻方位的方位号
}Box;

typedef struct
{
    Box data[99];
    int top;
}StType;

bool mgpath(int xi,int yi,int xe,int ye)    //(xi,yi)为入口，（xe,ye）为出口
{
    int i,j,k,di,find;
    StType st;st.top = -1;
    st.top++;
    st.data[st.top].i = xi;st.data[st.top].j = yi;
    st.data[st.top].di = -1;
    mg[xi][yi] = -1;


     while(st.top>-1)
    {
        i=st.data[st.top].i;j=st.data[st.top].j;
        di=st.data[st.top].di;
        if(i==xe&&j==ye)
        {
            printf("迷宫路径如下：\n");
            for(k=0;k<=st.top;k++)
            {
                printf("\t(%d,%d)",st.data[k].i,st.data[k].j);
                if((k+1)%5 == 0)
                    printf("\n");
            }
            printf("\n");
            return true;
        }

    find = 0;
    while(di<4&&find==0)
    {
        di++;
        switch(di)
        {
            case 0:i=st.data[st.top].i-1;j=st.data[st.top].j;
            break;
            case 1:i=st.data[st.top].i;j=st.data[st.top].j+1;
            break;
            case 2:i=st.data[st.top].i+1;j=st.data[st.top].j;
            break;
            case 3:i=st.data[st.top].i;j=st.data[st.top].j-1;
            break;
        }
        if(mg[i][j]==0) find=1;
    }
    if(find ==1)
    {
        st.data[st.top].di = di;
        st.top++;
        st.data[st.top].i=i;st.data[st.top].j=j;
        st.data[st.top].di=-1;
        mg[i][j]=-1;
    }else
    {
        mg[st.data[st.top].i][st.data[st.top].j] = 0;
        st.top--;
    }

  }
  return false;
}


int main()
{
    if(!mgpath(1,1,8,8))
        printf("该迷宫问题没有解！");
        return 0;
}
