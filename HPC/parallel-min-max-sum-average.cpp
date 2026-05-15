#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void minimum_seq(vector<int>&arr){
    int mini=INT_MAX;
    for(int i=0;i<arr.size();i++){
        if(arr[i]<mini) mini=arr[i];
    }
    cout<<" Minimun Sequential: "<<mini<<endl;
}

void minimum_par(vector<int>&arr){
    int mini=INT_MAX;
    #pragma omp parallel for reduction(min:mini)
    for(int i=0;i<arr.size();i++){
        if(arr[i]<mini) mini=arr[i];
    }
    cout<<" Minimun Parallel: "<<mini<<endl;
}

void maximum_seq(vector<int>&arr){
    int maxi=INT_MIN;
    for(int i=0;i<arr.size();i++){
        if(arr[i]>maxi) maxi=arr[i];
    }
    cout<<" Maximum Sequential: "<<maxi<<endl;
}

void maximum_par(vector<int>&arr){
    int maxi=INT_MIN;
     #pragma omp parallel for reduction(max:maxi)
    for(int i=0;i<arr.size();i++){
        if(arr[i]>maxi) maxi=arr[i];
    }
    cout<<" maximum parallel: "<<maxi<<endl;
}

int sum_seq(vector<int>&arr){
    long long sum=0;
    
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }
    cout<<"sum_sequential: "<<sum<<endl;
    return sum;
}

int sum_par(vector<int>&arr){
    long long sum=0;
    #pragma omp parallel for reduction(+:sum)
    
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }
    cout<<"sum_parallel: "<<sum<<endl;
    return sum;
}

void average_seq(vector<int>&arr){
    long long sum=sum_seq(arr);
    cout<<"average_sequential: "<<(double)sum/arr.size()<<endl;
}

void average_par(vector<int>&arr){
    long long sum=sum_par(arr);
    cout<<"average_parallel: "<<(double)sum/arr.size()<<endl;
}

int main(){
    int n=100000;
    
    vector<int>arr(n);
    
    for(int i=0;i<arr.size();i++){
        arr[i]=rand()%1000;
    }
    double t1 ,t2;
    
    t1=omp_get_wtime();
    minimum_seq(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    minimum_par(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    maximum_seq(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    maximum_par(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    sum_seq(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    sum_par(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    average_seq(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
    
    t1=omp_get_wtime();
    average_par(arr);
    t2=omp_get_wtime();
    cout<<"time: "<<t2-t1<<endl;
}
