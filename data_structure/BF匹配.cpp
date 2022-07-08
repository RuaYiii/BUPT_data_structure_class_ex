

int seqstring::index(seqstring &t){
    int i=1,j=1;
    while(i<=get_length() && j<=t.get_length()){
        if(get(i)== t.get(j)){i++;j++}
        else{
            i+=2-j; //返回开头 （i-j+1） 向后一下+1
            j=1;
        }
    }
    if(j>t.get_length()) return i+1-j;
    else return -1;
}