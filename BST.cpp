#include<iostream>

using namespace std;

#define ENDFLAG 999

//数据结构定义

typedef struct BSTNode {

	int data;	//结点数据域

	BSTNode* lchild, * rchild;	//左右孩子指针

}BSTNode, * BSTree;

//操作实现

//　二叉排序树的递归查找

BSTree SearchBST(BSTree T, int key) {
	if ((!T) || key == T->data)
		return T;
	else if (key < T->data)
		return SearchBST(T->lchild, key);
	else return SearchBST(T->rchild, key);
}


//算法7.5　二叉排序树的插入

void InsertBST(BSTree& T, int e) {

	//当二叉排序树T中不存在关键字等于e.key的数据元素时，则插入该元素

	if (!T) {

		BSTree S;
		S = new BSTNode;
		S->data = e;
		S->lchild = S->rchild = NULL;
		T = S;
	}
	else if (e < T->data)
		InsertBST(T->lchild, e);
	else if (e > T->data)
		InsertBST(T->rchild, e);
}

//　二叉排序树的创建

void CreateBST(BSTree& T) {

	//依次读入一个关键字为key的结点，将此结点插入二叉排序树T中

	T = NULL;
	int e;
	cout << "输入结点信息，输入‘999’结束" << endl;
	cin >> e;
	while (e != ENDFLAG) {
		InsertBST(T, e);
		cin >> e;
	}

}


//中序遍历验证BST树是否为递增序列

void InOrderTraverse(BSTree& T) {
	if(T){
		InOrderTraverse(T->lchild);
		cout << T->data << "  ";
		InOrderTraverse(T->rchild);
	}
}

int main()
{
	BSTree T = NULL;
	int choose=-1,x;
	cout << "  注意：先执行1号操作" << endl;
	while (choose != 0) {
		cout << "         【1.创建一个二叉排序树  2.中序遍历二叉树  3.查找   4.插入   0.退出 】" << endl;
		cout << " >>>请输入要进行的操作：" << endl;
		cin >> choose;
		switch (choose) {
		case 1:
			CreateBST(T);
			cout << "创建成功！已保存。" << endl;
			break;
		case 2:
			InOrderTraverse(T);
			cout << endl;
			break;
		case 3:
			cout << "输入要查找的信息：" << endl;
			cin >> x;
			if (SearchBST(T, x))
				cout << "查找成功！" << endl;
			else cout << "查找失败，没有此元素！" << endl;
			break;
		case 4:
			cout << "输入要插入的元素：" << endl;
			cin >> x;
			InsertBST(T, x);
			cout << "插入成功，已保存。" << endl;

		}
	}
	
	return 0;
	
}
