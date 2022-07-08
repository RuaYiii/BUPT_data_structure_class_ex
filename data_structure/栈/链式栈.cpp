#include <stddef.h>

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
        t get_top();
        bool empty(){return (top==NULL)?true:false;}
    private:
        struct node<t> * top;
};
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

