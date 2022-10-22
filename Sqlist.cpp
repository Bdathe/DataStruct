#include <iostream>
using namespace std;
#define MAXSIZE 100   //顺序表最大容量
#define ERROR 0
#define OK 1

typedef int Status; //用来表示函数状态
typedef int ElemType;

//顺序表结构体表示
typedef struct 
{
    ElemType * elem; //定义动态数组，存储数据
    int length; //顺序表当前的有效长度
}Sqlist;

//顺序表的相关操作

//初始化顺序表，建立一个空表L
Status Init_Sqlist(Sqlist &L); 
//销毁已存在的线性表L
Status Destory_Sqlist(Sqlist &L);
//清空线性表
Status Clear_Sqlist(Sqlist &L);
//在线性表的第i个位置插入新元素e //i从1开始
Status Insert_Elem(Sqlist &L, int i, ElemType e);
//删除线性表中的第i个位置的元素，并用e返回
Status Delete_Elem(Sqlist &L, int i, ElemType &e);
//判断线性表是否为空， 为空返回true， 否则返回false
bool Is_Empty(Sqlist L);
//判断线性表是否满
bool Is_Full(Sqlist L);
//返回线性表的元素个数
int Get_length(Sqlist L);
//L中查找与给定值e相等的元素，若成功返回元素在表中的序号（表中的第一个序号为1），否则返回0
int Locate_Elem(Sqlist L, ElemType e);
//将线性表的第i个位置元素返回给e
Status Get_Elem(Sqlist L, int i, ElemType &e);
//遍历
void Travese_Sqlist(Sqlist &L);
//冒泡排序---升序
Status Bubble_Sort(Sqlist &L);
//选择排序---升序
Status Select_Sort(Sqlist &L);
//插入排序---升序
Status Insert_Sort(Sqlist &L);
//线性表合并 --- La = La U Lb
void Union_Sqlist(Sqlist &La, Sqlist &Lb);


int main()
{
    //创建顺序表
    Sqlist La;
    Sqlist Lb;
    //初始化为空表
    Init_Sqlist(La);
    Init_Sqlist(Lb);

    //插入元素
    Insert_Elem(La,1,3);
    Insert_Elem(La,2,2);
    Insert_Elem(La,3,5);
    Insert_Elem(La,4,0);
    Insert_Elem(La,5,1);

    Insert_Elem(Lb,1,8);
    Insert_Elem(Lb,2,2);
    Insert_Elem(Lb,3,7);
    Insert_Elem(Lb,4,1);
    Insert_Elem(Lb,5,5);

    //遍历
    Travese_Sqlist(La);
    Travese_Sqlist(Lb);

    //线性表合并
    Union_Sqlist(La,Lb);

    //Bubble_Sort(La);
    //Select_Sort(La);
    //Insert_Sort(La);
    //遍历
    Travese_Sqlist(La);



    return 0;
}

//初始化顺序表，建立一个空表L
Status Init_Sqlist(Sqlist &L)
{
    //给表（数组）分配空间
    L.elem = new ElemType[MAXSIZE];
    
    //如果分配失败，退出程序
    if( !L.elem )
    exit(-1);

    //表的初始有效长度为0
    L.length = 0;

    return OK;
}

//销毁已存在的线性表L
Status Destory_Sqlist(Sqlist &L)
{
    //释放分配的空间
    delete []L.elem;
    //有效长度置0
    L.length = 0;

    return OK;
}

//清空线性表
Status Clear_Sqlist(Sqlist &L)
{
    //直接长度置为0
    L.length = 0;

    return OK;
}

//判断线性表是否为空， 为空返回true， 否则返回false
bool Is_Empty(Sqlist L)
{
    if( L.length == 0 )
    return true;
    else
    return false;
}

//判断线性表是否满
bool Is_Full(Sqlist L)
{
    if( L.length == MAXSIZE )
    return true;
    else
    return false;
}

//在线性表的第i个位置插入新元素e //i从1开始
Status Insert_Elem(Sqlist &L, int i, ElemType e)
{
    //满了就不能插入了
    if( Is_Full(L) ) 
    return ERROR;

    //判断插入位置是否合理
    if( i <= 0 || i > L.length + 1 )
    return ERROR;

    int j = L.length - 1; //用来判断是否到了插入位置
    //将i的空位让出来  //切记序号从1开始，下标从0开始
    while( j >= i - 1 )
    {
        L.elem[j+1] = L.elem[j];
        j--;
    }

    L.elem[i-1] = e; //插入

    L.length++; //长度加1

    return OK;
}

//删除线性表中的第i个位置的元素，并用e返回
Status Delete_Elem(Sqlist &L, int i, ElemType &e)
{
    //思路---直接覆盖
    //判断顺序表是否为空
    if( Is_Empty(L) )
    return ERROR;

    //判断删除位置是否合理
    if( i <= 0 || i > L.length )
    return ERROR;

    //先保存被删的值
    e = L.elem[i - 1];

    //覆盖
    for(int j = i - 1; j < L.length - 1; j++)
    {
        L.elem[j] = L.elem[j+1];
    }

    //有效值-1
    L.length--;

    return OK;
}

//返回线性表的元素个数
int Get_length(Sqlist L)
{
    return L.length; //返回有效长度
}

//L中查找与给定值e相等的元素，若成功返回元素在表中的序号（表中的第一个序号为1），否则返回0
int Locate_Elem(Sqlist L, ElemType e)
{
    //遍历
    for(int i = 0; i < L.length; i++)
    {
        if( L.elem[i] == e )
        return i+1;
    }

    return 0;
}

//将线性表的第i个位置元素返回给e
Status Get_Elem(Sqlist L, int i, ElemType &e)
{
    e = L.elem[i-1];

    return OK;
}

//遍历
void Travese_Sqlist(Sqlist &L)
{
    for(int i = 0; i < L.length; i++)
    cout << L.elem[i] << " ";

    cout << endl;
}

//冒泡排序---升序
Status Bubble_Sort(Sqlist &L)
{
    for( int i = 0; i < L.length - 1; i++ )
    {
        for( int j = 0; j < L.length - i - 1; j++ )
        {
            if( L.elem[j] > L.elem[j+1] )
            {
                ElemType temp = L.elem[j];
                L.elem[j] = L.elem[j+1];
                L.elem[j+1] = temp;
            }
        }
    }

    return OK;
}

//选择排序---升序
Status Select_Sort(Sqlist &L)
{
    for( int i = 0; i < L.length - 1; i++ )
    {
        int min = i; 
        for( int j = i + 1; j < L.length; j++ )
        {
            if( L.elem[min] > L.elem[j] )
            {
                min = j;
            }
        }

        if( min != i )
        {
            ElemType temp = L.elem[i];
            L.elem[i] = L.elem[min];
            L.elem[min] = temp;
        }

    }

    return OK;
}

//插入排序---升序
Status Insert_Sort(Sqlist &L)
{
    for( int i = 1; i < L.length; i++ )
    {
        //记录待插入元素的下标和值
        ElemType value = L.elem[i];
        int position = i;

        //寻找合适位置
        while( position > 0 && L.elem[position - 1] > value )
        {
            L.elem[position] = L.elem[position - 1];
            position--;
        }

        L.elem[position] = value; //插入
    }

    return OK;
}

//线性表合并
void Union_Sqlist(Sqlist &La, Sqlist &Lb)
{
    int La_len = Get_length(La);
    int Lb_Len = Get_length(Lb);

    ElemType e = 0;
    //在Lb中依次取出元素
    for( int i = 1; i <= Lb_Len; i++ )
    {
        //在b中获取元素
        Get_Elem(Lb,i,e);
        //在La中查找该元素
        if( !Locate_Elem(La, e) ) 
        {
            //如果在La中不存在该元素
            //将该元素插入在La的表尾
            Insert_Elem(La, La_len+1, e);
            La_len++;
        }
    }

    return;
}