#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

vector<int> start(int n){
    vector<int> arr(n);
    for(int i=0;i<n;i++) arr[i]=rand()%100;
    return arr;
}

void print(vector<int>&arr){
    for(int i=0;i<arr.size();i++) cout<<arr[i]<<" ";
    cout<<endl;
}

void bubble_s(vector<int>&arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        } 
    }
}

void bubble_p(vector<int>&arr){
    int n=arr.size();
    for(int i=0;i<n;i++){
        int startIndex=i%2;
        #pragma omp parallel for
        for(int j=startIndex;j<n-1;j+=2)
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
    }
}

void merge(vector<int>&arr,int left,int mid,int right){
    vector<int> arr1(arr.begin()+left,arr.begin()+mid+1);
    vector<int> arr2(arr.begin()+mid+1,arr.begin()+right+1);

    int i=0,j=0,k=left;

    while(i < arr1.size() && j < arr2.size()){
        if(arr1[i] <= arr2[j]){
            arr[k] = arr1[i];
            i++;
        }else{
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    while(i < arr1.size()){
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while(j < arr2.size()){
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void merge_s(vector<int>&arr,int left,int right){
    if(left>=right) return;
    int mid=(left+right)/2;
    merge_s(arr,left,mid);
    merge_s(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void merge_p(vector<int>&arr){
    int n=arr.size();
    for(int width=1;width<n;width*=2){
        #pragma omp parallel for
        for(int i=0;i<n;i+=2*width){
            int left=i;
            int mid=min(i+width-1,n-1);
            int right=min(i+2*width-1,n-1);
            if(mid<right) merge(arr,left,mid,right);
        }
    }
}

int main(){
    int n=20;
    // omp_set_num_threads(4);

    auto originalArray=start(n);
    cout<<"Original:"<<endl;
    print(originalArray);

    auto bubbleSeq=originalArray;
    double t1=omp_get_wtime();
    bubble_s(bubbleSeq);
    double t2=omp_get_wtime();
    cout<<"Bubble seq:"<<endl; 
    print(bubbleSeq);

    auto bubblePar=originalArray;
    double t3=omp_get_wtime();
    bubble_p(bubblePar);
    double t4=omp_get_wtime();
    cout<<"Bubble par:<<endl"; 
    print(bubblePar);

    auto mergeSeq=originalArray;
    double t5=omp_get_wtime();
    merge_s(mergeSeq,0,n-1);
    double t6=omp_get_wtime();
    cout<<"Merge seq:<<endl"; 
    print(mergeSeq);

    auto mergePar=originalArray;
    double t7=omp_get_wtime();
    merge_p(mergePar);
    double t8=omp_get_wtime();
    cout<<"Merge par:<<endl"; 
    print(mergePar);

    cout<<"Bubble seq "<<(t2-t1)*1e6<<endl;
    cout<<"Bubble par "<<(t4-t3)*1e6<<endl;
    cout<<"Merge seq "<<(t6-t5)*1e6<<endl;
    cout<<"Merge par "<<(t8-t7)*1e6<<endl;
}
