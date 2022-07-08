#include<iostream>
#include<windows.h>
#include<string>
using namespace std;

template<class t> class bi_node //这里复用二叉链表作为二叉排序树的存储结构
{
    public:
        t data;
        bi_node <t> *lch;
        bi_node <t> *rch;
        bi_node():bi_node(NULL),bi_node(NULL) { }; //构造函数 
};
template<class t>class BST{
    public:
        BST(t r[],int n);
        ~BST();
        void insert(bi_node<t> *&r, bi_node<t>*s);
        void del(bi_node<t> *&r); //删除节点
        bool delete_BST(bi_node<t>*&r,t key);//删除key
        bi_node<t>* search(bi_node<t> *r,t key);//查找
        bi_node<t> * root;
};
template<class t> 
BST<t>::BST(t r[],int n){ //构造函数
    root=NULL;
    for(int i=0;i<n;i++){
        bi_node<t> *s= new bi_node<t>;
        s->data=r[i];
        s->lch=s->rch=NULL;//初始化
        insert(root,s);
    }
}
template<class t> 
BST<t>::~BST(){ //析构函数
    ;
}

template<class t>
void BST<t>::insert(bi_node<t> *&r, bi_node<t>*s) //插入 -- 在构造的时候用
{
    if ( r == NULL) r = s; //根节点空那就填充
    else if (s->data<r->data) insert(r->lch, s); //依照标准：比根节点小的放左边
    else insert(r->rch, s);//大的放右边
}

template<class t>
bi_node<t>* BST<t>::search(bi_node<t> *r,t key){ //查找
    if(r==NULL) return BULL; //到头了--失败
    if(key==r->data) return r;//找到了
    else if(key<r->data) return search(r->lch);
    else return search(r->rch);
}
template<class t>
void BST<t>::del(bi_node<t> *&r){
    bi_node<t> *q,*s;
    if(r->lch==NULL) {//只有右子树
        q=r;
        r=r->rch;
        delete q;
    }
    else if(r->rch==NULL){//只有左子树
        q=r;
        r=r->lch;
        delete q;
    }
    else{ //去循环喽
        q=r;
        s=r->lch;
        while(s->rch!=NULL){
            q=s;
            s->rch;
        }//找到r左支的最右节点
        r->data= s->data;//替换
        if(q!=r) q->rch=s->lch;
        else r->rch=s->lch;
        delete s;
    }
}

template<class t>
bool BST<t>::delete_BST(bi_node<t>*&r,t key){ //删除指定节点 
    if(r==NULL) return false;//结束
    else{
        if(key==r->data){ //先找后删除
            del(r);
            return true;
        }
        else if(key<r->data) return delete_BST(r->lch,key);
        else return delete_BST(r->rch,key);
    }
}