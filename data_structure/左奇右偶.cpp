void convert(int A[], int n){
    int i= 0;
    int j= n-1;
    while(i<j){
        while (A[i]%2!=0)  i++;
        while(A[j]%2==0) j--;
        if(i<j){
        int cup=A[i];
        A[i]=A[j];
        A[j]=cup;          
        }
    }
}