#include<iostream>
using namespace std;
#include<cstdlib>
#include<ctime> //用时间做种子，生成随机数，本实验的关键字为整型
#include<algorithm> //为得到有序表调用了排序函数sort(begin,end)
#define MS 13  //取质数方便生成哈希表
typedef int ElemType;

typedef struct {
	ElemType* R;
	int length;
}SSTable;


int Creat_SSTable(SSTable & S, int range)

{//创建查找表S

    int i;

    srand(unsigned(time(NULL)));//指定随机数种子为系统时间，每次调用可以生成不同的随机数

    S.R = new ElemType[MS + 1];

    for (i = 1; i <= MS; i++)

    {//调用随机函数生成关键字,下标从1开始写入

        S.R[i] = rand() % range;//使随机数的大小落在0~range范围内

    }

    std::cout << "随机查找表生成完毕！" << endl;

    S.length = MS;

    return 0;

}//Create


void show(SSTable S)

{//打印查找表

    int i;

    for (i = 1; i <= S.length; i++)

        std::cout << S.R[i] << "\t";//逐个打印S的关键字

    std::cout << endl;

}


int Search_Seq(SSTable S1, int key)

{
    int i, cnt = 1;//cnt统计比较次数

    S1.R[0]=key;//待比较关键字入监视哨；

    for (i = S1.length ; S1.R[i] != key ; --i, cnt++);

    std::cout << "比较" << cnt << "次" << endl;

    return i;

}// Search_Seq

int Search_Bin(SSTable S2, int key)

{

    int low = 1, high = MS , mid;

    int  cnt = 1;

    while (low <= high) {

        mid = (low+high)/2;

        std::cout << cnt++ << "次查找，mid=" << mid << endl;

        if (S2.R[mid] == key)  return mid;		//找到待查元素

        else if (S2.R[mid] > key)  high = mid-1;	//在前一子表进行查找

        else low = mid +1;   //在后一子表进行查找

    }//while

    return 0;//表中不存在待查元素

}// Search_Bin

//定义哈希函数，创建哈希表

int Hash(int key)

{//除留余数法构造哈希函数Hash(key)

    int result;

    result = key % MS;//按表长计算地址

    return result;

}//Hash

int Creat_HashTable(SSTable S, SSTable& S3)

{//读取S的关键字，创建哈希表S3

    int i, cur_key, h0 = 0;

    S3.R = new ElemType[MS + 1];

    for (i = 0; i <= MS; i++)

        S3.R[i] = -1;//初始化哈希表，-1表示该单元未使用

    for (i = 1; i <= MS; i++)

    {//逐个读取S的元素写入哈希表S3

        cur_key = S.R[i];//读取S的当前关键字

        h0 = Hash(cur_key);//通过哈希函数得到当前关键字对应的哈希地址h0

        while ( S3.R[h0]> 0)//如果h0被占用,再哈希

        {

            ++h0;//线性探测法，探测下一个位置

            h0 = h0 % MS;

        }//再哈希

        S3.R[h0] = cur_key;//将当前关键字写入到哈希表的h0位置

        std::cout << "(" << h0 << ")" << S3.R[h0] << "\t";

    }

    return 0;

}//Creathashtable

int Search_Hash(SSTable S3, int key)

{//哈希查找

    int i, h0, cnt = 0;

    h0 = Hash(key);//计算

        if (S3.R[h0] == key) return h0;//找到

        else if (S3.R[h0] == -1) return -1;//h0下没有对应元素

        else

        {
            for (i = 1; S3.R[h0] != key && i < MS; i++)//冲突,再哈希

            {

                cnt++; std::cout << h0 << "冲突\t";

                h0 = (h0 + i) % MS;

            }//再哈希

            std::cout << "\n比较次数为" << cnt;

            return h0;//最终位置

        }

    return -1;

}

//主函数测试

int main() {

    SSTable S, S1, S2, S3;//S1,S2用于顺序查找和折半查找

    int x, pos, range, choose = -1; //x是用户输入的关键字，pos是折半查找的结果，range是关键字范围

        while (choose != 0) {

            cout << '\n' << "1 创建查找表  2 顺序查找  3折半查找  4 创建哈希表 5 哈希查找 0退出：" << endl;

            cin >>choose;//输入选项

            switch (choose) {

            case 1://随机生成查找表S

                cout << "随机生成查找表，输入随机数的模(如17、107、1007，视关键字位数而定）" << endl;

                cin >> range;

                Creat_SSTable(S, range);//创建查找表S

                show(S);//打印S

                break;

            case 2://顺序查找

                S1 = S;//复制S得到S1

                cout << "输入待查关键字：";

                cin >> x;

                pos = Search_Seq(S1, x);

                cout << "关键字" << x << "位置是: " << pos << endl;

                break;

            case 3://折半查找

                S2 = S;

                sort(S2.R + 1, S2.R + MS);//有序表S2

                cout << "输入待查关键字：";

                cin >> x;

                pos = Search_Bin(S2, x);

                    if (pos != 0)

                        cout << "排序之后，关键字" << x << "的位置是: " << pos << endl;

                    else

                        cout << "查找失败\n";

                break;

            case 4://哈希表的创建

                Creat_HashTable(S,S3);

                break;

            case 5:

                cout << endl << "输入待查关键字：";

                cin >> x;

                cout << "哈希表中关键字位置在" << Search_Hash(S3, x) << endl;

                break;

            }

        }

    return 0;

}
