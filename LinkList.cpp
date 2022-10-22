#include <iostream>
using namespace std;
#define ERROR 0
#define OK 0

typedef int ElemType;
typedef int Status;

//链表结点结构体表示
typedef struct LNode
{
    ElemType data; //数据域
    struct LNode * pNext; //数据域
}LNODE, *LinkList;

//对链表的相关操作

//链表的初始化
Status Init_LinkList(LinkList &L);
//判断链表是否为空
bool Is_Empty(LinkList &L);
//销毁单链表
Status Destory_LinkList(LinkList &L);
//清空单链表
Status Clear_LinkList(LinkList &L);
//单链表元素个数
int Get_lenth(LinkList &L);
//取出单链表第i个位置的值,存储在e中---i从1开始
Status Get_Elem(LinkList &L, int i, ElemType &e);
//按值查找---返回结点指针
LNODE * Find_Elem_p(LinkList &L, ElemType e);
//按值查找---返回结点序号i
int Find_Elem_i(LinkList &L, ElemType e);
//插入节点---在第i个结点前，插入一个有效值为e的新结点
Status Insert_LNODE(LinkList &L, int i, ElemType e);
//删除节点---删除第i个结点，并将删除结点的有效值存储在e中
Status Delete_LNODE(LinkList &L, int i, ElemType &e);
//头插法建立链表
Status Head_Insert(LinkList &L,ElemType e);
//尾插法建立链表
Status Back_Insert(LinkList &L, ElemType e);
//遍历
void Travese_LinkList(LinkList &L);
//冒泡排序---升序
Status Bubble_Sort(LinkList &L);
//选择排序---升序
Status Select_Sort(LinkList &L);
//线性表合并 --- La = La U Lb
void Union_LinkList(LinkList &La, LinkList &Lb);


int main()
{
    //建立链表
    LinkList L;
    LinkList L1;
    //初始化
    Init_LinkList(L);
    Init_LinkList(L1);


    //尾插法建立链表
    Back_Insert(L,2);
    Back_Insert(L,1);
    Back_Insert(L,5);
    Back_Insert(L,3);
    Back_Insert(L,0);

    //头插法建立链表
    Head_Insert(L1,2);
    Head_Insert(L1,6);
    Head_Insert(L1,8);
    Head_Insert(L1,7);
    Head_Insert(L1,0);

    //遍历
    Travese_LinkList(L);
    Travese_LinkList(L1);

    //Bubble_Sort(L);
    //Select_Sort(L1);

    //线性表合并
    Union_LinkList(L,L1);

    //遍历
    Travese_LinkList(L);


    return 0;
}

//链表的初始化
Status Init_LinkList(LinkList &L)
{
    //创造一个头结点，头指针指向头结点
    LNODE * NewNode = new LNODE;
    if( !NewNode )
    exit(-1); //退出

    NewNode->pNext = NULL;
    L = NewNode;

    return OK;
}

//判断链表是否为空
bool Is_Empty(LinkList &L)
{
    if( L->pNext == NULL )
    return true;
    else
    return false;
}

//销毁单链表
Status Destory_LinkList(LinkList &L)
{
    //包括头结点也要销毁
    LNODE * p = L; //指针p指向头结点
    while( p->pNext )
    {
        L = p->pNext;
        delete p;
        p = L;
    }
    
    delete L;
    L = NULL;
    p = NULL;
    
    return OK;
}

//清空单链表
Status Clear_LinkList(LinkList &L)
{
    //与销毁类似，保留头结点,L指向头结点
    LNODE * p = L->pNext; //指针指向首结点
    LNODE * q = p;
    while( p ->pNext )
    {
        q = p->pNext;
        delete p;
        p = q;
    }

    delete p;
    p = NULL;
    q = NULL;

    L->pNext = NULL;

    return OK;
}

//单链表元素个数
int Get_lenth(LinkList &L)
{
    int len = 0;
    LNODE * p = L;

    while( p->pNext )
    {
        len++;
        p = p->pNext;
    }

    return len;
}

//取出单链表第i个位置的值---i从1开始
Status Get_Elem(LinkList &L, int i, ElemType &e)
{
    //判断 i 是否合理
    if( i < 1 || i > Get_lenth(L) )
    {
        return ERROR;
    }

    // 定位到 i 结点
    int j = 0;
    LNODE * p = L;
    while( p->pNext && j < i )
    {
        j++;
        p = p->pNext;
    }

    e = p->data;

    return OK;
}

//按值查找---返回结点指针
LNODE * Find_Elem_p(LinkList &L, ElemType e)
{
    //遍历
    LNODE * p = L;

    while( p->pNext )
    {
        p = p->pNext;
        if( e == p->data )
        return p;
    }

    return NULL;
}

//按值查找---返回结点序号i
int Find_Elem_i(LinkList &L, ElemType e)
{
    //遍历
    LNODE * p = L;
    int j = 0;

    while( p->pNext )
    {
        p = p->pNext;
        j++;

        if( e == p->data )
        return j;
    }

    return 0;
}

//插入节点---在第i个结点前，插入一个有效值为e的新结点
Status Insert_LNODE(LinkList &L, int i, ElemType e)
{
    //判断插入位置i是否合理
    if( i < 1 || i > Get_lenth(L) )
    return ERROR;

    //创造新结点
    LNODE * NewNode = new LNODE;
    if( !NewNode )
    exit(-1);

    //保存有效值
    NewNode->data = e;

    //定位到第i个结点前一个结点
    int j = 0;
    LNODE * p = L;

    while( p->pNext && j < i - 1 )
    {
        p = p->pNext;
        j++;
    }

    //插入
    NewNode->pNext = p->pNext;
    p->pNext = NewNode;

    return OK;
}

//删除节点---删除第i个结点，并将删除结点的有效值存储在e中
Status Delete_LNODE(LinkList &L, int i, ElemType &e)
{
    //判断删除位置是否合理
    if( i < 1 || i > Get_lenth(L) )
    return ERROR;

    //定位到第i个结点的前一个结点
    int j = 0;
    LNODE * p = L;
    
    while( p->pNext && j < i - 1 )
    {
        p = p->pNext;
        j++;
    }

    //定义指针指向被删除的结点，并将该节点有效值存储在e中
    LNODE * temp = p->pNext;
    e = temp->data;

    //第i-1个结点指向第i+1个结点
    p->pNext = p->pNext->pNext;

    //删除i结点
    delete temp;

    //指针置空
    temp = NULL;

    return OK;
}

//头插法建立链表
Status Head_Insert(LinkList &L,ElemType e)
{
    //创建新结点
    LNODE * NewNode = new LNODE;
    if( !NewNode )
    exit(-1);

    //放入有效值
    NewNode->data = e;

    //新结点指向首结点
    NewNode->pNext = L->pNext;

    //头结点指向新结点
    L->pNext = NewNode;

    return OK;
}

//尾插法建立链表
Status Back_Insert(LinkList &L, ElemType e)
{
    //创造新结点
    LNODE * NewNode = new LNODE;
    if( !NewNode )
    exit(-1);

    //给节点赋值
    NewNode->data = e;
    NewNode->pNext = NULL;

    //遍历到尾结点
    LNODE * p = L;
    while( p->pNext != NULL )
    {
        p = p->pNext;
    }

    //插入
    p->pNext = NewNode;

    return OK;
}

//遍历
void Travese_LinkList(LinkList &L)
{
    LNODE * p = L->pNext;
    while( p )
    {
        cout << p->data << " ";
        p = p->pNext;
    }

    cout << endl;

    return;
}

//冒泡排序---升序
Status Bubble_Sort(LinkList &L)
{
    //用指针指向结点移动
    LNODE * p, *q;
    int i,j;

    for( i = 0, p = L->pNext; i < Get_lenth(L) - 1; i++, p = p->pNext )
    {
        for( j = 0, q = L->pNext; j < Get_lenth(L) - i - 1; j++, q = q->pNext )
        {
            if( q->data > q->pNext->data )
            {
                ElemType temp = q->pNext->data;
                q->pNext->data = q->data;
                q->data = temp;
            }
        }
    }

    return OK;
}

//选择排序---升序
Status Select_Sort(LinkList &L)
{
    //用指针指向结点表示移动
    LNODE *p, *q;
    int i,j;

    for( i = 0, p = L->pNext; i < Get_lenth(L) - 1; i++, p = p->pNext )
    {
        //保存最小值的位置
        LNODE * min = p;
        for( j = i + 1, q = p->pNext; j < Get_lenth(L); j++, q = q->pNext )
        {
            if( min->data > q->data )
            {
                min = q;
            }
        }

        if( min != p )
        {
            ElemType temp = min->data;
            min->data = p->data;
            p->data = temp;
        }
    }

    return OK;
}


//线性表合并
void Union_LinkList(LinkList &La, LinkList &Lb)
{
    ElemType e = 0;
    //首先遍历Lb，在Lb中取元素
    for( int i = 1; i <= Get_lenth(Lb); i++ )
    {
        Get_Elem(Lb,i,e); //取元素

        //在La中查找是否存在e
        if( !Find_Elem_i(La,e) )
        {
            //如果不存在
            //将该元素插入表尾
            Back_Insert(La,e);
        }
    }

    return;
}