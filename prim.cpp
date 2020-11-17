#include<iostream>
using namespace std;

#define MaxInt 32767
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
    int i, j, w;
    cout << "依次输入总顶点数和总边数：" << endl;
    cin >> G.vexnum >> G.arcnum;
    cout << "依次输入点的信息：" << endl;
    for (i = 0; i < G.vexnum; i++)
        cin >> G.vexs[i];
    for (i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MaxInt;
    cout << "依次输入边依附的顶点和权值：" << endl;
    for (int k = 0; k < G.arcnum; k++)
    {
        cin >> v1 >> v2 >> w;
        i = LocateVex(G, v1); j = LocateVex(G, v2);
        G.arcs[i][j] = w;
        G.arcs[j][i] = G.arcs[i][j];
    }
    return 1;
}

//Prim算法的实现
struct
{
    VerTexType adjvex;
    ArcType lowcost;
}closedge[MVNum];

int Min(int n)
{
    int result,temp = MaxInt;
    for (int i=0; i < n; i++)
    {
        if (closedge[i].lowcost != 0 && closedge[i].lowcost < temp)
        {
            temp = closedge[i].lowcost;
            result = i;
        }
    }
    return result;
}

void MiniSpanTree_Prim(AMGraph G, VerTexType u)
{
    //无向图G以邻接矩阵形式存储，从顶点u出发构造G的最小生成树T，输出T的各条边
    int k, i, j; VerTexType u0, v0;
    k = LocateVex(G, u);
    for (j = 0; j < G.vexnum; ++j)
        if (j != k) closedge[j] = { u,G.arcs[k][j] };
    closedge[k].lowcost = 0;
    for (i = 1; i < G.vexnum; ++i)
    {
        //选择其余n-1个顶点，生成n-1条边（n=G.vexnum）
        k = Min(G.vexnum);
        //求出T的下一个结点：第k个顶点，closedge[k]中存有当前最小边
        u0 = closedge[k].adjvex;
        v0 = G.vexs[k];
        cout << u0 << v0 << "\t";
        closedge[k].lowcost = 0;
        for (j = 0; j < G.vexnum; ++j)
            if (G.arcs[k][j] < closedge[j].lowcost)
                closedge[j] = { G.vexs[k],G.arcs[k][j] };
    }
}

int main()
{
    VerTexType u;
    AMGraph G;
    CreateUDN(G);
    cout << "请输入生成最小树开始的节点：\n";
    cin >> u;
    MiniSpanTree_Prim(G, u);
    return 0;
}
