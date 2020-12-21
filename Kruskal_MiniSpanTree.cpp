#include<iostream>
using namespace std;

#define MaxInt 3276
#define MVNum 99
typedef char VerTexType;
typedef int ArcType;


//定义一个无向图，用邻接矩阵储存

typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
}AMGraph;

int LocateVex(AMGraph G, VerTexType v)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vexs[i] == v)
            return i;
    }
    return -1;
}

int CreateUDN(AMGraph& G)
{
    VerTexType v1, v2;
    int i, j, w, k;
    cout << "依次输入总顶点数和总边数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "依次输入点的信息：" << endl;
    for (i = 0; i < G.vexnum; i++)
        cin >> G.vexs[i];
    for (i = 0; i < G.vexnum; i++)
        for (j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MaxInt;
    cout << "依次输入边依附的顶点和权值：" << endl;
    for (k = 0; k < G.arcnum; k++)
    {
        cin >> v1 >> v2 >> w;
        i = LocateVex(G, v1); j = LocateVex(G, v2);
        G.arcs[i][j] = w;
        G.arcs[j][i] = G.arcs[i][j];
    }
    return 1;
}

//克鲁斯卡尔算法
void MiniSpanTree_Kruskal(AMGraph G)
{
    int i,j,v1,v2,vs1,vs2,e = 0;
    //定义辅助数组Edge
    struct
    {
        VerTexType Head;
        VerTexType Tail;
        ArcType lowcost;
    }Edge[MVNum];
    //定义辅助数组Vexset
    int Vexset[MVNum];

    //将各边的信息存储到Edge数组中
    for (i = 0; i < G.vexnum; i++) {
        for (j = i + 1; j < G.vexnum; j++) {
            if (G.arcs[i][j] != MaxInt) {
                Edge[e].Head = G.vexs[i];
                Edge[e].Tail = G.vexs[j];
                Edge[e].lowcost = G.arcs[i][j];
                e++;
            }
        }
    }

    //将数组Edge中的元素按权值从小到达排序
    for (i = 0; i < G.arcnum; i++) {
        e = i;
        for (j = i + 1; j < G.arcnum; j++) {
            if (Edge[e].lowcost > Edge[j].lowcost) {
                e = j;
            }
        }
        Edge[G.arcnum] = Edge[i];
        Edge[i] = Edge[e];
        Edge[e] = Edge[G.arcnum];
    }

    //辅助数组，表示各顶点自成一个连通分量
    for (i = 0; i < G.vexnum; i++) {
        Vexset[i] = i;
    }

    for (i = 0; i < G.arcnum; ++i)        //依次查看数组Edge中的边
    {
        v1 = LocateVex(G, Edge[i].Head);   //获取边点的下标
        v2 = LocateVex(G, Edge[i].Tail);
        vs1 = Vexset[v1];                  //获取点的连通分量
        vs2 = Vexset[v2];
        if (vs1 != vs2)                 //边的两个顶点分属不同的连通分量
        {
            cout << Edge[i].Head << Edge[i].Tail << "  ";     //输出此边
            for (j = 0; j < G.vexnum; ++j)               //合并vs1和vs2两个连通分量
                if (Vexset[j] == vs2) Vexset[j] = vs1;
        } //if
    }  //for
}

int main() {
    AMGraph G;
    CreateUDN(G);
    MiniSpanTree_Kruskal(G);
    return 0;
}
