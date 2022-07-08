#include<iostream>

using namespace std;
const int stack_size = 1024;
template<class t>
class seq_stack{
    public:
        seq_stack(){top=-1;}
        void push(t x);
        t pop();
        t get_top();
        bool empty();
    protected:
        t data[stack_size];
        int top;
};
template<class t>
    void seq_stack<t>::push(t x){ //入栈
        if(top>=stack_size-1) throw "上溢";
        top++;
        data[top]=x;
    }
template<class t>
    t seq_stack<t>::pop(){ //出栈
        if(empty()) throw "下溢";
        top--;
        return data[top+1];
    }
template<class t>
    t seq_stack<t>::get_top(){
        if(empty()) throw "下溢";
        return data[top];
    }
template<class t>
    bool seq_stack<t>::empty(){
        if(top==-1) return true;
        return false;
    }
seq_stack<int> test(void){
    //输入一个十进制
    int dec_;
    cin>>dec_;
    seq_stack<int> ans;
    while(dec_){ //啥时候到0就结束
        ans.push(dec_%2); //余二的结果压栈
        dec_ /=2; 
    }
    //输出结果，刚好就是倒叙输出
    while(!ans.empty()){
        cout<<ans.pop();
    }
    
}