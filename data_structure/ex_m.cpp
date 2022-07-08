#include <stddef.h>
#include <iostream>
#include<fstream>
using namespace std;

template <class T>
struct dul_node
{
    T data; //存储数据
    struct dul_node<T>* prior, * next; //前驱与后继 --- 灵活变动 就不用中间变量了
};
//双链表
template<class T>
class tongxunlu
{
public:
    tongxunlu();
    tongxunlu(T a[], int n);
    ~tongxunlu();
    int length();
    T get(int);
    int locate(T);
    void insert(T, int);
    T Delete(int);
    dul_node<T>* first;
private:
    //dul_node<T>* first;
};

template<class T> tongxunlu<T>::tongxunlu()
{
    first = new dul_node<T>;
    first->prior = NULL;
    first->next = NULL; //创建一个空链表
}
template<class T> tongxunlu<T>::tongxunlu(T a[], int n)
{
    first = new dul_node<T>;
    dul_node<T>* r = first; //用来移动定位的尾指针
    r->next = NULL;
    r->prior = NULL;
    for (int i = 0; i < n; i++)
    {
        dul_node<T>* s = new dul_node<T>;
        s->data = a[i];
        s->prior = r; //前驱动
        r->next = s;
        r = s;
    }
    r->next = NULL;
};
//析构
template<class T> tongxunlu<T>::~tongxunlu()
{

    while (first != NULL)
    {
        dul_node<T>* p = first;
        first = first->next;
        delete p;
    }//释放内存
}
//定位：需要优化
template<class T> int tongxunlu<T>::locate(T x)
{
    dul_node<T>* p = first->next;
    int j = 1;
    while (p != NULL)
    {
        if (p->data == x) return j;
        p = p->next;
        j++;
    }
}
//查找：注意有可能查不到，记得处理异常
template<class T> T tongxunlu<T>::get(int i)
{
    dul_node<T>* p = first->next;
    int j = 1;
    while (j != i && p != NULL)
    {
        p = p->next;
        j++;
    }
    if (p == NULL) throw "位置非法";
    return p->data;
}
//插入
template<class T> void tongxunlu<T>::insert(T x, int i)
{
    dul_node<T>* p = first;
    int j = 0;//因为在i的位置插入，原有位置的数据将会变成i+1
    while (p != NULL && j != i)
    {
        p = p->next;
        j++;
    } //找到位置n-1;
    if (p == NULL) throw "位置非法";
    else
    {
        dul_node<T>* s = new dul_node<T>;
        s->data = x; //初始化
        s->prior = p->prior;
        s->next = p;//连接原有i位置
        p->prior->next = s;
        p->prior = s;
    }
}
//删除
template<class T> T tongxunlu<T>::Delete(int i)
{
    dul_node<T>* p = first;
    int j = 0;
    while (p != NULL && j != i)
    {
        p = p->next;
        j++;
    } //找到位置n; 不需要中间变量了
    if (p->next == NULL) throw "位置非法";
    else
    {
        p->prior->next = p->next; //null空置
        p->next->prior = p->prior;
        delete p;
    }
}
//长度查询
template<class T> int tongxunlu<T>::length()
{
    dul_node<T>* p = first;
    int i = 0;
    while (p->next != NULL)
    {
        p = p->next;
        i++;
    }
    return i;
}

int main(void)
{
    struct DataType
    {
        int id;      	//编号
        char name[10];	//姓名
        char xb;		//性别
        char phone[13];	//电话
        char addr[31];	//地址
    };

    //菜单
    tongxunlu<DataType> xintxl;

    int a;
    cout << "输入1为新建通讯录\t输入2为查询联系人\t输入0为退出" << ' ';
    cin >> a;
    int i = 0;
    while (a == 1||a==2)
    {
        
        if (a == 1)
        {
            DataType ceshi ;
            if (i == 0)
            {
                cout << "请输入联系人的编号，姓名，性别，电话，地址";
                cin >> ceshi.id;
                cin >> ceshi.name;
                cin >> ceshi.xb;
                cin >> ceshi.phone;
                cin >> ceshi.addr;
                dul_node<DataType>* z = new dul_node<DataType>;
                z->data = ceshi;
                dul_node<DataType>* p = xintxl.first;
                p->next=z;
                i++;
            }
            else
            {
                cout << "请输入联系人的编号，姓名，性别，电话，地址";
                cin >> ceshi.id;
                cin >> ceshi.name;
                cin >> ceshi.xb;
                cin >> ceshi.phone;
                cin >> ceshi.addr;
                xintxl.insert(ceshi, i);
                i++;
            };
            
        }
        else if (a == 2)
        {
            int k;
            cout << "请输入联系人编号";
            cin >> k;
            //查询---暂时只能用编号查询，后续优化
            dul_node<DataType>* x = xintxl.first->next;
            int place = 0;//位置变量
            while (x != NULL)
            {
                if ((x->data).id == k)
                    break;
                cout << (x->data).id << " ";//测试用的
                x = x->next;
                place++;
            }
            //cout << place;//测试
        }
        cout << "输入1为新建通讯录\t输入2为查询联系人\t输入0为退出" << ' ';
        cin >> a;

    }
    if (a != 1 && a != 2 && a != 0)
        cout << "非法输入";
    else if(a==0)
        cout << "已退出";

    ofstream outfile;
    outfile.open("data.txl", ios::out);
    dul_node<DataType>* q = xintxl.first->next;
    while (q != NULL) {
        outfile << (q->data).id << " ";
        outfile << (q->data).name << " ";
        outfile << (q->data).xb << " ";
        outfile << (q->data).phone << " ";
        outfile << (q->data).addr << endl;
        q = q->next;
    }
    outfile.close();
}