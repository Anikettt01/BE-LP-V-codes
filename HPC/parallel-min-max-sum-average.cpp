#include<bits/stdc++.h>
using namespace std;

void first_fit(){
    vector<int>status={0,0,0,0,0};
    vector<int>block={100,500,200,300,600};
    vector<int>processsize={212,417,112,426};
    
    for(int i=0;i<4;i++){
        bool allocated = false;
        for(int j=0;j<5;j++){
            if(status[j]==0 && block[j]>=processsize[i]){
                status[j]=1;
                allocated=true;
                
                cout<<" Process "<<i+1<<" Allocated in Block "<<j+1<<endl;
                break;
            }
        }
        if(allocated == false){
            cout<<" Process "<<i+1<<" Blok not Allocated "<<endl;
        }
    }
}

void best_fit(){
    vector<int>status={0,0,0,0,0};
    vector<int>block={100,500,200,300,600};
    vector<int>processsize={212,417,112,426};
    
    for(int i=0;i<4;i++){
        int best=-1;
        for(int j=0;j<5;j++){
            if(status[j]==0 && block[j]>=processsize[i]){
                if(best == -1 || block[j]<block[best]){
                    best=j;
                }
            }
        }
        if(best != -1){
            status[best]=1;
            cout<<" Process "<<i+1<<" Allocated in Block "<<best+1<<endl;
            
        }
        else{
            cout<<" Process "<<i+1<<" Blok not Allocated "<<endl;
            
        }
    }
    
}

void worst_fit(){
    vector<int>status={0,0,0,0,0};
    vector<int>block={100,500,200,300,600};
    vector<int>processsize={212,417,112,426};
    
    for(int i=0;i<4;i++){
        int worst=-1;
        for(int j=0;j<5;j++){
            if(status[j]==0 && block[j]>=processsize[i]){
                if(worst == -1 || block[j]>block[worst]){
                    worst=j;
                }
            }
        }
        if(worst != -1){
            status[worst]=1;
            cout<<" Process "<<i+1<<" Allocated in Block "<<worst+1<<endl;
            
        }
        else{
            cout<<" Process "<<i+1<<" Blok not Allocated "<<endl;
            
        }
    }
    
}

void next_fit(){
    vector<int>status={0,0,0,0,0};
    vector<int>block={100,500,200,300,600};
    vector<int>processsize={212,417,112,426};
    
    int nextlocation =0;
    for(int i=0;i<4;i++){
        bool allocated=false;
        int count=0;
        while(count<5){
            if(status[nextlocation]==0 && block[nextlocation]>=processsize[i]){
                status[nextlocation]=1;
                allocated=true;
                
                cout<<" Process "<<i+1<<" Allocated in Block "<<nextlocation+1<<endl;
                break;
                
            }
            nextlocation = (nextlocation + 1)%5;
            count++;
        }
        
    }
    
}




int main(){
    cout<<" Fist_fit "<<endl;
    cout<<endl;
    first_fit();
    cout<<endl;
    
    cout<<" Best_fit "<<endl;
    cout<<endl;
    best_fit();
    cout<<endl;
    
    cout<<" Worst_fit "<<endl;
    cout<<endl;
    worst_fit();
    cout<<endl;
    
    cout<<" Next_fit "<<endl;
    cout<<endl;
    next_fit();
    cout<<endl;
}