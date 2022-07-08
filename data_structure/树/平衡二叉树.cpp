template<class t> class bi_node //这里复用二叉链表作为二叉排序树的存储结构
{
    public:
        t data;
        bi_node <t> *lch;
        bi_node <t> *rch;
        bi_node <t> *pare;
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
int deep(bi_node<t> *& tree){ //获取深度
    int dep=0;
    if(tree==nullptr) return dep;
    eles{
        int ld=deep(tree->lch);
        int rd=deep(tree->rch);
        if(ld>rd) dep= ld+1;
        else dep= rd+1;
        return dep;
    }
}   
template<class t>
int get_bal_factor(bi_node<t> *& tree){//获取平衡因子
    int l= deep(tree->lch);
    int r= deep(tree->rch);
    //左右子树深度
    int res= l-r// 差值
    if(res<0)//左大于右
        return -res;
    else return res;
}
template<class t>
bi_node<t>* get_noed(bi_node<t> *& p){//寻找最小不平衡结点
    bi_node<t>* t=p;
    while (get_bal_factor(t)<=1)
    {
        t=t->pare;
    }
    return t;
}

template<class t>
bool judge(bi_node<t> *& tree, int val){ //判断是否平衡
    bi_node<t>* p=s;
}
int main(void){

    return 0;
}