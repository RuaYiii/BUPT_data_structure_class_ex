#include<windows.h>
#include <stddef.h>
#include <iostream>
//#include <Link_ls.h>
#include <stddef.h>
#include<fstream>
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
        T* get_ad(int i);
        dul_node<T> *first;
    private:
        //dul_node<T> *first;
        ;
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
//获取地址
template<class T> T* linklist<T>::get_ad(int i){
    dul_node<T> *p= first->next;
    int j=1;
    while (j!=i&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL) throw "位置非法";
    return &(p->data);
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
        p->prior=s;}
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

struct DataType{
	int id;           //编号
    char name[10];   //姓名
	char tender;	//性别: male female
	char phone[13];//电话
	char addr[31];//地址
    }; 
DataType get_data(){
    DataType a;
    cin>>a.id;
    cin>>a.name;
    cin>>a.tender;
    cin>>a.phone;
    cin>>a.addr;
    return a;
}
//输入数据

int main(void){

    DataType input= {114,"MOMO",'M',"6666666","天桥"};
    bool on=1;//开关值
    bool empty; //是否空表
    char key;
    //测试数据
    DataType test_set[5]={
            {1,"alice",'M',"1000100010","西大街2号"},
            {2,"bob",'F',"123","东大街2号"},
            {3,"cat",'M',"345","南大街2号"},
            {4,"dog",'F',"114514","北大街2号"},
            {5,"elter",'F',"19196666","未知地址"}};
    linklist<DataType> test_book(test_set,5);
    linklist<DataType> book;
    
    //首先选取表
    while(on){
        cout<<"欢迎来到菜单，你想做的操作是："<<endl;
        cout<<"1.新建"<<endl;
        cout<<"2.使用测试表"<<endl;
        cout<<"q.退出"<<endl;
        cin>>key;
        if(key=='1'){
            cout<<"###当前您使用的是【空表】"<<endl;
            empty=true;
            on=false;}
        else if(key=='2'){
            book=test_book;
            cout<<"###当前您使用的是【测试表】（默认有5条数据）"<<endl;
            empty=false;
            on=false;
            }
        else if(key=='q'){return 0;}
        else cout<<"===不认识的指令，将重新回到菜单==="<<endl;
        }
    on=true;
    //接下来进行功能测试
    
    while(on){
        if(empty){
            cout<<"由于您是空表，只能进行一下操作："<<endl;
            cout<<"1.插入"<<endl;
            cout<<"2.放弃空表"<<endl;
            cin>>key;
            if(key=='1'){
                empty=0;
                
                dul_node<DataType> *r= book.first;
                dul_node<DataType> *s=new dul_node<DataType>;
                s->data=get_data();
                s->prior=r;
                s->next=NULL;
                r->next=s;
                }
            else if(key=='2'){return 0;}
            else {cout<<"===未知指令==="<<endl;continue;}
        }
        else{
        cout<<"请进行接下来的的操作是："<<endl;
        cout<<"1.插入"<<endl;
        cout<<"2.修改"<<endl;
        cout<<"3.删除"<<endl;
        cout<<"4.查找"<<endl;
        cout<<"5.退出并保存"<<endl;
        cin>>key;
        if(key=='1'){
            DataType input=get_data();
            int n;
            cout<<"插入位置？";
            cin>>n;
            book.insert(input,n);//插入整行测试数据
        }
        else if(key=='2'){
            int n;
            cout<<"修改位置？";
            cin>>n;
            DataType *change=book.get_ad(n+1);//获取待修改数据的地址
            cout<<"原有数据::";
            cout<<(*change).id<<"|"<<(*change).name<<"|"<<(*change).tender<<"|"<<(*change).phone<<"|"<<(*change).addr<<endl;
            (*change)=get_data();
            //修改
            cout<<"现在数据::";
            cout<<(*change).id<<"|"<<(*change).name<<"|"<<(*change).tender<<"|"<<(*change).phone<<"|"<<(*change).addr<<endl;
        }
        else if(key=='3'){
            int n;
            cout<<"删除位置？";
            cin>>n;
            book.Delete(n+1);//删除测试数据
        }
        else if(key=='4'){
            int id; //待查询id
            cout<<"查询id?";
            cin>>id;
            dul_node<DataType> *p=book.first->next;
            int place=0; //查到的位置  
        while(p!=NULL){
            if((p->data).id==id) break;
            //cout<<(p->data).id<<" ";
            p=p->next;
            place++;
        }
        if(place>=book.length()){cout<<"###查不到！！！"<<endl;}
        else cout<<"###查询结果位置是"<<place<<"(第"<<place+1<<"行数据)"<<endl;
        }
        else if(key=='5'){
            //保存数据: 文件读写
            ofstream outfile;
            outfile.open("data.book",ios::out|ios::app);
            dul_node<DataType> *q=book.first->next;
            while(q!=NULL){
                outfile<<(q->data).id<<" ";
                outfile<<(q->data).name<<" ";
                outfile<<(q->data).tender<<" ";
                outfile<<(q->data).phone<<" ";
                outfile<<(q->data).addr<<endl;
                q=q->next;
                }
            outfile.close();
            return 0;
        }
        else cout<<"===不认识的指令，将重新回到菜单==="<<endl;;
        //展示原有数据
    }
    }
    return 0;
}