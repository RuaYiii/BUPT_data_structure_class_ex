#include<iostream>
#include<windows.h>
#include<string>
using namespace std;
#define max_size 100
template <class T>struct Node{
    T data;
    Node<T>* lch;
    Node<T>* rch;
};
template <class T> class BiTree{
    private:
        void Create(Node<T>* &R,T data[],int i,int n);
        void release(Node<T> *R);
    public:
        Node<T> *root;
        //BiTree():root(NULL){};
        int num;
        BiTree(T data[],int n);
        void pre_order(Node<T> *R);
        void in_order(Node<T> *R);
        void post_order(Node<T> *R);
        void level_order(Node<T> *R);

        bool get_path(Node<T> *R,T goal);

        int count_node(Node<T> *r);//节点数
        int count_l_node(Node<T> *r);//叶节点数
        int height(Node<T> *r); //深度
        ~BiTree();
};

//#二叉树的建立
//用于构建的辅助函数
template <class T> void BiTree<T>::Create(Node<T> *&R,T data[],int i,int n){
    if(data[i-1]!=0&&i<=n){
        R=new Node<T>;
        R->data = data[i-1];
        R->lch = R->rch = NULL;
        Create(R->lch,data, 2*i,n);
        Create(R->rch, data,2*i+1,n); 
    }
}
//构造函数
template <class T> BiTree<T>::BiTree(T data[],int n){
    Create(root,data,1,n);
    num=n;
}
//用于析构的辅助函数
template<class T> void BiTree<T>::release(Node<T> *Root){
    if(Root!=NULL){
        release(Root->lch);
        release(Root->rch);
        delete Root;
    }
}
//析构函数
template <class T> BiTree<T>::~BiTree(){
    release(root);
}
template <class T> bool BiTree<T>::get_path(Node<T> *R,T goal){
    bool key=0;
    if(R!=NULL){
        if(R->data==goal) return true;
        key=get_path(R->lch,goal);//左子树
        if(key) {
            cout<<R->lch->data<<"->";
            return true;
        }
        key=get_path(R->rch,goal); //右子树
        if(key) {
            cout<<R->rch->data<<"->";
            return true;
        }
        return false;
    }
    else return false;
}
//#遍历
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
        in_order(R->rch); //右子树
    }
}
//后序遍历
template<class T>
void BiTree<T>::post_order(Node<T> *R){
    if(R!=NULL){
        post_order(R->lch);//先左子树
        post_order(R->rch); //右子树
        cout<<R->data; //访问节点  
    }
}
//层序遍历
template<class T>
void BiTree<T>::level_order(Node<T> *R){
    Node<T> *q[num];
    int f=0;//队头
    int r=0;//队尾
    if(R!=NULL) q[++r]=R; //根节点入队
    while(f!=r){
        Node<T> *p= q[++f];//队头出队
        cout<<(p->data); 
        if(p->lch!=NULL) q[++r] =p->lch;//入队
        if(p->rch!=NULL) q[++r] =p->rch;//入队
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
//哈夫曼树的部分

struct h_code{
    char data;
    string code;
};
struct h_node{
    int w; //权重
    int lc,rc,parent; //左右孩子、父母节点
    bool visted=0;
};

class huffman{
    private:
        ;
    public:
        h_node* h_tree; //树
        h_code* code_table; //编码表
        int l_n;//叶节点数
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
    int ans_a;//最小的
    int ans_b;//次小的
    int c=0;
    int counter=0;
    for(int i=0;i<n;i++){
        c++;
        if(h_tree[i].visted==1){continue;}//被访问的不管了
        if(counter>=2){c--;break;}
        else if(counter==0){ans_a=i;}
        else{
            if(h_tree[i].w>h_tree[ans_a].w) ans_b=i;
            else{
                ans_b=ans_a;
                ans_a=i;
            }
        }
        counter++;
    }

    for(int i=c;i<n;i++){
        if(h_tree[i].visted==1){continue;}//被访问的不管了
        if(h_tree[i].w>h_tree[ans_a].w && h_tree[i].w>h_tree[ans_b].w) continue;
        else if(h_tree[i].w<=h_tree[ans_a].w){
            ans_b=ans_a;
            ans_a=i;
        }
        else ans_b=i;
    }
    h_tree[ans_a].visted=1;
    h_tree[ans_b].visted=1;
    *x=ans_a;
    *y=ans_b;
}
//建树
void huffman::create_tree(int a[],int n,char name[]){
    //a[]是权重数组::其实就是频率
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
    int n_v=n*2 -1;
    
    for(int i=n;i<2*n-1;i++){
        //选取两个最小的
        select_2_min(&x,&y,i); 
        //cout<<x<<" "<<y<<"||";
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
        cout<<code_table[i].data<<":"<<code_table[i].code<<" "; //编码表的输出
        return;
    }
    //左0右1
    code(h_tree[i].lc,newcode+"0");
    code(h_tree[i].rc,newcode+"1");
}
//递归建表
void huffman::create_table(){
    code(2*l_n-2,""); //2*n-1 个节点，去头再-1
}
//编码
void huffman::encode(char* i,string o){
    cout<<"##编码结果：";
    while (*i!='\0'){
        for(int a=0;a<l_n;a++){
            if(*i==code_table[a].data) {
                cout<<code_table[a].code;
                o+=code_table[a].code;
                break;}
            }
        i++;
    }
    cout<<endl;
}
//解码
void huffman::decode(char* i,char *o){
    cout<<"##解码结果：";
    while (*i!='\0'){
        int parent=2*l_n-2;
        while(h_tree[parent].lc!=-1){ //直到找到叶子结点
            if(*i=='0') parent=h_tree[parent].lc;
            else parent=h_tree[parent].rc;
            i++;
        }
        *o=code_table[parent].data; //记录
        cout<<code_table[parent].data; 
        o++;
    }
    cout<<endl;
}
int main(void){
    
    int test_set[9]={1,2,3,4,5,6,7,8,9};
    BiTree<int> test_tree(test_set,9);
    cout<<"##建树完成"<<endl;   
    cout<<"##开始测试前序遍历"<<endl;
    test_tree.pre_order(test_tree.root);
    cout<<endl;
    cout<<"##开始测试中序遍历"<<endl;
    test_tree.in_order(test_tree.root);
    cout<<endl;
    cout<<"##开始测试后序遍历"<<endl;
    test_tree.post_order(test_tree.root);
    cout<<endl;
    cout<<"##开始测试层序遍历"<<endl;
    test_tree.level_order(test_tree.root);
    cout<<endl;
    cout<<"##开始测试 求树深度的功能"<<endl;
    cout<<"树的深度是："<<test_tree.height(test_tree.root);
    cout<<endl;
    cout<<"##开始测试 求指定结点到根的路径的功能"<<endl;
    int find;
    cout<<"你想要从那开始？";
    cin>>find;
    test_tree.get_path(test_tree.root,find);
    cout<<'1'<<endl;
    cout<<"####二叉树实验结束####";
    cout<<"====================================="<<endl;
    cout<<"##开始哈夫曼树实验"<<endl;
    struct dict
    {
        char name;
        int w;
    };

    //初始化
    dict test_dic[25];
    string s;
    char input_c[25];
    int input_w[25];
    cout<<"请输入一段字符文本作为哈夫曼树编码依据："<<endl;
    //cin>>s;
    getchar();//读一下上一个操作的回车
    getline(cin,s);
    int leng=s.size();
    input_c[0]=s[0];
    input_w[0]=1;
    int l=1;
    //录入频率
    for(int i=1;i<leng;i++){
        //查找i位置的频率
        for(int j=0;j<l;j++){
            if(s[i]==input_c[j]){
                input_w[j]++;
                break;
                }
            if(j==l-1){
                input_c[l]=s[i];
                input_w[l]=1;
                l++;
                break;
            }//到头了
        }
    }
    cout<<"##统计词频成功 开始建树"<<endl;
    //cout<<test_dic[1].name<<test_dic[1].w;
    huffman test;
    int test_w[5]={20,100,1,3,2};
    char name[5]={'a','b','c','d','e'};
    test.create_tree(input_w,l,input_c); 
    cout<<"##哈夫曼树建树成功 开始创建编码表如下："<<endl;
    test.create_table();
    char i[10];
    char o[10];
    cout<<"##请选择您的操作："<<endl<<"1.编码"<<endl<<"2.解码"<<endl<<"q.退出"<<endl;
    char key;
    cin>>key;
    while(key!='q'){
        if(key=='1'){
            cout<<"请输入待编码字符串"<<endl;
            cin>>i;
            test.encode(i,o); 
        }
        else if(key=='2'){
            cout<<"请输入待解码字符串"<<endl;
            cin>>i;
            test.decode(i,o);
        }
        else{cout<<"!!!是不认识的字符，请重新输入"<<endl;}
        cout<<"##请选择您的操作："<<endl<<"1.编码"<<endl<<"2.解码"<<endl<<"q.退出"<<endl;
        cin>>key;
    }
    return 0;
}