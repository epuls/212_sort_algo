#include<iostream>
#include<vector>
using namespace std;
void mergeem(int L,int M,int R,vector<int>& array1){
    //vector<int>
    int a1= M-L+1;
    int a2= R-M;
    //int a=0,b=,c=L;
    vector<int> left(a1); //temp array 1
    vector<int> right(a2);//temp array 2
    for(int i=0;i<a1;i++){
        left[i]=array1[L+i];
    }for(int j=0;j<a2;j++){
        right[j]=array1[M+1+j];
    }
    int a=0,b=0,c=L;// put temp array back to original array
    for(;a<a1 && b<a2;c++){
        if(left[a]<=right[b]){
            array1[c]=left[a];
            a++;
        }else{
            array1[c]=right[b];
            b++;
        }
    }
    for(;a<a1;a++,c++){// copies remaining ints from left and right
        array1[c]=left[a];
        //c++;
    }for(;b<a2;b++,c++){
        array1[c]=right[b];
    }
}
void mergesort(int L,int R,vector<int>& array1){
    if(L<R){
        int M=L+(R-L)/2;
        mergesort(L,M,array1);
        mergesort(M+1,R,array1);
        mergeem(L,M,R,array1);
    }
}
int main(){
    vector<int> array1={12, 11, 13, 5, 6, 7};
    cout<<"inputed array "<<endl;
    for(int n:array1){
        cout<<n<<" ";
    }
    cout<<endl;
    mergesort(0,array1.size()-1,array1);
    cout<<"sorted "<<endl;
    for(int n:array1){
        cout<<n<<" ";
    }
    cout<<endl;
    return 0;
}
