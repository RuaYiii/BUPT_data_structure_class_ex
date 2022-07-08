#include<iostream>
#include<windows.h>
#include<string>
using namespace std;

template<class t> class bi_node //这里复用二叉链表作为二叉排序树的存储结构
{
    public:
        t data;
        bi_node<t> *lch=NULL;
        bi_node<t> *rch=NULL    ;
        //构造函数 
};
template<class t>class BST{
    public:
        BST(t r[],int n);
        ~BST();
        void insert(bi_node<t> *&r, bi_node<t>*s);
        void del(bi_node<t> *&r); //删除节点
        bool delete_BST(bi_node<t>*&r,t key);//删除key
        bi_node<t> * search(bi_node<t> *r,t key);//查找
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
    else if (s->data < r->data) insert(r->lch, s); //依照标准：比根节点小的放左边
    else insert(r->rch, s);//大的放右边
}

template<class t>
bi_node<t>* BST<t>::search(bi_node<t> *r,t key){ //查找
    //cout<<"|";
    if(r==NULL) {
        cout<<"找不到您想要的值"<<endl;
        return NULL;
        } //到头了--失败
    if(key==r->data) {
        cout<<"找到了："<<r->data<<endl;
        return r;}//找到了
    else if(key<r->data) return search(r->lch,key);
    else return search(r->rch,key);
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


template <class t>
class AVL{
    private:
        ;
    public:
        t data;
        int height;
        AVL<t>* lch;//左孩子
        AVL<t>* rch;//右孩子
        AVL<t>* Insert(AVL<t>* avl,t data);//插入
        AVL<t>* Create(t* data,int size);//构造
        AVL<t>* del(AVL* avl,t data);//删除
        int getHeight(AVL<t>* avl);//获得树高
        AVL<t>* LL(AVL<t>* avl);
        AVL<t>* LR(AVL<t>* avl);
        AVL<t>* RR(AVL<t>* avl);
        AVL<t>* RL(AVL<t>* avl);
        AVL<t>* FindMin(AVL* avl);//找最小值
        AVL<t>* FindMax(AVL* avl);//找最大值
        int Max(int a,int b){
			return (a>b)?a:b;
		};
        void preorder(AVL* T);//前序遍历
        AVL<t>* search(AVL<t> *r,t data);//查找

};
template <class t>//插入
AVL<t>* AVL<t>::Insert(AVL<t>* avl,t data){
    if(!avl){ //如果是空的
		avl = new AVL<t>;
		avl->data = data;
		avl->height = 0; 
		avl->lch = avl->rch = NULL; 
        }
    else if(data<avl->data){ //若data小于根节点的值 去左子树
        avl->lch= Insert(avl->lch,data);//插入的结果扔进来
        //查看左右子树高度
        int lh= getHeight(avl->lch);
        int rh= getHeight(avl->rch);
        if(lh-rh==2){ //失衡了，得开始平衡
            if(data<avl->lch->data){
                //插入节点小于左孩子
                avl=LL(avl);//进行ll旋转
            }
            else avl=LR(avl); //否则lr旋转
        }
    }
    else if(data>avl->data){
        avl->rch= Insert(avl->rch,data);//插入的结果扔进来
        //查看左右子树高度
        int lh= getHeight(avl->lch);
        int rh= getHeight(avl->rch);
        if(lh-rh==2){//失衡了
            if(data>avl->rch->data){
                //插入节点大于右孩子
                avl=RR(avl);//进行ll旋转
            }
            else avl=RL(avl); //否则lr旋转
        }
    }
    avl->height= Max(getHeight(avl->lch),getHeight(avl->rch))+1;//更新深度
    return avl;
}
template <class t>//删除 对应data
AVL<t>* AVL<t>::del(AVL<t>* avl,t data){
    if(!avl) return avl; //空的话直接返回就好
    else if(data < avl->data){
        //去左子树找
        avl->lch= del(avl->lch,data);
        //因为有可能删完破坏平衡 所以得立刻修正
        int lh= getHeight(avl->lch);
        int rh= getHeight(avl->rch);
        if(rh-lh==2){//右比左高2
            if(data > avl->rch->data) 
                avl=RR(avl);//RR旋转
            else 
                avl=RL(avl);//反之RL
        }
        
    }
    else if(data > avl->data){
        //去右子树
        avl->rch= del(avl->rch,data);
        //因为有可能删完破坏平衡 所以得立刻修正
        int lh= getHeight(avl->lch);
        int rh= getHeight(avl->rch);
        if(lh-rh==2){
            if(data < avl->lch->data)
                avl=LL(avl);//理解类似
            else 
                avl=LR(avl);
        }
    }
    else{ //等于的情况——找到要删除的咯
        if(avl->lch&&avl->rch){
            //即 都存在
            AVL<t> *tmp= FindMin(avl->rch);//找右子树最小的来代替
            avl->data=tmp->data; //替换
            avl->rch=del(avl->rch,tmp->data);//继续看看
        }
        else{//总之有一个为空
            AVL<t>* tmp= avl;
            if(!avl->lch) avl= avl->rch;
            else if(!avl->rch) avl= avl->lch; 
            delete tmp; 
        }
    }
    return avl;
}
template <class t> //查找最大值
AVL<t>* AVL<t>::FindMax(AVL* avl){
    ;
}
template <class t> //查找最小值 - 辅助删除
AVL<t>* AVL<t>::FindMin(AVL<t>* avl){
    AVL<t>* cur = avl;//搜索树为空时，返回NULL 
	if(cur == NULL) return NULL;
	while(cur){
	if(cur->lch == NULL) return cur; //左子树为空时 那根节点就最小
    else cur = cur->lch; //继续左走
	}
}
template <class t>
AVL<t>* AVL<t>::Create(t* data,int size){ //建树
    AVL<t>* avl = NULL;
    for(int i=0;i<size;i++){ avl=Insert(avl,data[i]);}
    return avl;
}
template <class t>
int AVL<t>::getHeight(AVL<t>* avl){ //获取高度
    if(!avl) return 0;
	return avl->height;
}
template <class t>//LL旋转-单旋转
AVL<t>* AVL<t>::LL(AVL<t>* avl){
    //左子树的左子树导致的失衡
    //自然，A成为了B的右孩子，BL,AR的性质不变，BR成为了A的左孩子
    AVL<t>* tmp = avl->lch;//抓住节点B往上拽使之成为根节点
    avl->lch=tmp->rch;
    tmp->rch=avl;//完成旋转
    avl->height=Max(getHeight(avl->lch),getHeight(avl->rch))+1;
    tmp->height=Max(getHeight(tmp->lch),getHeight(avl))+1;
    return tmp;
}
template <class t>//RR旋转-单旋转
AVL<t>* AVL<t>::RR(AVL<t>* avl){
    //右子树的右子树导致的失衡

    AVL<t>* tmp = avl->rch;//抓住节点B往上拽使之成为根节点
    avl->rch=tmp->lch;
    tmp->lch=avl;//完成旋转
    avl->height=Max(getHeight(avl->lch),getHeight(avl->rch))+1;
    tmp->height=Max(getHeight(tmp->rch),getHeight(avl))+1;
    return tmp;
}
template <class t>
AVL<t>* AVL<t>::RL(AVL<t>* avl){//LR旋转
    //左子树的右子树插入导致对的失衡 
    avl->lch= LL(avl->lch);//先左子树RR旋转
    return RR(avl);//然后左旋
}
template <class t>
AVL<t>* AVL<t>::LR(AVL<t>* avl){//LR旋转
    //右子树的左子树插入导致对的失衡 
    avl->lch= RR(avl->rch);//先右子树LL旋转
    return LL(avl); //然后右旋
}
template <class t> //前序遍历
void AVL<t>::preorder(AVL<t>* T){
    if(T==NULL) return; //到底了 结束
    cout<<T->data<<" ";
    preorder(T->lch);
    preorder(T->rch);
}
template <class t> //查找
AVL<t>* AVL<t>::search(AVL<t> *r,t data){ 
    //cout<<"|";
    if(r==NULL) {
        cout<<"===没找到==="<<endl;
        return NULL;} //到头了--失败
    if(data==r->data) {
        cout<<"找到了："<<r->data<<endl;
        return r;
        }//找到了
    else if(data<r->data) return search(r->lch,data);
    else return search(r->rch,data);
}

int main(void){
    cout<<"###开始二叉排序树实验"<<endl;
    int test_set[10]={30,2,31,4,5,6,7,8,90};
    BST<int> test(test_set,10);
    //cout<<test.root->data;
    cout<<"###请输入要查找的结点："<<endl;
    int del_n;
    cin>>del_n;
    bi_node<int>* ans= test.search(test.root,del_n);
    cout<<"###请输入要删除的结点："<<endl;
    cin>>del_n;
    test.delete_BST(test.root,del_n);
    cout<<"###请输入要查找的结点："<<endl;
    cin>>del_n;
    bi_node<int>* t= test.search(test.root,del_n);
    cout<<"###请输入要插入的结点："<<endl;
    bi_node<int>* new_ans=new bi_node<int>;
    cin>>new_ans->data;
    test.insert(test.root,new_ans);
    cout<<"###请输入要查找的结点："<<endl;
    cin>>del_n;
    t= test.search(test.root,del_n);
    cout<<"===end====";
    int test_data[10]={1,2,3,4,5,6,7,8,9,10};
	AVL<int>* avl;
	avl = new AVL<int>;
	avl = avl->Create(test_data,10);
	
	cout<<"##前序遍历："<<endl;
	avl->preorder(avl);

    int find_n;
    cout<<"请输入要查找的结点："<<endl;
    cin>>find_n;
	AVL<int>* find;
    find=avl->search(avl,find_n);
    int num;
	cout<<"请输入要删除的结点："<<endl;
	cin>>num;
	avl = avl->del(avl,num);

	cout<<"删除之后："<<endl;
	cout<<"##前序遍历："<<endl;
	avl->preorder(avl);

    cout<<"请输入要查找的结点："<<endl;
    cin>>find_n;
    find=avl->search(avl,find_n);

    cout<<"请输入要插入的结点："<<endl;
    cin>>find_n;

    avl=avl->Insert(avl,find_n);
    cout<<"##前序遍历："<<endl;
	avl->preorder(avl);

    cout<<"===end==";
    return 0;
    return 0;
}