#include<iostream>
using namespace std;


#define MVNum 20   //最大顶点数
#define MAXQSIZE 100//队列元素


//队列的实现
typedef struct{

       int *base;         //初始化的动态分配存储空间

       int front;        //头指针指向队头元素

       int rear;         //尾指针指向队尾元素的下一个位置

}sqQueue;//顺序队列结构定义

void InitQueue(sqQueue &Q){

       Q.base= new int[MAXQSIZE];

       Q.front=Q.rear=0;//队头队尾指针置0

}

void EnQueue(sqQueue &Q, int e){

       Q.base[Q.rear]=e;//元素e添加到队尾

       Q.rear=(Q.rear+1)%MAXQSIZE;//尾指针加1（求余构造循环）

}

bool QueueEmpty(sqQueue Q){

        if(Q.front==Q.rear)//头尾指针相同

              return true;//返回真

      return false;//返回假

}

void DeQueue(sqQueue &Q, int &u){

       //队头元素出队并置为u

       u= Q.base[Q.front];//Q.base数组的队头元素赋值给u

       Q.front=(Q.front+1)%MAXQSIZE;//队头指针加1

}

//图的邻接矩阵定义和操作

//- - - - -图的邻接矩阵结构定义- - - - -

typedef struct{

       char vexs[MVNum];      //顶点表

       int arcs[MVNum][MVNum];  //邻接矩阵

       int vexnum,arcnum;   //图的当前点数和边数

}AMGraph;

//--------图邻接矩阵的操作--------------------

int LocateVex(AMGraph G , char v){
        int i;
        for(i=0;i<G.vexnum;i++)//按索引迭代G的顶点列表

              if(G.vexs[i]==v)//第i个顶点等于v，查找成功

                     return i;//返回索引

  return -1;

}//按名称查找顶点V，返回其索引

int CreateUDG(AMGraph &G){

    // 采用邻接矩阵表示法，创建无向图G

       int i , j , k;

       cout<<"请输入总顶点数，总边数，以空格隔开：";

    cin>> G.vexnum >> G.arcnum;

       cout<< "输入顶点的名称" << endl;

//初始化顶点列表

   for(i=0;i<G.vexnum;i++){

            cin>>G.vexs[i];

       }

       cout<< endl;

// 初始化邻接矩阵

for(i=0;i<G.vexnum;i++)

        for(j=0;j<G.vexnum;j++)
                G.arcs[i][j]= 0;//无权图

       cout<< "输入边依附的两个顶点，如 a b " << endl;

//构造邻接矩阵

for(k=0;k<G.arcnum;k++){

              char v1 , v2;

             cin>>v1>>v2;//输入边（v1,v2）依附的顶点

              i=LocateVex(G,v1);  j =LocateVex(G,v2);

              G.arcs[i][j]=1;//边（v1,v2）对应行列置为1

              G.arcs[j][i]=G.arcs[i][j];//赋值给对称边（v2,v1）

       }//for

       return 1;

}//CreateUDG

void PrintMatrix(AMGraph G)

{

    int i, j;

   for(i=0;i<G.vexnum;i++){

              for(j=0;j<G.vexnum;j++)

                     if (j!= G.vexnum )

                         cout <<G.arcs[i][j]<< "\t";

       cout<<endl;

       }

};//打印邻接矩阵

bool visited[MVNum];//定义访问状态数组，初值默认为false

int clearvisit( )

{

    int i;

    for (i=0;i< MVNum;i++)   visited[i]=false;

   return 0;

}//复位访问数组为初始状态

void DFS(AMGraph G, int v){

     int  w;

    cout<<G.vexs[v];//访问（输出）v的名称

      visited[v]=true;//改v的状态

    for(w=0;w<G.vexnum;w++)//依次检查v所在行

              if((G.arcs[v][w]!=0)&&(!visited[w]))//(v,w)存在边，且w未被访问 ，

                      DFS(G,w);//递归调用w

 }// 基于邻接矩阵实现DFS

void BFS (AMGraph G, int v){

    //广度优先遍历连通图G

       sqQueue  Q;//声明一个队列Q

       int  u,w;

       cout<<G.vexs[v];   //打印起点v的名称

       visited[v]=true;//改变v的状态
      InitQueue(Q);//对Q调用队列初始化函数

       EnQueue(Q,v);//v入队

   while(!QueueEmpty(Q)){//当队列非空时循环

              DeQueue(Q,u);//队头出队给u

              for(w= 0; w <G.vexnum;w++)

           { //如果v的邻接点w存在，且w未被访问过

                        if((G.arcs[u][w]=1)&&(!visited[w])){

                            cout<<G.vexs[w];//输出w的名称

                            visited[w]=true;//修改w的状态

                            EnQueue(Q,w);//邻接点w入队

                     }//if

              }//for

   }//while

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//主函数测试（建议使用菜单式调用，可反复操作）

/*int main(){

       cout<< "************邻接矩阵的创建及遍历**************" << endl << endl;

       AMGraph G;

       int  i, v , choose=-1;

       char vex;

       cout<<"1.创建 2.打印 3.DFS4.BFS 0.退出"<<endl;



       while(choose!=0){

       cout<<endl<<"输入选项："<<endl;

       cin>>choose;

       switch(choose)

       {

       case 1:

           CreateUDG(G);
           break;


       case 2:

          PrintMatrix(G);
          break;

       case 3:

            clearvisit();//复位状态数组

            cout << "请输入遍历起点：";

           cin >> vex;//输入顶点

           v=LocateVex(G,vex);//查找顶点，返回其索引

           cout << "深度优先搜索遍历连通图结果：" << endl;

           DFS(G,v);//对v进行深度优先遍历

           cout <<endl;

           break;

       case 4:

           clearvisit();//复位状态数组

            cout << "请输入遍历起点：";

           cin >> vex;//输入顶点

           v=LocateVex(G,vex);//查找顶点，返回其索引

           cout << "广度优先搜索遍历连通图结果：" << endl;

           BFS(G,v);//对v进行深度优先遍历

           cout <<endl;

           break;

        default:

               break;

       }

       }

       return 0;

}*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//邻接表


 //-------------图的邻接表定义---------------------

typedef struct ArcNode{       //边结点

   int adjvex;      //该边所指向的顶点的位置

   struct ArcNode *nextarc; //指向下一条边的指针

}ArcNode;

typedef struct VNode{

   char data; //顶点信息

   ArcNode *firstarc; //指向第一条依附该顶点的边的指针

}VNode, AdjList[MVNum];  //AdjList表示邻接表类型

typedef struct{

   AdjList vertices; //邻接表

   int vexnum, arcnum; //图的当前顶点数和边数

}ALGraph;



int ALocateVex(ALGraph G,char v){
       int i;

       for( i=0;i<G.vexnum;i++){ //确定点v在G中的位置
            if(G.vertices[i].data == v)
                return i;
       }
       return -1;


}//ALocateVex

//　采用邻接表创建无向图

void CreateAUDG(ALGraph &G){

       int i , k;

       cout<<"请输入总顶点数，总边数，以空格隔开:";

       cin>>G.vexnum>>G.arcnum; //输入总顶点数，总边数

      cout << endl;

//初始化邻接表的n个表头结点

cout<< "输入点的名称，如a" << endl;

       for(i= 0; i < G.vexnum; ++i){ //输入各点，构造表头结点表

              cout<< "请输入第" << (i+1) << "个点的名称:";

              cin>>G.vertices[i].data;       //输入顶点i的名称到data域

              G.vertices[i].firstarc=NULL;//初始化表头结点的指针域为NULL

   }

       cout<< endl;

//输入各边，创建边结点，构造邻接表

       cout<< "输入边依附的顶点，如a b" << endl;

       for(k= 0; k < G.arcnum;++k){

              char v1 , v2;

              int i , j;

              cout<< "请输入第" << (k + 1) << "条边依附的顶点:";

              cin>>v1>>v2; //输入一条边依附的两个顶点

              i= ALocateVex(G,v1);  j =ALocateVex(G,v2);

              //确定v1和v2在G中位置，即顶点在G.vertices中的序号

              ArcNode *p1=new ArcNode;       //生成一个新的边结点*p1

              p1->adjvex=j;//邻接点序号为j

              p1->nextarc=G.vertices[i].firstarc; G.vertices[i].firstarc=p1;

              //将新结点*p1插入顶点vi的边表头部

               ArcNode *p2=new ArcNode;  //生成另一个对称的新的边结点*p2

               p2->adjvex=i;  //邻接点序号为i

                p2->nextarc=G.vertices[j].firstarc; G.vertices[j].firstarc=p2;

              //将新结点*p2插入顶点vj的边表头部

   }//for

}//CreateUDG

int printALgraph(ALGraph G)

{

   cout << endl;

       cout<< "*****邻接表表示法创建的无向图*****" << endl;

       int i;

       for(i= 0 ; i < G.vexnum ; ++i){

              VNode  temp = G.vertices[i];

              ArcNode *p = temp.firstarc;

              if(p== NULL){

                     cout<<temp.data;//打印顶点i的data值

                     cout<<endl;

              }

              else{

                     cout<< temp.data;

                     while(p){

                            cout<< "->";

                            cout<< p->adjvex;//打印p的邻接点索引值

                            p=p->nextarc;//p后移

                     }

              }

              cout<< endl;

}

return 0;

}

int FirstAdjVex(ALGraph G,int u){

    ArcNode *p;

    p=G.vertices[u].firstarc;//顶点u的第一条边指针为p

    if(p) return p->adjvex;//p非空，返回p结点的邻接点值

    else return -1;

}//返回u的第1个邻接点



int NextAdjVex(ALGraph G,int u,int w){

    ArcNode *p;

     p=G.vertices[u].firstarc;//顶点u的第一条边指针为p

    while(p->adjvex!=w)//当p所指结点的邻接点不为w时循环，直到找到w

        p=p->nextarc;//p后移

    if (p->nextarc)    //如果p的后继结点非空，则存在邻接点

        return p->nextarc->adjvex;//返回p后继结点的邻接点值

    else

        return -1;

}//返回u的w之后的下一个邻接点新w



void ADFS(ALGraph G, int v){ //图G为邻接表类型

       cout<< G.vertices[v].data << "  ";

       visited[v]= true; //访问第v个顶点，并置访问标志数组相应分量值为true

       ArcNode *p = G.vertices[v].firstarc;            //p指向v的边链表的第一个边结点

       while(p!= NULL){    //边结点非空

              int w = p->adjvex; //表示w是v的邻接点

              if(!visited[w])  ADFS(G, w); //如果w未访问，则递归调用DFS

              p= p->nextarc;  //p指向下一个边结点

       }

}//DFS

void ABFS (ALGraph G, int v){

   // 按广度优先非递归遍历连通图G

       sqQueue Q;

       int u,w;

       cout<< G.vertices[v].data<<"\t";   visited[v] = true;

       InitQueue(Q);

       EnQueue(Q,v);

       while(!QueueEmpty(Q)){

               DeQueue(Q,u);

              for(w=FirstAdjVex(G,u);w>=0;w=NextAdjVex(G,u,w))

           {

                        if(!visited[w]){

                            cout<<G.vertices[w].data<<"\t";  //输出顶点w的data值

                            visited[w]=true;

                            EnQueue(Q,w);

                     }//if

              }//for

   }//while

}//BFS


int main(){

       cout<< "************邻接表的创建及遍历**************" << endl << endl;

       ALGraph G;

       int  i, v , choose=-1;

       char vex;

       cout<<"1.创建 2.打印 3.DFS4.BFS 0.退出"<<endl;



       while(choose!=0){

       cout<<endl<<"输入选项："<<endl;

       cin>>choose;

       switch(choose)

       {

       case 1:

           CreateAUDG(G);
           break;


       case 2:

          printALgraph(G);
          break;

       case 3:

            clearvisit();//复位状态数组

            cout << "请输入遍历起点：";

           cin >> vex;//输入顶点

           v=ALocateVex(G,vex);//查找顶点，返回其索引

           cout << "深度优先搜索遍历连通图结果：" << endl;

           ADFS(G,v);//对v进行深度优先遍历

           cout <<endl;

           break;

       case 4:

           clearvisit();//复位状态数组

            cout << "请输入遍历起点：";

           cin >> vex;//输入顶点

           v=ALocateVex(G,vex);//查找顶点，返回其索引

           cout << "广度优先搜索遍历连通图结果：" << endl;

           ABFS(G,v);//对v进行深度优先遍历

           cout <<endl;

           break;

        default:

               break;

       }

       }

       return 0;

}
