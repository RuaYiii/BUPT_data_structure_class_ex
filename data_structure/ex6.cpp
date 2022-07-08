#include<iostream>
#include<windows.h>
#include<string>
#include <time.h>
#include<stdlib.h>
#include<fstream>
#include <chrono>
#include <ctime>


using namespace std;
using namespace std::chrono;
int count_=0;
int move_=0;

struct  Node{
    int data;
    Node* next;
};
void swap(int* a,int *b){ //用于交换的辅助函数
    int cup;
    cup= *a;
    *a=*b;
    *b= cup;
}
void resart(int a[],int b[],int n){ //对数据进行初始化的辅助函数----因为牵扯测试数据的复用
    for(int i=0;i<n;i++){
        a[i]=b[i];
    }
}
Node* resart_link(Node*head_,int n){ //对数据进行初始化的辅助函数----因为牵扯测试数据的复用
    Node* first= new Node;
    Node*p=head_;
    Node*q=first;
    for(int i=0;i<n;i++){
        Node* sub=new Node;
        sub->data= p->data;
        q->next= sub; 
        q=sub;
        p=p->next;
    }
    q->next=NULL;
    return first;
}
//冒泡排序 | O(n2) 
void bubble_sort(int _data[],int n){
    int *data = new int[n];
    resart(data,_data,n);//对数据进行初始化
    int count=0;
    int move=0;
    int p=n;
    while(p!=0){
        count++;
        int bound=p; //记录无序区域的范围
        p=0;
        for(int i=0;i<bound;i++){
            count++;
            if(data[i]>data[i+1]){
                count++;
                swap(&data[i],&data[i+1]);
                move+=3;//一次交换3次移动
                p=i;
            }
        }
    }
    delete []data;
    cout<<"移动次数："<<move<<"|";
    cout<<"比较次数："<<count<<endl;
}
void Link_bubble(Node* Head_,int n){
    count_=0;
    move_=0;
    Node * Head=resart_link(Head_,n);//一个新的复用
    Node *p = Head,*q = p->next;
    int num=n;
    while(num!=0){
        count_++;
        int bound=num; //记录无序区域的范围
        num=0;
        for(int i=0;i<bound;i++){
            count_++;
            if(q->data > q->next->data){
                count_++;
                int cup=q->data;
                q->data=q->next->data;
                q->next->data=cup;
                move_+=3;//一次交换3次移动
                num=i;
            }
            
        }
        q = p->next;
    }
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//直接插入排序   O(n2) ---O(1)
void insert_sort(int _data[],int n){
    int *data = new int[n];
    resart(data,_data,n);//对数据进行初始化
    int count=0;
    int move=0;
    for(int i=1;i<n;i++){
        count++;
        int tmp = data[i];//设置哨兵
        //哨兵之前有序 哨兵后无序
        int j;
        for(j=i;j>0 && data[j-1]>tmp;j--){
            count++;
            data[j] = data[j-1];
            move++;
        }
        data[j] = tmp; //找到合适位置进行插入
    }
    delete []data;
    cout<<"移动次数："<<move<<"|";
    cout<<"比较次数："<<count<<endl;
}

//直接拆入排序--链表方法
void Link_sert(Node* Head_,int n){
    count_=0;
    move_=0;
    Node * Head=resart_link(Head_,n);//一个新的复用
    Node *p = Head,*q = p->next;
    while(p->next!=NULL){
        count_++;
        p=Head;
        while(p->next!=NULL && p!=q ){
            count_++;
            if (p->next->data > q->next->data){ //交换结点的顺序
                Node *s=q->next;
                q->next = s->next; //摘除s结点
                s->next = p->next; //插入到p结点之后
                p->next = s;
                move_+=3;
                break;
            }
            count_++;
            p=p->next;
        }
        if(p==q) q= q->next;
        p=q;
    }
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//简单选择排序 | O(n2) ---O(1)
void ez_select_sort(int _data[],int n){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    int move=0;
    int count=0;
    for(int i=0;i<n-1;i++){
        count++;
        int index=i;//查找最小位置
        for(int j=i+1;j<n;j++){
            //i-n之间找一个最小的关键码
            if(data[j]<data[index]) index=j;
            count+=2;
        }
        if(index!=i){
            move+=3;
            swap(&data[index],&data[i]); //最小关键码位置与i位置交换
        }
        count++;
    }
    delete []data;
    cout<<"移动次数："<<move<<"|";
    cout<<"比较次数："<<count<<endl;
}
void Link_ez_select(Node* Head_,int n){
    count_=0;
    move_=0;
    Node * Head=resart_link(Head_,n);//一个新的复用
    Node *p = Head,*q = p->next;
    for(int i=0;i<n-1;i++){
        Node * index_n;
        count_++;
        int index=i;//查找最小位置
        index_n=q;
        Node *j_n=q->next;
        for(int j=i+1;j<n;j++){
            if(j_n->data < index_n->data) index=j;
            count_+=2;
            j_n=j_n->next;
        }
        if(index!=i){
            move_+=3;
            int cup= q->data;
            index_n->data= q->data;
            q->data= cup;
        }
        q=q->next;
        count_++;
    }
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//希尔排序 -- 插入排序的改良 | O(n2) 和 O(nlog2n) 之间
void shell_insert(int _data[],int n){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    int move=0;
    int count=0;
    //以d作为增量
    for(int d=n/2;d>=1;d=d/2){
        //每次缩小间隔 然分d个子序列
        count++;
        for(int i=d;i<n;i++){ //一趟希尔排序
            count++;
            if(data[i]<data[i-d]){
                int tmp =data[i]; //还是插入排序里的哨兵
                int j;
                for(j=i;j>=d && data[j-d]>tmp;j=j-d){
                    count++;
                    data[j] = data[j-d];
                    move++;
                    }
                data[j] = tmp;
                move++;
            }
        }
    }
    delete []data;
    //不太稳定 和增量序列序列有关 | |时间复杂度在 O(n2)和O(nlog2n)之间（
    cout<<"移动次数："<<move<<"|";
    cout<<"比较次数："<<count<<endl;
}
//快排  |O(nlog2n)
int partion(int r[] , int first, int end){   //其实就是找个轴值 向两端移动比较小的
    int i=first;
    int j=end;
    int pivot = r[i];
    extern int count_;
    extern int move_;
    //选取基准记录
    while (i<j){
        while((i<j) && (r[j]>=pivot)){ //右侧扫描 | 从后向前找到第一个比基准小的记录
            j--;
            count_++;
            }
        r[i] = r[j];
        while((i<j) && (r[i]<=pivot)){//左侧扫描  | 从前到后找到第一个比基准大的记录
            i++;
            count_++;
            }
        r[j] =r[i];
        move_+=2;
        count_++;
    }
    r[i] = pivot;
    return i;
}

void qsort(int r[], int i, int j){
    if (i<j){
        count_++;
        int pivotloc = partion(r,i,j); //选一个基准记录
        qsort( r, i, pivotloc-1); //基准记录以左扫描
        qsort( r, pivotloc+1, j); //基准数据以右扫描
    }
}
void Q_sort(int _data[],int n){ 
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    qsort(data,0,n-1);
    delete []data;
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}

//快排---链表形式 
Node * link_find(Node *first,int n){
    Node *p= first->next;
    int j=0;
    while (p!=NULL){
        if(j==n) return p;
        p=p->next;
        j++;
    }
}

int link_partion(Node *head, int first, int end){
    int i=first;
    int j=end;
    Node* pivot_n=link_find(head,i);
    Node* j_n=link_find(head,j);
    int pivot = pivot_n->data;
    
    //选取基准记录
    while (i<j){
        while((i<j) && (j_n->data >=pivot)){ //右侧扫描
            j--;
            j_n=link_find(head,j);
            count_++;
            }
        link_find(head,i)->data = j_n->data;
        while((i<j) && (link_find(head,i)->data<=pivot)){//左侧扫描
            i++;
            count_++;
            }
        j_n->data =link_find(head,i)->data;
        move_+=2;
        count_++;
    }
    link_find(head,i)->data= pivot;
    return i;
}
void link_q(Node* head ,int i,int j){
    
    if (i<j){
        count_++;
        int pivotloc = link_partion(head,i,j);
        link_q(head, i, pivotloc-1);
        link_q(head, pivotloc+1, j);
    }
}
void Link_Q(Node* Head_,int n){
    count_=0;
    move_=0;
    Node * Head=resart_link(Head_,n);//一个新的复用
    link_q(Head,0,n-1);
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//堆排序 - 简单选择排序的改进【大根堆】 | O(nlog2n)
void sift(int r[],int k,int m){ //筛选算法
    int i=k;
    int j=i*2; //因为是完全二叉树的结构
    while(j<=m&&i!=j){
        //根结点与左右孩子进行比较
        if(j<m && r[j]<r[j+1] ) j++;
        if(r[i]>r[j]) break;
        else{
            swap(r[i],r[j]);//不满足堆的条根结点与较小的节点对换
            i=j;
            j=i*2;
            move_+=3;
        }
        count_+=3;
    }
}
void heap_sort(int _data[],int n){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    move_=0;
    count_=0;
    //先建堆
    for(int i=(n/2);i>=0;i--){
        sift(data,i,n-1);
        count_++;
    }
    for(int i=n-1;i>0;i--){
        //输出堆顶元素----这个堆的最小值
        swap(data[0],data[i]);//最后一个元素移至堆顶 - 
        sift(data,1,i-1); //整理一下这个堆
        count_++;
        move_+=3; //因为做了一次对换
    }
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//归并排序 O(nlog2n)
void merge(int r[], int r1[], int s, int m, int t){
    int i=s;//i指向r[s~m]
    int j=m+1; //j指向r[m+1~t],
    int k=s;    
    while (i<=m && j<=t){
        count_+=2;
        if (r[i]<r[j]){
            r1[k++] = r[i++];// 每次循环取r[i] r[j]较小者放入r[k]
            } 
        else r1[k++] = r[j++];
    }
}
void merge_s(int r[], int r1[], int s, int t){ 
    int r2[10];
    count_++;
    if (s==t) r1[s] = r[s];
    else{
        int m=(s+t)/2; //将r平分成r[s..m] 和r[m+1..t]
        merge_s (r, r2, s, m); //递归的将r[s..m] 归并为r2[s..m]
        merge_s ( r, r2, m+1, t); //递归的将r[m+1..t] 归并为r2[m+1..t]
        merge( r2, r1, s, m, t); // 将r2[s..m] 和r2[m+1..t]归并r1[s..t]
        move_++;
    }
}
void merge_sort(int _data[],int n){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    move_=0;
    count_=0;
    merge_s(data,data,0,n-1);
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//计数排序 | O(k+n) | k为最大数
void count_num_sort(int _data[],int n,int k){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    move_=0;
    count_=0;
    int *b=new int[n];
    int *c=new int[k+1];
    memset(c,0,(k+1)*sizeof(int));//置零
    int j;
    for(j=0;j<n;j++){ //计算每个元素的个数
        c[data[j]]++;
        count_++;
    }
    for(j=1;j<=k;j++){ //计算每个元素比它小的元素个数————能确定其排序的位置
        c[j]=c[j]+c[j-1];
        count_++;
        move_++;
    }
    for(j=n-1;j>=0;j--){
        b[c[data[j]-1]]=data[j]; //存储到相应的位置
        c[data[j]]--;
        count_++;
        move_++;
    }
    delete []c;
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//桶排序 | O(m+n)
struct node{ //节点
    int n_data;
    node *next;
}; 
struct bucket{ //桶定义
    int num;
    node* first;
    node* rear;
};
void bucket_sort(int _data[],int n,int m,node* &p){
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    move_=0;
    count_=0;
    int i,k;
    bucket* b= new bucket[m]; //建立m个桶
    for(i=0;i<m;i++){ //初始化清桶 
        b[i].num=0;
        b[i].first=b[i].rear = NULL;
    }
    for(i=0;i<n;i++){ //装桶过程
        count_++;
        k=data[i];
        p= new node;
        p->n_data=k;
        p->next= NULL;
        if(b[k].num==0){ //对应数字的桶没装过
            count_++;
            b[k].first=b[k].rear=p;
            move_++;
            } 
        else{
            b[k].rear->next=p;//继续装这个桶
            b[k].rear=p;
            move_+=2;
        }
        b[k].num++;
    }
    //进行收集
    for(i=0;i<m && b[i].num==0;i++){count_++;} //就是找空桶位置i
    p=b[i].first;
    //按序号依次将各非空的桶首尾连接起来
    for(int j=i+1;j<m;j++){
        count_+=2;
        if(b[j].num!=0){
            b[i].rear->next=b[j].first;
            move_++;
            i=j;
        }
    }
    delete []b;
    delete []data;
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}
//基数排序 --按各位的值进行排序的技术 | O(m1+n)+O(m2+n)+..... 
void count(int data[],int n,int exp){ //按照exp位数排序--辅助函数
    int* output= new int[n];
    int i,buckets[10]={0};
    for(i=0;i<n;i++){
        count_++;
        buckets[(data[i]/exp)%10]++; //存储出现次数
    }
    for(i=1;i<10;i++){
        count_++;
        move_++;
        buckets[i]+=buckets[i-1];//更改其值为  output的位置
    }
    for(i=n-1;i>=0;i--){
        count_++;
        output[buckets[(data[i]/exp)%10]-1] =data[i]; //临时存储排序好的数据---
        move_++;
        buckets[(data[i]/exp)%10]--; //倒一个减一个
    }
    for(i=0;i<n;i++){//排序好的结果
        count_++;
        data[i]=output[i];
        move_++;
    }
    delete []output;
}
int get_max(int data[],int n){ //找到数组内最大值---辅助函数
    int max= data[0];
    for(int i=0;i<n;i++){
        count_++;
        if(data[i]>max){ max=data[i];}
    }
    return max;
}
void radix_sort(int _data[],int n){ //基数排序
    int *data = new int[n]; 
    resart(data,_data,n);//对数据进行初始化
    move_=0;
    count_=0;
    int exp;//位数
    int max=get_max(data,n);//获取数组内最大值
    for(exp=1;max/exp>0;exp*=10){//每次迭代进位
        count_++;
        count(data,n,exp);
    }
    delete []data;
    cout<<"移动次数："<<move_<<"|";
    cout<<"比较次数："<<count_<<endl;
}

//单链表
template<class T> 
    class linklist{
    public:
        linklist(T a[],int n);
        ~linklist();
        int length();
        T get(int);
        int locate(T);
        void insert(T,int);
        T Delete(int);
        Node *first;
};
//构造
template<class T> linklist<T>::linklist(T a[],int n){
    first= new Node;
    Node *r= first; //用来移动定位的尾指针
    r->next= NULL; 
    for(int i=0;i<n;i++){
        Node*s=new Node;
        s->data= a[i];
        r->next= s; 
        r=s;
    }
    r->next=NULL;
};
//析构
template<class T> linklist<T>::~linklist(){
    //释放内存
    while(first !=NULL){
        Node *p=first;
        first=first->next;
        delete p;
    }
}
//定位
template<class T> int linklist<T>::locate(T x){
    Node *p= first->next;
    int j=1;
    while (p!=NULL){
        if(p->data==x) return j;
        p=p->next;
        j++;
    }
}

time_t get_time(){
    system_clock::time_point time_point_now = system_clock::now(); // 获取当前时间点
    system_clock::duration duration_since_epoch = time_point_now.time_since_epoch(); // 从1970-01-01 00:00:00到当前时间点的时长
    time_t microseconds_since_epoch = duration_cast<microseconds>(duration_since_epoch).count(); 
    time_t tm_microsec = microseconds_since_epoch; // 当前时间的微妙数
    return tm_microsec;
}
int main(void){
    int pos_set[10]={1,2,3,4,5,6,7,8,9,10};//正序数据
    int re_set[10]={10,9,8,7,6,5,4,3,2,1};//逆序数据
    int rand_set[10]={5,3,10,4,6,7,1,9,2,8};//随机数据
    
    
    cout<<"###进行起泡排序测试："<<endl;
    time_t start=get_time();
    cout<<"【正序数据】:";
    bubble_sort(pos_set,10);
    cout<<"【逆序数据】:";
    bubble_sort(re_set,10);
    cout<<"【随机数据】:";
    bubble_sort(rand_set,10);
    time_t end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    cout<<"###进行直接插入排序测试："<<endl;
    cout<<"【正序数据】:";
    insert_sort(pos_set,10);
    cout<<"【逆序数据】:";
    insert_sort(re_set,10);
    cout<<"【随机数据】:";
    insert_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();    
    cout<<"###进行简单选择排序测试："<<endl;
    cout<<"【正序数据】:";
    ez_select_sort(pos_set,10);
    cout<<"【逆序数据】:";
    ez_select_sort(re_set,10);
    cout<<"【随机数据】:";
    ez_select_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();    
    cout<<"###进行希尔排序测试："<<endl;
    cout<<"【正序数据】:";
    shell_insert(pos_set,10);
    cout<<"【逆序数据】:";
    shell_insert(re_set,10);
    cout<<"【随机数据】:";
    shell_insert(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time(); 
    cout<<"###进行快速排序测试："<<endl;
    cout<<"【正序数据】:";
    Q_sort(pos_set,10);
    cout<<"【逆序数据】:";
    Q_sort(re_set,10);
    cout<<"【随机数据】:";
    Q_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;
    
    start=get_time();
    cout<<"###进行桶排序测试："<<endl;
    cout<<"【正序数据】:";
    heap_sort(pos_set,10);
    cout<<"【逆序数据】:";
    heap_sort(re_set,9);
    cout<<"【随机数据】:";
    heap_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;
    
    start=get_time();
    cout<<"###进行归并排序测试："<<endl;
    cout<<"【正序数据】:";
    merge_sort(pos_set,10);
    cout<<"【逆序数据】:";
    merge_sort(re_set,10);
    cout<<"【随机数据】:";
    merge_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    cout<<"###进行计数排序测试："<<endl;
    cout<<"【正序数据】:";
    count_num_sort(pos_set,10,10);
    cout<<"【逆序数据】:";
    count_num_sort(re_set,9,10);
    cout<<"【随机数据】:";
    count_num_sort(rand_set,10,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;
    
    start=get_time();
    cout<<"###进行桶排序测试："<<endl;
    node *front;
    cout<<"【正序数据】:";
    bucket_sort(pos_set,10,11,front);
    cout<<"【逆序数据】:";
    bucket_sort(re_set,10,11,front);
    cout<<"【随机数据】:";
    bucket_sort(rand_set,10,11,front);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    cout<<"###进行基数排序测试："<<endl;
    cout<<"【正序数据】:";
    radix_sort(pos_set,10);
    cout<<"【逆序数据】:";
    radix_sort(re_set,10);
    cout<<"【随机数据】:";
    radix_sort(rand_set,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    cout<<"##接下来我们进行链表形式的排序测试"<<endl;
    
    linklist<int> test1(pos_set,10);
    linklist<int> test2(re_set,10);
    linklist<int> test3(rand_set,10);
    //建立测试数据
    start=get_time();
    cout<<"###进行【链表】插入排序测试："<<endl;
    cout<<"【正序】:";
    Link_sert(test1.first,10);
    cout<<"【逆序】:";
    Link_sert(test2.first,10);
    cout<<"【乱序】:";
    Link_sert(test3.first,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    cout<<"###进行【链表】冒泡排序测试："<<endl;
    cout<<"【正序】:";
    Link_bubble(test1.first,10);
    cout<<"【逆序】:";
    Link_bubble(test2.first,10);
    cout<<"【乱序】:";
    Link_bubble(test3.first,10);
    //快速
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    //简单选择
    cout<<"###进行【链表】简单选择排序测试："<<endl;
    cout<<"【正序】:";
    Link_ez_select(test1.first,10);
    cout<<"【逆序】:";
    Link_ez_select(test2.first,10);
    cout<<"【乱序】:";
    Link_ez_select(test3.first,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;

    start=get_time();
    cout<<"###进行【链表】快速排序测试："<<endl;
    cout<<"【正序】:";
    Link_Q(test1.first,10);
    cout<<"【逆序】:";
    Link_Q(test2.first,10);
    cout<<"【乱序】:";
    Link_Q(test3.first,10);
    end=get_time();  
    cout<<"|总耗时:"<<end-start<<"微秒"<<endl;
    cout<<"===end==="<<endl;

    return 0;
}