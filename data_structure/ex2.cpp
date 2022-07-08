#include <stddef.h>
#include<iostream>
using namespace std;
template<class t> struct node
{
    t data;
    struct node<t> * next;
    
};
template<class t> class link_stack{
    public:
        link_stack(){top=NULL;}
        ~link_stack();
        void push(t x);
        t pop();
        t get_top(){return top->data;}
        bool empty(){return (top==NULL)?true:false;}
        bool find(t x){
            struct node<t> *p= top;
            while (p!=NULL){
                if(p->data == x) return true; //如果找到了
                p=p->next;
            }
            return false;
        }
        struct node<t> * top;
    private:
        ;
};
template<class t>
    link_stack<t>::~link_stack(){
        while(top){
            struct node<t> *p= top;
            top=top->next;
            delete p;
        }
    }
template<class t>
    void link_stack<t>::push(t x){
        struct node<t> *p= new node<t>;
        p->data= x;
        p->next= top;
        top=p;
    }
template<class t>
    t link_stack<t>::pop(){
        if(empty()) throw "下溢";
        t x= top->data;
        struct node<t> *p=top;
        top= top->next;
        delete p;
        return x;
    }
class Queen{
    public:
        int x;
        int y;
        Queen(int x_=0,int y_=0){x=x_; y=y_;}
        bool operator==(Queen const& q) const {//重载判等操作符 :其实是看是否冲突
            return (x==q.x)||(y==q.y)||(x+y==q.x+q.y)||(x-y==q.x-q.y);
            }
        bool operator!=(Queen const& q) const {//重载不等
            return !(*this==q);
            } 
    protected:
        ;
};
int main(void){
    link_stack<int> test;
    cout<<"#测试链栈功能"<<endl;
    test.push(1);
    test.push(2);
    cout<<"入栈成功"<<endl;
    cout<<"获取顶部值："<<test.get_top()<<endl;
    cout<<"出栈成功:"<<test.pop()<<endl;
    cout<<"获取顶部值："<<test.get_top()<<endl;
    cout<<"出栈成功:"<<test.pop()<<endl;
    //开始八皇后问题
     
    link_stack<Queen> ans;
    
    Queen q(0,0);
    
    //ans.push(q);
    
    int q_count=0; //记录皇后数量 
    int sum_ans=0; //解数
    do{
    //是否出界: y或者皇后数量>=8
        //出界
        if(q_count>=8 ||q.y>=8){q =ans.pop(); q.y++;q_count--;} //回溯上个解答 然后尝试下列
        //没出界
        else{
            //现在这个皇后符合条件吗？
            while(ans.find(q)&&q.y<8){
                q.y++;
            }
            //找到符合的或者沦为越界
            if(q.y<8) {
                ans.push(q); 
                q_count++;//皇后++
                
                if(q_count>=8){ //如果这是最后一颗期中？
                    sum_ans++; //完整解答++
                    cout<<"#解答";
                    struct node<Queen> * P_= ans.top;
                    for(int i=0;i<8;i++){
                        cout<<"("<<P_->data.x<<","<<P_->data.y<<")";
                        P_=P_->next;
                        }
                    cout<<"#"<<endl;
                }
                q.x++;//去下一行
                q.y= 0;//从头再来
            }
            //越界的情况肯定没法通过循环的
            }
    }
    while((q.x>0)||(q.y<8));
    cout<<"解答个数："<<sum_ans;
    return 0;
}
