#include<bits/stdc++.h>
#include<omp.h>
using namespace std;
using namespace std::chrono_literals;

int n=20000;

void bubbles(vector<int>&arr){
    for(int i=0;i<n;i++){
        std::this_thread::sleep_for(100us);
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
        }
    }
}

void bubblep(vector<int>&arr){
    #pragma omp parallel
    {
        for(int i=0;i<n;i++){
            int startIndex=i%2;
            #pragma omp for
            for(int j=startIndex;j<n-1;j+=2){
                if(arr[j]>arr[j+1]) swap(arr[j],arr[j+1]);
            }
        }
    }
}

void merge(vector<int>&arr,int left,int mid,int right){
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

void merges(vector<int>&arr,int left, int right){
    if(left>=right) return;
    int mid=(left+right)/2;
    merges(arr,left,mid);
    merges(arr,mid+1,right);
    merge(arr,left,mid,right);
}

void mergep(vector<int>&arr,int left,int right){
    if(left>=right) return;
    if(right-left<1000){
        merges(arr,left,right);
        return;
    }
    int mid=(left+right)/2;
    #pragma omp task shared(arr)
    mergep(arr,left,mid);
    #pragma omp task shared(arr)
    mergep(arr,mid+1,right);
    #pragma omp taskwait
    merge(arr,left,mid,right);
}

int main(){
    vector<int>arr(n);
    for(int i=0;i<n;i++) arr[i]=rand()%10000;
    
    vector<int>temp1=arr;
    double start1=omp_get_wtime();
    bubbles(temp1);
    double end1=omp_get_wtime();
    
    vector<int>temp2=arr;
    double start2=omp_get_wtime();
    bubblep(temp2);
    double end2=omp_get_wtime();
    
    vector<int>temp3=arr;
    double start3=omp_get_wtime();
    merges(temp3,0,n-1);
    double end3=omp_get_wtime();
    
    vector<int>temp4=arr;
    double start4=omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            mergep(temp4,0,n-1);    
        }
    }
    double end4=omp_get_wtime();
    
    cout<<"Sequential bubble time: "<<end1-start1<<endl;
    cout<<"parallel bubble time: "<<end2-start2<<endl;
    cout<<"Sequential merge time: "<<end3-start3<<endl;
    cout<<"parallel merge time: "<<end4-start4<<endl;
    
}