#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int n;

void print(vector<int>temp){
    for(int i:temp) cout<<i<<" ";
    cout<<endl;
    
}

void bubbles(vector<int>&arr){
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}

void bubblep(vector<int>&arr){
    for(int i=0;i<n;i++){
        int startIndex=i%2;
        #pragma omp parallel for
        for(int j=startIndex;j<n-1;j+=2){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}

void merge(vector<int>&arr,int left, int mid,int right){
    vector<int>arr1(arr.begin()+left,arr.begin()+mid+1);
    vector<int>arr2(arr.begin()+mid+1,arr.begin()+right+1);
    
    int i=0,j=0,k=left;
    while(i<arr1.size() && j<arr2.size()){
        if(arr1[i]<=arr2[j]){
            arr[k]=arr1[i];
            i++;
            k++;
        }
        else{
            arr[k]=arr2[j];
            j++;
            k++;
        }
    }
    while(i<arr1.size()){
        arr[k]=arr1[i];
        i++;
        k++;
    }
    while(j<arr2.size()){
        arr[k]=arr2[j];
        j++;
        k++;
    }
}

void merges(vector<int>&arr,int left,int right){
    if(left>=right) return;
    int mid=(left+right)/2;
    merges(arr,left,mid);
    merges(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void mergep(vector<int>&arr,int left,int right){
    if(left>=right)return;
    if(right-left<1000){
        merges(arr,left,right);
        return;
    }
    int mid=(right+left)/2;
    #pragma omp task shared(arr)
    mergep(arr,left,mid);
    #pragma omp task shared(arr)
    mergep(arr,mid+1,right);
    #pragma omp taskwait
    merge(arr,left,mid,right);
}

int main(){
    // int n;
    cout<<"n: ";
    cin>>n;
    
    vector<int>arr(n);
    for(int i=0;i<n;i++){
        arr[i]=rand()%10000;
    }
    
    cout<<"Original Array: ";
    for(int i:arr) cout<<arr[i]<<" ";
    cout<<endl;
    
    omp_set_num_threads(4);
    
    vector<int>temp=arr;
    double t1=omp_get_wtime();
    bubbles(temp);
    double t2=omp_get_wtime();
    cout<<"Bubble sort: ";
    print(temp);
    
    temp=arr;
    double t3=omp_get_wtime();
    bubblep(temp);
    double t4=omp_get_wtime();
    cout<<"Bubble parallel: ";
    print(temp);
    
    temp=arr;
    double t5=omp_get_wtime();
    merges(temp,0,n-1);
    double t6=omp_get_wtime();
    cout<<"merge seq: ";
    print(temp);
    
    temp=arr;
    double t7=omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergep(temp,0,n-1);
        }
    }
    double t8=omp_get_wtime();
    cout<<"merge parallel: ";
    print(temp);
    
    cout<<"Bubble sequential time: "<<(t2-t1)*1e6<<endl;
    cout<<"Bubble parallel time: "<<(t4-t3)*1e6<<endl;
    cout<<"merge sequential time: "<<(t6-t5)*1e6<<endl;
    cout<<"merge parallel time: "<<(t8-t7)*1e6<<endl;
    
}