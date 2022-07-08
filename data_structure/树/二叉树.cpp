#include<iostream>
#include<windows.h>
#include<string>
using namespace std;
#define max_size 100
template <class T>struct Node{
    T data;
    Node<T>* lch;
    Node<T>* rch;
};//二叉树node

template <class T> class BiTree{
    private:
        void Create(Node<T>*&R,T data[],int i,int n);
        void release(Node<T> *R);
        
    public:
        Node<T> *root;
        BiTree():root(NULL){};
        BiTree(T data[]);
        void pre_order(Node<T> *R);
        void in_order(Node<T> *R);
        void post_order(Node<T> *R);
        void level_order(Node<T> *R);
        int count_node(Node<T> *r);//节点数
        int count_l_node(Node<T> *r);//叶节点数
        int height(Node<T> *r); //深度
        ~BiTree();
};
//二叉树的建立
template <class T>
void BiTree<T>::Create(Node<T> *&R,T data[],int i,int n){
    if(i<=n&&data[i-1]!=0){
        R=new Node<T>;
        R->data = data[i-1];
        R->lch = R->rch = NULL;
        Create(R->lch,data, 2*i);
        Create(R->rch, data,2*i+1); 
    }
}
//前序遍历
template <class T>
void BiTree<T>::pre_order(Node<T> *R){
    if(R!=NULL){
        cout<<R->data; //访问节点
        pre_order(R->lch);//左子树
        pre_order(R->rch); //右子树
    }
}
//中序遍历
template<class T>
void BiTree<T>::in_order(Node<T> *R){
    if(R!=NULL){
        in_order(R->lch);//先左子树
        cout<<R->data; //访问节点
        pre_order(R->rch); //右子树
    }
}
//后序遍历
template<class T>
void BiTree<T>::post_order(Node<T> *R){
    if(R!=NULL){
        in_order(R->lch);//先左子树
        pre_order(R->rch); //右子树
        cout<<R->data; //访问节点  
    }
}
//层序遍历
/*
template<class T>
void BiTree<T>::level_order(Node<T> *R){
    Queue<Node<T>> Q;
    if(R!=NULL) Q.InQueue(R);
    while(!Q.IsEmpty()){
        Node<T>*p= Q.DelQueue();
        cout<<p->data;
        if(p->lch!NULL) Q.inQueue(p->lch);
        if(p->rch!NULL) Q.inQueue(p->rch)
    }
} */
//释放：析构函数
template<class T>
void BiTree<T>::release(Node<T> *root){
    if(root!=NULL){
        release(root->lch);
        release(root->rch);
        delete root;
    }
}
//求节点总数
template<class T>
int BiTree<T>::count_node(Node<T> *r){
    if(r==NULL){return 0;}
    else {
        int m= count_node(r->lch);
        int n= count_node(r->rch);
        return(m+n+1);//结点总数= 左子树 + 右子树 + 1
    }
}
//求叶节点数
template<class T>
int BiTree<T>::count_l_node(Node<T> *r){
    if(r==NULL){return 0;}
    if(r->lch==NULL&&r->rch) return 1;
    else{
        int m= count_l_node(r->lch);
        int n= count_l_node(r->rch);
        return(m+n);//叶结点总数= 左子树 + 右子树 
    }
}
//求深度
template<class T>
int BiTree<T>::height(Node<T> *r){
    if(r==NULL)return 0;
    else{
        int m=height(r->lch);
        int n=height(r->rch);
        return(m>n? m+1 : n+1);
    }
}
//求指定结点到根的路径
struct h_code{
    char data;
    string code;
};
struct h_node{
    int w; //权重
    int lc,rc,parent; //左右孩子、父母节点
};
class huffman{
    private:
        h_node* h_tree; //树
        h_code* code_table; //编码表
        int l_n;//叶节点数
    public:
        void create_tree(int a[],int n,char name[]);//建树
        void create_table(); //建表
        void encode(char* i, string o);//编码
        void decode(char* i, char* o);//解码
        void select_2_min(int*x,int*y,int n);
        void code(int i,string newcode);//对第i个节点编码
        //~huffman();
};
//选两个最小的
void huffman::select_2_min(int*x,int*y,int n){
    int ans_a,ans_b;
    if(h_tree[0].w>=h_tree[1].w){
        ans_b=0;
        ans_a=1;}
    else{
        ans_a=0;
        ans_b=1;
    }

    for(int i=2;i<n;i++){
        if(h_tree[i].w>h_tree[ans_a].w && h_tree[i].w>h_tree[ans_b].w) continue;
        else if(h_tree[i].w<=h_tree[ans_a].w){
            ans_b=ans_a;
            ans_a=i;
        }
        else ans_b=i;
    }
    *x=ans_a;
    *y=ans_b;
}
//建树
void huffman::create_tree(int a[],int n,char name[]){
    //a[]是权重数组::其实就是评论
    //name[]是字符内容
    l_n=n;
    h_tree= new h_node[l_n*2 -1]; //
    code_table= new h_code[l_n]; 
    int x,y;
    //初始化
    for(int i=0;i<n;i++){
        h_tree[i].w=a[i]; //权重
        h_tree[i].lc=h_tree[i].rc=h_tree[i].parent=-1; //全置为-1
        code_table[i].data=name[i]; //字符
    }
    //正式建树    
    for(int i=n;i<2*n-1;i++){
        //选取两个最小的
        select_2_min(&x,&y,i); //这有问题
        h_tree[x].parent=h_tree[y].parent=i; //设立共同父亲
        h_tree[i].lc=x;
        h_tree[i].rc=y;
        h_tree[i].w= h_tree[x].w+h_tree[y].w; //其权重和成为新的节点权重
        h_tree[i].parent=-1;
    }   
}
//单个编码
void huffman::code(int i,string newcode){
    if(h_tree[i].lc==-1){ //左孩子不存在
        code_table[i].code=newcode; //后续累加
        return;
    }
    //左0右1
    code(h_tree[i].lc,newcode+"0");
    code(h_tree[i].rc,newcode+"1");
}
//递归建
void huffman::create_table(){
    code(2*l_n-2,""); //2*n-1 个节点，去头再-1
}
//编码
void huffman::encode(char* i,string o){
    while (*i!='\0'){
        for(int a=0;a<l_n;i++){
            if(*i==code_table[a].data) {
                o+=code_table[a].code;
                break;}
            }
        i++;
    }
}
//解码
void huffman::decode(char* i,char *o){
    while (*i!='\0'){
        int n=2*n-2;
        while(h_tree[n].lc!=-1){ //直到找到叶子结点
            if(*i=='0') n=h_tree[n].lc;
            else n=h_tree[n].rc;
            i++;
        }
        *o=code_table[n].data; //记录 
        o++;
    }
}
int main(void){
    huffman test;
    int test_w[5]={20,100,1,3,2};
    char name[5]={'a','b','c','d','e'};
    string test_s;
    return 0;
}
