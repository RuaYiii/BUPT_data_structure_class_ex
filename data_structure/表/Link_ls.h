#include <stddef.h>
#include <iostream>
using namespace std;

template <class T>
    struct dul_node{
    T data; //数据
    struct dul_node<T> *prior,*next; //前驱与后继 --- 灵活变动 就不用中间变量了
    };
//双链表
template<class T> 
    class linklist{
    public:
        linklist();
        linklist(T a[],int n);
        ~linklist();
        int length();
        T get(int);
        int locate(T);
        void insert(T,int);
        T Delete(int);
    private:
        dul_node<T> *first;
};

template<class T> linklist<T>::linklist(){
    first= new dul_node<T>;
    first->prior= NULL;
    first->next= NULL; //一个空链表
}
template<class T> linklist<T>::linklist(T a[],int n){
    first= new dul_node<T>;
    dul_node<T> *r= first; //用来移动定位的尾指针
    r->next= NULL; 
    r->prior=NULL;
    for(int i=0;i<n;i++){
        dul_node<T>*s=new dul_node<T>;
        s->data= a[i];
        s->prior=r; //先搞定前驱动
        r->next= s;
        r=s;
    }
    r->next=NULL;
};
//析构
template<class T> linklist<T>::~linklist(){
    //释放内存
    while(first !=NULL){
        dul_node<T> *p=first;
        first=first->next;
        delete p;
    }
}
//定位 -- 呃呃 还没优化
template<class T> int linklist<T>::locate(T x){
    dul_node<T> *p= first->next;
    int j=1;
    while (p!=NULL){
        if(p->data==x) return j;
        p=p->next;
        j++;
    }
}
//get 注意有可能查不到，记得处理异常
template<class T> T linklist<T>::get(int i){
    dul_node<T> *p= first->next;
    int j=1;
    while (j!=i&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL) throw "位置非法";
    return p->data;
}
//插入
template<class T> void linklist<T>::insert(T x,int i){ 
    dul_node<T> *p=first;
    int j=0;//因为在i的位置插入，原有位置的数据将会变成i+1
    while (p!=NULL && j!=i){
        p=p->next;
        j++;} //找到位置n-1;
    if(p==NULL) throw "位置非法";
    else{
        dul_node<T> *s= new dul_node<T>;
        s->data=x; //初始化
        s->prior=p->prior;
        s->next=p;//连接原有i位置
        p->prior->next=s;
        p->prior=s;
    }
}
//删除
template<class T> T linklist<T>::Delete(int i){ 
    dul_node<T> *p=first;
    int j=0;
    while (p!=NULL && j!=i){
        p=p->next;
        j++;} //找到位置n; 不需要中间变量了
    if(p->next==NULL) throw "位置非法";
    else{
        p->prior->next=p->next; //null
        p->next->prior=p->prior;
        delete p;
    }
}
//len
template<class T> int linklist<T>::length(){
    dul_node<T> *p=first;
    int i=0;
    while(p->next != NULL){
        p=p->next;
        i++;}
    return i;
}
