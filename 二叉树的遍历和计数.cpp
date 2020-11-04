#include<iostream>
using namespace std;
typedef struct BiTNode{

    char data;//字符型数据域

    struct BiTNode *lchild,*rchild;//左右孩子指针

}BiTNode,*BiTree;


void CreateBiTree(BiTree &T){

    //按先序次序输入二叉树的结点值，#表示空子树（也可以用你熟悉的其他标记）

    char ch;

    cin>>ch;
    if(ch=='#') T=NULL;
    else
    {
        T = new BiTNode;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}



void PreOrderTraverse(BiTree T){

    //先序遍历二叉树T的递归算法

    if(T){

        cout<<T->data;//输出T的数据域

        PreOrderTraverse(T->lchild);//先序遍历T的左子树

        PreOrderTraverse(T->rchild);//先序遍历T的右子树

    }

}



void InOrderTraverse(BiTree T){

    //中序遍历二叉树T的递归算法
if(T){

        InOrderTraverse(T->lchild);//中序遍历T的左子树
        cout<<T->data;//输出T的数据域
        InOrderTraverse(T->rchild);//中序遍历T的右子树

    }


}



void PostOrderTraverse(BiTree T){

    //后序遍历二叉树T的递归算法

if(T){

        PostOrderTraverse(T->lchild);//后序遍历T的左子树

        PostOrderTraverse(T->rchild);//后序遍历T的右子树

        cout<<T->data;//输出T的数据域

    }

}



int Depth(BiTree T)

{

    int m,n;

    if(T==NULL) return 0;//如果是空树，深度为0，递归结束

    else

    {

        m=Depth(T->lchild);//递归计算左子树的深度记为m

        n=Depth(T->rchild);//递归计算右子树的深度记为n

        if(m>n) return (m+1);//二叉树的深度为m 与n的较大者加1

        else  return (n+1);

    }

}

int NodeCount(BiTree T)

{

    if(T==NULL) return 0;
    else return NodeCount(T->lchild)+NodeCount(T->rchild)+1;

}


void Copy(BiTree T, BiTree &NewT)

{
    if(T==NULL)
        {
            NewT=NULL;
            return;
        }
        else
        {
            NewT = new BiTNode;
            NewT->data=T->data;
            Copy(T->lchild,NewT->lchild);
            Copy(T->rchild,NewT->rchild);
        }
}


int main(){
BiTree tree,new_tree;

	int choose=-1;

	cout<<"1先序创建二叉树 2先序遍历 3中序遍历 4后序遍历 5统计结点数目 6复制 7深度 0退出"<<endl;

	while(choose!=0){

        cout<<"\n请选择操作：";

        cin>>choose;

        switch(choose){

        case 1:

            cout<<"请输入先序建立二叉链表的序列，#表示空子树（如ab##c##）\n";

             CreateBiTree(tree);//先序创建二叉树tree

            break;

        case 2:

            cout<<"先序遍历结果：";

             PreOrderTraverse(tree);//先序遍历二叉树tree

            break;

        case 3:

            cout<<"中序遍历结果：";

             InOrderTraverse(tree);//中序遍历二叉树tree

            break;

        case 4:

            cout<<"后序遍历结果：";

             PostOrderTraverse(tree);//后序遍历二叉树tree

            break;

        case 5:

            cout<<endl<<"结点个数为："<<NodeCount(tree)<<endl;//统计tree的结点总数

            break;

        case 6:

            Copy(tree,new_tree);//复制tree到newtree

            cout<<"复制完成,验证先序遍历结果："<<endl;

             PreOrderTraverse(new_tree);//先序遍历newtree

            break;

        case 7:

            cout<<"深度为："<< Depth(tree)<<endl;//计算tree的深度

            cout<<endl;

            break;



        }

        }

	return 0;

}

