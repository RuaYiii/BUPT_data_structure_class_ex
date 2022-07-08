void seqstring::get_next_array(seqstring &t,int * & next){
    //如果第j哥字符不符合，则回溯到哪个位置（next[j]）
    //next: 
        //0 j=1
        //1 j>=2 且不满足条件的前缀子串
        //K+1; j>2 且满足条件
    int *next= new int[t.get_length()+1]; //index 0的位置不使用

    next[1]=0;
    next[2]=1;
    int j,p=1;
    for(j=3;j<=t.get_length();j++){
        while(p>1 &&t.get(p)!=t.get(j-1)){
            p=next[p]; //回退到上一步
        if(t.get(p)==t.get(j-1))
        p++;
        }
        next[j]=p;
    }
}
//构建next数字
int seqstring::KMP(seqstring &t){
    int *next;
    get_next_array(t,next);
    int i=1;j=1;
    while(i<get_length() && j<=t.get_length()){
        if(get(i) == t.get(j)){i++;j++}
        else if(!next[j]){
            i++;j=1;//next为0的时候，i后移一位，j回到开始
        }
        else{
            j=next[j]; //回到合适的数组
        }
    }
    delete [] next;
    if(j>t.get_length()) return i+1-j;
    else return -1;
}