#include <stddef.h>
#include <iostream>
#include<fstream>
using namespace std;

template <class T>
struct dul_node
{
    T data; //�洢����
    struct dul_node<T>* prior, * next; //ǰ������ --- ���䶯 �Ͳ����м������
};
//˫����
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
    first->next = NULL; //����һ��������
}
template<class T> tongxunlu<T>::tongxunlu(T a[], int n)
{
    first = new dul_node<T>;
    dul_node<T>* r = first; //�����ƶ���λ��βָ��
    r->next = NULL;
    r->prior = NULL;
    for (int i = 0; i < n; i++)
    {
        dul_node<T>* s = new dul_node<T>;
        s->data = a[i];
        s->prior = r; //ǰ����
        r->next = s;
        r = s;
    }
    r->next = NULL;
};
//����
template<class T> tongxunlu<T>::~tongxunlu()
{

    while (first != NULL)
    {
        dul_node<T>* p = first;
        first = first->next;
        delete p;
    }//�ͷ��ڴ�
}
//��λ����Ҫ�Ż�
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
//���ң�ע���п��ܲ鲻�����ǵô����쳣
template<class T> T tongxunlu<T>::get(int i)
{
    dul_node<T>* p = first->next;
    int j = 1;
    while (j != i && p != NULL)
    {
        p = p->next;
        j++;
    }
    if (p == NULL) throw "λ�÷Ƿ�";
    return p->data;
}
//����
template<class T> void tongxunlu<T>::insert(T x, int i)
{
    dul_node<T>* p = first;
    int j = 0;//��Ϊ��i��λ�ò��룬ԭ��λ�õ����ݽ�����i+1
    while (p != NULL && j != i)
    {
        p = p->next;
        j++;
    } //�ҵ�λ��n-1;
    if (p == NULL) throw "λ�÷Ƿ�";
    else
    {
        dul_node<T>* s = new dul_node<T>;
        s->data = x; //��ʼ��
        s->prior = p->prior;
        s->next = p;//����ԭ��iλ��
        p->prior->next = s;
        p->prior = s;
    }
}
//ɾ��
template<class T> T tongxunlu<T>::Delete(int i)
{
    dul_node<T>* p = first;
    int j = 0;
    while (p != NULL && j != i)
    {
        p = p->next;
        j++;
    } //�ҵ�λ��n; ����Ҫ�м������
    if (p->next == NULL) throw "λ�÷Ƿ�";
    else
    {
        p->prior->next = p->next; //null����
        p->next->prior = p->prior;
        delete p;
    }
}
//���Ȳ�ѯ
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
        int id;      	//���
        char name[10];	//����
        char xb;		//�Ա�
        char phone[13];	//�绰
        char addr[31];	//��ַ
    };

    //�˵�
    tongxunlu<DataType> xintxl;

    int a;
    cout << "����1Ϊ�½�ͨѶ¼\t����2Ϊ��ѯ��ϵ��\t����0Ϊ�˳�" << ' ';
    cin >> a;
    int i = 0;
    while (a == 1||a==2)
    {
        
        if (a == 1)
        {
            DataType ceshi ;
            if (i == 0)
            {
                cout << "��������ϵ�˵ı�ţ��������Ա𣬵绰����ַ";
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
                cout << "��������ϵ�˵ı�ţ��������Ա𣬵绰����ַ";
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
            cout << "��������ϵ�˱��";
            cin >> k;
            //��ѯ---��ʱֻ���ñ�Ų�ѯ�������Ż�
            dul_node<DataType>* x = xintxl.first->next;
            int place = 0;//λ�ñ���
            while (x != NULL)
            {
                if ((x->data).id == k)
                    break;
                cout << (x->data).id << " ";//�����õ�
                x = x->next;
                place++;
            }
            //cout << place;//����
        }
        cout << "����1Ϊ�½�ͨѶ¼\t����2Ϊ��ѯ��ϵ��\t����0Ϊ�˳�" << ' ';
        cin >> a;

    }
    if (a != 1 && a != 2 && a != 0)
        cout << "�Ƿ�����";
    else if(a==0)
        cout << "���˳�";

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