#include<iostream>
#include<windows.h>
using namespace std;
const int max_size =10;
//弧节点
struct arc_node{ 
    int adj_vex;//邻接顶点下标
    arc_node * next; //下一条弧结点
    //int w;//权重
};
//顶点节点
struct vertex_node{ 
    char vertex; //顶点信息
    arc_node *first; //指向第一道弧 | 实际上是最后一个添加上去的的东西
};

template <class t> class graph{
    public:
        graph(t a[], int n, int e);
        ~graph();
        void dfs(int v); //深度优先
        void bfs(int v); //广度优先
        vertex_node adjlist[max_size];
        int v_num, arc_num;
    private:
        ;
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
    cout<<"请输入顶点信息如: 0 1 （表示位置0的节点指向位置1）"<<endl;
    for(int k=0;k<e;k++){
        int i; //对应顶点
        int j; //指向点
        //int w; //权重
        arc_node *s = new arc_node; //创建个弧
        cin>>i>>j; // j->i | 权重
        s->adj_vex=j;
        //s->w=w;
        s->next=adjlist[i].first; //头插
        adjlist[i].first=s;
    } 
}
//析构
template <class t>
graph<t>::~graph(){
    int i=0;
    while(i<v_num){
        arc_node*p=adjlist[i++].first;
        while (p){
            arc_node*s= p->next;
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
        p=p->next;
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
    while(f!=r){ // 队空
        v=q[++f]; //队头出队 
        arc_node *p= adjlist[v].first;
        while(p){
            int j=p->adj_vex;
            if(visited[j]==0) {
                cout<<adjlist[j].vertex;
                visited[j]=1;//标记访问
                q[++r]=j;//入队
                }
            p=p->next;
        }
    }
}

int mininum(int lowcost[]){
    int min=10000;//找个不可能的最大值
    int k=0;
    for(int i=1;i<6;i++){
        if(lowcost[i]!=0&&lowcost[i]<min){
            min=lowcost[i];
            k=i;
        }
    }
    return k;
}
int main(void){
    char a[5]={'a','b','c','d','e'};
    int max=10000;

    graph<char> test(a,5,4);
    cout<<"==图 建立完成=="<<endl;
    cout<<"==开始测试深度优先=="<<endl;
    test.dfs(0);
    cout<<endl;
    cout<<"==开始测试广度优先=="<<endl;
    test.bfs(0);
    cout<<endl;
    cout<<"==开始测试最小生成树=="<<endl;
    //构建邻接矩阵
    cout<<"请输入节点信息"<<endl;

    int edge[6][6]={0};
    int side=9;
    for(int i=0;i<6;i++){
        for(int j=0;j<6;j++){
            if(i!=j) edge[i][j]=max;
        }
    }
    //cin>>side;
    for(int i=0;i<side;i++){
        int a,b,w;
        cin>>a>>b>>w;
        edge[a][b]=w;
        edge[b][a]=w;
    }
    
    //开始最小生成树问题
    /*
0 1 24
0 2 46
0 5 19
1 4 12
2 3 17
2 5 25
3 4 38
3 5 25
4 5 26
    */
    int adjvex[6]={0};
    int lowcost[6]={0}; //最小权值边 
    int sum=0;
    for(int i=0;i<6;i++){
        adjvex[i]=0;
        lowcost[i]=edge[0][i];//选中0开始
    }
    lowcost[0]=0;//选中0开始
    for(int i=1;i<6;i++){
        
        int k=mininum(lowcost);
        //cout<<"##"<<k<<"##";
        cout<<adjvex[k]<<"->"<<k<<endl;
        sum+=edge[adjvex[k]][k];
        lowcost[k]=0;
        //更新
        for(int j=0;j<6;j++){
            if(lowcost[j]!=0 && edge[k][j]<lowcost[j]){
                lowcost[j]=edge[k][j];
                adjvex[j]=k;
            }
        }
    }
    for(int i=0;i<6;i++){
        cout<<adjvex[i]<<"|";
    }
    cout<<"最小花费："<<sum<<endl;
/*
    int num=0;
    for(int i=0;i<5;i++){
        cout<<lowcost[i]<<"|";
    }
    //count_w(lowcost,0,test);//初始化
    cout<<endl;
    arc_node *r= test.adjlist[num].first;
    lowcost[0]=0;
    while(r){
        int n=r->adj_vex;
        lowcost[n]=r->w;    
        r=r->next;
    }
    for(int i=0;i<5;i++){
        cout<<lowcost[i]<<"|";
    }

    for(int i=1;i<5;i++){
        int k=mininum(lowcost); //获取当前最小权值的点位
        cout<<"##"<<k<<"##";
        cout<<adjvex[k]<<"->>"<<k<<endl; //之前的值到k
        lowcost[k]=0; //从这里开始
        int arc_k[5]={-1,-1,-1,-1,-1};

        //count_w(arc_k,k,test);
        //再更新一遍权值
        arc_node *r= test.adjlist[k].first;
        arc_k[k]=0;
        while(r){
            int n=r->adj_vex;
            arc_k[n]=r->w;
            cout<<n;    
            r=r->next;
        }

        for(int j=0;j<5;j++){
            if(lowcost[j]!=0&&(arc_k[j]<lowcost[j] || lowcost[j]==-1)){
                lowcost[j]=arc_k[j];
                adjvex[j]=k;
            }
        }
        //现在的权值
        for(int i=0;i<5;i++){
        cout<<lowcost[i]<<"|";
        }
    }
    //lowcost[0]=0;// a-a 肯定是0 其实就算表示被选中
    cout<<"a"<<"b"<<"c"<<"d"<<"e"<<endl;
    for(int i=0;i<5;i++){
        cout<<adjvex[i]<<"|";
    }
*/
    //cout<<lowcost[1]<<lowcost[4];
    cout<<"=====end=====";
    return 0;
}