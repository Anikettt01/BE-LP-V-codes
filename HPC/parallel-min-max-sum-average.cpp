#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

int min_seq(vector<int>&arr){
    int mini=INT_MAX;

    for(int i=0;i<arr.size();i++){
        if(arr[i]<mini) mini=arr[i];
    }

    return mini;
}

int min_par(vector<int>&arr){
    int mini=INT_MAX;

    #pragma omp parallel for reduction(min:mini)
    for(int i=0;i<arr.size();i++){
        if(arr[i]<mini) mini=arr[i];
    }

    return mini;
}

int max_seq(vector<int>&arr){
    int maxi=INT_MIN;

    for(int i=0;i<arr.size();i++){
        if(arr[i]>maxi) maxi=arr[i];
    }

    return maxi;
}

int max_par(vector<int>&arr){
    int maxi=INT_MIN;

    #pragma omp parallel for reduction(max:maxi)
    for(int i=0;i<arr.size();i++){
        if(arr[i]>maxi) maxi=arr[i];
    }

    return maxi;
}

long long sum_seq(vector<int>&arr){
    long long sum=0;

    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }

    return sum;
}

long long sum_par(vector<int>&arr){
    long long sum=0;

    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<arr.size();i++){
        sum+=arr[i];
    }

    return sum;
}

double avg_seq(vector<int>&arr){
    long long sum=sum_seq(arr);
    return (double)sum/arr.size();
}

double avg_par(vector<int>&arr){
    long long sum=sum_par(arr);
    return (double)sum/arr.size();
}

int main(){

    int n=1e7;

    vector<int>arr(n);

    srand(time(0));

    for(int i=0;i<n;i++){
        arr[i]=rand()%100000;
    }

    double t1,t2;

    t1=omp_get_wtime();
    int mn1=min_seq(arr);
    t2=omp_get_wtime();

    cout<<"Sequential Min = "<<mn1<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    int mn2=min_par(arr);
    t2=omp_get_wtime();

    cout<<"Parallel Min = "<<mn2<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    int mx1=max_seq(arr);
    t2=omp_get_wtime();

    cout<<"Sequential Max = "<<mx1<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    int mx2=max_par(arr);
    t2=omp_get_wtime();

    cout<<"Parallel Max = "<<mx2<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    long long s1=sum_seq(arr);
    t2=omp_get_wtime();

    cout<<"Sequential Sum = "<<s1<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    long long s2=sum_par(arr);
    t2=omp_get_wtime();

    cout<<"Parallel Sum = "<<s2<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    double a1=avg_seq(arr);
    t2=omp_get_wtime();

    cout<<"Sequential Average = "<<a1<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl<<endl;

    t1=omp_get_wtime();
    double a2=avg_par(arr);
    t2=omp_get_wtime();

    cout<<"Parallel Average = "<<a2<<endl;
    cout<<"Time = "<<t2-t1<<" sec"<<endl;
}