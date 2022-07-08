#include<iostream>
#include<windows.h>
using namespace std;
const int max_size =10;
//顶点节点
struct vertex_node{ 
    char vertex; //顶点信息
    arc_node *first; //指向第一道弧
};
//弧节点
struct arc_node{ 
    int adj_vex;//邻接顶点下标
    arc_node * next; //下一条弧结点
};
template <class t> class graph{
    public:
        graph(t a[], int n, int e);
        ~graph();
        void dfs(int v); //深度优先
        void bfs(int v); //广度优先
    private:
        vertex_node adjlist[max_size];
        int v_num, arc_num;
};
//构造
template <class t>
graph<t>::graph(t a[],int n,int e){
    v_num= n;//顶点
    arc_num= e;//弧数
    for(int k=0;k<n;k++){ //初始化顶点
        adjlist[k].vertex=a[k];
        adjlist[k].first=NULL;
    }
    for(int k=0;k<e;k++){
        int i; //对应顶点
        int j; //指向点
        arc_node *r = new arc_node; //创建个弧
        cin>>i>>j; // j->i
        s->adj_vex=j;
        s->next=adjlist[i].first; //头插
        adjlist[i].vertex=s;
    } 
}
//析构
template <class t>
graph<t>::~graph(){
    int i=0;
    while(i<v_num){
        arc_node*p=adjlist[i++].first;
        while (p){
            arc_node*s= p->adj_vex;
            delete p;
            p=s;
        }
        
    }
}
//深度优先
template <class t>
void graph<t>::dfs(int v){
    bool visited[max_size]={0};//是否被访问过
    cout<<adjlist[v].vertex;//打印顶点信息
    visited[v]=1;//标识访问
    arc_node *p= adjlist[v].first; //指向第一道弧
    while(p){
        int j=p->adj_vex;
        if(visited[j]==0)
            dfs(j);//若没有访问过，就再深度访问
        p=p->next
    }
}
//广度优先
template <class t>
void graph<t>::bfs(int v){
    bool visited[max_size]={0};//是否被访问过
    cout<<adjlist[v].vertex;//打印顶点信息
    int q[max_size];
    int f=0;//队头
    int r=0;//队尾
    visited[v]=1;
    q[++r]=v;//入队
    while(f!=r){ //层级一致就代表 这一层结束了
        v=q[++f] //队头出队 
        arc_node *p= adjlist[v].first;
        while(p){
            int j=p.adj_vex;
            if(visited[j]==0) {
                cout<<adjlist[j].vertex;
                visited[j]=1;//标记访问
                q[++r]=j;//入队
                }
            p=p->next;
        }
    }
}
