#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType char
#define MAXSIZE 100
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

typedef struct TreeNode* BinTree;
struct TreeNode {
    ElementType Data;
    BinTree LeftChild;    //左儿子
    BinTree RightChild;   //右儿子
};

typedef struct Node* SNode;     //定义结构体，以便写队列
struct Node {
    ElementType Item;
    SNode Next;
};

struct QNode {      //定义队列
    SNode front;    //front指向队列的第一个元素
    SNode rear;     //rear指向队列的最后一个元素
};

typedef struct QNode* Queue;

BinTree Initialize() {  //初始化二叉树
    return (BinTree)malloc(sizeof(struct TreeNode));
}

Queue CreatQ() {        //初始化队列
    return (Queue)malloc(sizeof(struct TreeNode) * MAXSIZE);
}

int IsEmptyQ(Queue Q) { //判断队列是否为空
    return (Q->front == Q->rear) ? 0 : 1;
}

BinTree DeleteQ(Queue PtrQ) {   //输出队列的第一个元素，类型是BinTree
    SNode FrontCell;
    BinTree T;
    T = Initialize();
    
    if (PtrQ->front == NULL) {
        printf("ERROR\n");
        return NULL;
    }
    FrontCell = PtrQ->front;
    if (PtrQ->front == PtrQ->rear) {
        PtrQ->front = PtrQ->rear = NULL;
        return NULL;
    }
    else {
        PtrQ->front = PtrQ->front->Next;
    }
    
    T->Data = FrontCell->Item;
    
    return T;
}

void AddQ(Queue PtrQ, BinTree Child) {  //从最后位置插入元素
    SNode RearCell = malloc(sizeof(SNode));
    
    if (PtrQ->front == NULL) {
        printf("ERROR\n");
        return;
    }
    RearCell->Item = Child->Data;
    if (PtrQ->front == PtrQ->rear) {
        PtrQ->rear = NULL;
        PtrQ->front = RearCell;
        RearCell->Next = PtrQ->rear;
        return;
    }
    else {
        PtrQ->front = RearCell;
        RearCell->Next = RearCell->Next->Next;
        return;
    }
}

void First_Read(BinTree X) {    //先序遍历
    if (X) {
        printf("%c", X->Data);
        First_Read(X->LeftChild);
        First_Read(X->RightChild);
    }
}

void Mid_Read(BinTree X) {      //中序遍历
    if (X) {
        Mid_Read(X->LeftChild);
        printf("%c", X->Data);
        Mid_Read(X->RightChild);
    }
}

void Last_Read(BinTree X) {     //后序遍历
    if (X) {
        Last_Read(X->LeftChild);
        Last_Read(X->RightChild);
        printf("%c", X->Data);
    }
}

void Lever_Read(BinTree X) {    //层序遍历
    Queue Q;
    BinTree T;
    if (!X) {
        return;
    }
    Q = CreatQ();
    AddQ(Q, X);
    while (!IsEmptyQ(Q)) {
        T = DeleteQ(Q);
        printf("%c", T->Data);
        if (T->LeftChild) {
            AddQ(Q, T->LeftChild);
        }
        if (T->RightChild) {
            AddQ(Q, T->RightChild);
        }
    }
}

BinTree CreatBinTree(ElementType* input_mid, ElementType* input_last, int length) { //已知中序和后序序列构造二叉树
    BinTree T;
    T = Initialize();
    
    ElementType* p;
    ElementType root;
    
    if (length <= 0) {
        return NULL;
    }
    root = *(input_last + length - 1);
    T->Data = root;
    for (p = input_mid; p < input_mid + length; p++) {
        if (*p == root) {
            break;
        }
    }
    
    int k = (int)(p - input_mid);
    T->LeftChild = CreatBinTree(input_mid, input_last, k);
    T->RightChild = CreatBinTree(input_mid + k + 1, input_last + k, length - k - 1);
    return T;
}

ElementType Max(BinTree T) {
    if (T->LeftChild == NULL && T->RightChild != NULL) {
        return MAX(T->Data, Max(T->RightChild));
    }
    else if (T->LeftChild != NULL && T->RightChild == NULL) {
        return MAX(T->Data, Max(T->LeftChild));
    }
    else if (T->LeftChild == NULL && T->RightChild == NULL) {
        return T->Data;
    }
    return (MAX(T->Data, MAX(Max(T->LeftChild), Max(T->RightChild))));
}

ElementType Min(BinTree T) {
    if (T->LeftChild == NULL && T->RightChild != NULL) {
        return MIN(T->Data, Min(T->RightChild));
    }
    else if (T->LeftChild != NULL && T->RightChild == NULL) {
        return MIN(T->Data, Min(T->LeftChild));
    }
    else if (T->LeftChild == NULL && T->RightChild == NULL) {
        return T->Data;
    }
    return (MIN(T->Data, MIN(Min(T->LeftChild), Min(T->RightChild))));
}

int Value(BinTree T) {
    return (Max(T) - Min(T));
}

int main(int argc, char const *argv[]) {
    BinTree X;
    X = Initialize();
    char input_mid[] = "BBCDEFGHIJW";
    char input_last[] = "BCDBGJWIHFE";
    int length = (int)strlen(input_mid);
    X = CreatBinTree(input_mid, input_last, length);
    First_Read(X);
    printf("\n");
    Mid_Read(X);
    printf("\n");
    Last_Read(X);
    printf("\n");
    printf("%d\n", Value(X));
    return 0;
}
