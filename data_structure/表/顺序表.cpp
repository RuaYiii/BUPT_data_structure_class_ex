template<class T,int N>
class seqlist{
    public:
        seqlist(){length=0;} //
        seqlist(T a[],int n); //构造
        int get_length();
        T get(int i);
        int locate(T x);
        void insert(int i,T x);//只是插入一个值
        T Delete(int i); //删除值 并且弹出
        void print_ls();
    private:
        T data[N];
        int length;
};
template<class T,int N>
seqlist<T,N>::seqlist(T a[],int n){
    if(n>N) throw "太长了！";
    for(int i=0;i<n;i++){
        data[i]=a[i];
        length=n;
    }
}
template<class T,int N>
void seqlist<T,N>::insert(int i,T x){
    if(i>length+1 || i<1)   throw "位置异常";
    if(length>=N) throw "上溢";
    for(int j=length;j>=i;j--)
        data[j]=data[j-1];
    data[i-1]=x;
    length++;
}
template<class T,int N>
T seqlist<T,N>::Delete(int i){
    if((i<1) || (i>length)) throw "位置异常";
    if(length==0) throw "下溢";
    T t=data[i-1];
    for(int j=i;i<length;j++)
        data[j-1]= data[j];
    length--;
    return t;
}
template<class T,int N>
T seqlist<T,N>::get(int i){
    if(i<1 || i>length) throw "查找位置非法";
    else return data[i-1];
}

template<class T,int N>
int seqlist<T,N>::locate(T x){
    data[0] = x;
    for (int i=length;data[i] != x;i--) ;
    return i;
}

