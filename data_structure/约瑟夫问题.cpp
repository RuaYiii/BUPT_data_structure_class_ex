#include<iostream>

using namespace std;
//不使用链表的解法 :思路是倒推
int save_Josephus(int a[],int n,int m){
    //m是会死的编号，n是所有人的人数
    for(int i=0;i<n;i++){
        int k=0; // 出局人数
        int num=-1; //编号
        while(k<n){
        for(int i=0;i<m;){
            num=(num+1)%n;
            if(a[num!=0]) i++;
        }
        cout<<a[num]<<endl;
        a[num]=0;
    }
}
}



template <class T>
    struct node{
    T data; //数据
    node<T> *next; //指针
    };

//单链表
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
        node<T> *first;
};

template<class T> linklist<T>::linklist(){
    first= new node<T>;
    first->next= NULL; //一个空链表
}
/*
template<class T> linklist<T>::linklist(T a[],int n){
    first= new node<T>;
    first->next= NULL; //
    for(int i=0;i<n;i++){
        node<T>*s=new node<T>;
        s->data = a[i];
        s->next=first->next;
        first->next=s;
    }
}
*/
template<class T> linklist<T>::linklist(T a[],int n){
    first= new node<T>;
    node<T> *r= first; //用来移动定位的尾指针
    r->next= NULL; 
    for(int i=0;i<n;i++){
        node<T>*s=new node<T>;
        s->data= a[i];
        r->next= s; 
        r=s;
    }
};
//析构
template<class T> linklist<T>::~linklist(){
    //释放内存
    while(first !=NULL){
        node<T> *p=first;
        first=first->next;
        delete p;
    }
}
//定位
template<class T> int linklist<T>::locate(T x){
    ndoe<T> *p= first->next;
    int j=1;
    while (p!=NULL){
        if(p->data==x) return j;
        p=p->next;
        j++;
    }
}
//get 注意有可能查不到，记得处理异常
template<class T> T linklist<T>::get(int i){
    ndoe<T> *p= first->next;
    int j=1;
    while (j!=i&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL) throw "位置非法"；
    return p->data;
}
//插入
template<class T> void linklist<T>::insert(T x,int i){ 
    node<t> *p=first;
    int j=0;//因为在i的位置插入，原有位置的数据将会变成i+1
    while (p!=NULL && j!=i-1){
        p=p->next;
        j++;} //找到位置n-1;
    if(p==NULL) throw "位置非法";
    else{
        node<T> *s= new node<T>;
        s->data=x; //初始化
        s->next=p->next;//连接原有i位置
        p->next=s;
    }
}
//删除
template<class T> T linklist<T>::Delete(int i){ 
    node<t> *p=first;
    int j=0;
    while (p!=NULL && j!=i-1){
        p=p->next;
        j++;} //找到位置n-1;
    if(p->next==NULL) throw "位置非法";
    else{
        node<T> *s= new node<T>;
        s=p->next;
        p->next=s->next; //null
        delete s;
    }
}
//len
template<class T> int linklist<T>::length(){
    node<T> *p=first;
    int i=0
    while(p->next!=NULL){
        p=p->next;
        i++;}
    return i;
}

