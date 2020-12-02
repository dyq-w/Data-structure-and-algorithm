#include <iostream>

#include <cstdlib>

#include <ctime>

#include <iomanip>

#include <windows.h>

#include <fstream>

using namespace std;

#define  MAXSIZE 30 //100、1000

typedef int ElemType;

typedef struct

{
    ElemType* r;

    int  length;

}SqList;

//函数的声明
void Create_Sq(SqList& L);

void InsertSort(SqList& L);

void BInsertSort(SqList& L);

void ShellSort(SqList& L);

void ShellInsert(SqList& L, int  dk);

void BubbleSort(SqList& L);

void QSort(SqList& L, int low, int high);

int Partition(SqList& L, int low, int high);

void SelectSort(SqList& L);

void HeapSort(SqList& L);

void CreatHeap(SqList& L);

void HeapAdjust(SqList& L, int s, int m);

//建立待排序列，写入文件

void Create_Sq(SqList & L)

{

    int i;

    ofstream outFile("排序时间_段永强.txt", ios::out);

    srand(unsigned(time(NULL)));

    for (i = 1; i < MAXSIZE + 1; i++)

    {//调用随机函数生成待排关键字。

        L.r[i] = rand() * rand() % 2033;//自己调整除数

        outFile << L.r[i] << '\t';

    }

    L.length = MAXSIZE;

    cout << "随机数生成完毕！" << endl;

}//Create_Sq

//显示排序表

void show(SqList L)

{
    int i;

    for (i = 1; i <= L.length; i++)

        cout << left << L.r[i] << '\t';//控制输出格式

    cout << endl;

}//show

//直接插入排序

void InsertSort(SqList & L)

{

    int i, j;

    for (i = 2; i <= L.length; ++i)

        if (L.r[i] < L.r[i - 1])

        {

            L.r[0] = L.r[i];
            L.r[i] = L.r[i - 1];
            for ( j = i - 2; L.r[0] < L.r[j]; --j)
                L.r[j + 1] = L.r[j];
            L.r[j + 1] = L.r[0];

        }//if

}   //InsertSort
 
//折半插入排序

void BInsertSort(SqList & L) {

    int i, j, low, high, m;

    for (i = 2; i <= L.length; ++i)

    {

        L.r[0] = L.r[i];

        low = 1; high = i - 1;

        while (low <= high)

        {
            m = (low + high) / 2;
            if (L.r[0] < L.r[m]) high = m - 1;
            else low = m + 1;

        }//while

        for ( j = i - 1; j >= high + 1; --j)

            L.r[j + 1] = L.r[j];

        L.r[high + 1] = L.r[0];

    }
}

//一趟希尔插入排序

void ShellInsert(SqList & L, int dk)

{

    int i, j;

    for (i = dk + 1; i <= L.length; ++i)

        if (L.r[i] < L.r[i - dk])

        {
         
            L.r[0] = L.r[i];
            for (j = i - dk; j > 0 && L.r[0] < L.r[j]; j -= dk)
                L.r[j + dk] = L.r[j];
            L.r[j + dk] = L.r[0];

        }

}//ShellInsert

//冒泡排序

void BubbleSort(SqList & L)

{

    int m, j, flag;

    ElemType t;

    m = L.length - 1; flag = 1;

    while ((m > 0) && (flag == 1))

    {

        flag = 0;
        for(j =1;j<=m;j++)
            if (L.r[j] > L.r[j + 1]) {
                flag = 1;
                t = L.r[j]; L.r[j] = L.r[j + 1]; L.r[j + 1] = t;
            }
        --m;
    }  //while

}   //BubbleSort

//一趟快速排序

int Partition(SqList & L, int low, int high)

{

    int pivotkey;

    L.r[0] = L.r[low];

    pivotkey = L.r[low];

    while (low < high)

    {
        while (low < high && L.r[high] >= pivotkey) --high;
        L.r[low] = L.r[high];
        while (low < high && L.r[low] <= pivotkey) ++low;
        L.r[high] = L.r[low];

    }//while

    L.r[low] = L.r[0];//枢轴记录到位

    return  low;

}//Partition

//快速排序

void QSort(SqList & L, int low, int high)

{

    int pivotloc;

    if (low < high)

    {

        pivotloc = Partition(L, low, high);
        QSort(L, low, pivotloc - 1);
        QSort(L, pivotloc + 1, high);

    }

}//QSort

//简单选择排序

void SelectSort(SqList & L)

{

    int i, j, k;

    ElemType t;

    for (i = 1; i < L.length; ++i)

    {
        k = i;
        for(j = i+1;j<=L.length;++j)
            if (L.r[j] < L.r[k]) k = j;
        if (k != i) {
            t = L.r[i]; L.r[i] = L.r[k]; L.r[k] = t;
        }
    }//for

}   //SelectSort

// 筛选法调整堆
void HeapAdjust(SqList & L, int s, int m)

{
    ElemType rc;

    int j;

    rc = L.r[s];

    for (j = 2 * s; j <= m; j *= 2)

    {
        if (j < m && L.r[j] < L.r[j + 1]) ++j;
        if (rc >= L.r[j]) break;
        L.r[s] = L.r[j];
        s = j;

    }

    L.r[s] = rc;

}//HeapAdjust

// 建初堆

void CreatHeap(SqList & L)

{

    int i, n;

    n = L.length;

    for (i = n / 2; i > 0; --i)    HeapAdjust(L, i, n);

}  //CreatHeap

int main()

{

    SqList L, Q;    int choose;

    LARGE_INTEGER  start, finish, freq;//CPU计时器的开始、结束和频率

    ofstream outFile("排序时间_段永强.txt", ios::out);//创建你的输出文件 

    for (;;)

    {

        cout << "选择操作:1生成随机关键字 2直接插入排序  3折半插入排序  4希尔排序  \n 5冒泡排序  6快速排序  7简单选择排序  8堆排序   0退出"<<endl;

            cin >> choose;

        switch (choose)

        {

        case 1:

            L.r = new ElemType[MAXSIZE + 1];

            L.length = 0;

            Create_Sq(L);

            show(L);

            break;

        case 2://直接插入排序

            Q = L;//复制新表Q对其进行排序

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            InsertSort(Q);

            QueryPerformanceCounter(&finish);

            cout << endl << "直接插入排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 直接插入排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 3://折半插入排序

            Q = L;

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            BInsertSort(Q);

            QueryPerformanceCounter(&finish);

            cout << endl << "折半插入排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 折半插入排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 4://k趟希尔排序

            Q = L;

            int* dt, i, t, k;

            cout << "输入增量个数：" << endl;

            cin >> t;

            cout << "输入增量序列：" << endl;

            dt = new int[10];//增量数组dt的长度不超过10

            for (i = 0; i < t; i++)

                cin>>dt[i];

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            for (k = 0; k < t; ++k)

                ShellInsert(Q,dt[k]);

            QueryPerformanceCounter(&finish);

            cout << endl << "希尔排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 希尔插入排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 5:

            Q = L;

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            BubbleSort(Q);

            QueryPerformanceCounter(&finish);

            cout << endl << "冒泡排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 冒泡排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 6:

            Q = L;

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            QSort(Q,1,Q.length);

            QueryPerformanceCounter(&finish);

            cout << endl << "快速排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 快速排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 7:

            Q = L;

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            SelectSort(Q);

            QueryPerformanceCounter(&finish);

            cout << endl << "简单选择排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 简单选择排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;

        case 8://堆排序

            Q = L; ElemType x;

            CreatHeap(Q);

            QueryPerformanceFrequency(&freq);

            QueryPerformanceCounter(&start);

            for (i = Q.length; i > 1; --i)

            {//将Q.r[1..i-1]重新调整为大根堆

                x = Q.r[1];

                Q.r[1] = Q.r[i];

                Q.r[i] = x;

                HeapAdjust(Q,1,i-1);

            }//for

            QueryPerformanceCounter(&finish);

            cout << endl << "堆排序的结果是：" << endl;

            show(Q);

            outFile << endl << " 堆排序 " << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << "   " << endl;

            cout << "时间为：" << (double)(finish.QuadPart - start.QuadPart) / freq.QuadPart << endl;

            break;


        case 0:

            exit(0);

        }

    }//for

    outFile.close();

    return 0;


}
