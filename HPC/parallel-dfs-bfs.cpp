#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void bfss(int start,vector<vector<int>>&adj,vector<int>&visited){
    queue<int>q;
    visited[start]=1;
    q.push(start);
    while(!q.empty()){
        int node=q.front();
        q.pop();
        for(int i:adj[node]){
            if(!visited[i]){
                visited[i]=1;
                q.push(i);
            }
        }
    }
}

void bfsp(int start,vector<vector<int>>&adj,vector<int>&visited){
    queue<int>q;
    q.push(start);
    visited[start]=1;
    while(!q.empty()){
        int size=q.size();
        #pragma omp parallel for
        for(int i=0;i<size;i++){
            int node;
            #pragma omp critical
            {
                node=q.front();
                q.pop();
            }
            for(int i:adj[node]){
                if(!visited[i]){
                    #pragma omp critical
                    {
                        if(!visited[i]){
                            visited[i]=1;
                            q.push(i);
                        }
                    }
                }
            }
        }
    }
}

void dfss(int start,vector<vector<int>>&adj,vector<int>&visited){
    visited[start]=1;
    for(int i:adj[start]){
        if(!visited[i]){
            dfss(i,adj,visited);
        }
    }
}

void dfsp(int start,vector<vector<int>>&adj,vector<int>&visited){
    
    for(int i:adj[start]){
        bool flag=false;
        #pragma omp critical
        {
            if(!visited[i]){
                visited[i]=1;
                flag=true;
            }
        }
        if(flag){
            #pragma omp task
            dfsp(i,adj,visited);
        }
    }
    #pragma omp taskwait
}

int main(){
    int v;
    cout<<"total vertices: ";
    cin>>v;
    
    vector<vector<int>>adj(v);
    for(int i=0;i<v;i++){
        for(int j=0;j<5;j++){
            int node=rand()%v;
            if(i!=node){
                adj[i].push_back(node);
                adj[node].push_back(i);
            }
        }
    }
    
    omp_set_num_threads(4);
    
    vector<int>visited(v,0);
    
    double start1=omp_get_wtime();
    bfss(0,adj,visited);
    double end1=omp_get_wtime();
    
    visited.assign(v,0);
    double start2=omp_get_wtime();
    bfsp(0,adj,visited);
    double end2=omp_get_wtime();
    
    visited.assign(v,0);
    double start3=omp_get_wtime();
    dfss(0,adj,visited);
    double end3=omp_get_wtime();
    
    visited.assign(v,0);
    visited[0]=1;
    double start4=omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            dfsp(0,adj,visited);
        }
    }
    double end4=omp_get_wtime();
    
    cout<<"BFS Sequential Time: "<<(end1-start1)*1e6<<endl;
    cout<<"BFS Parallel Time: "<<(end2-start2)*1e6<<endl;
    cout<<"DFS Sequential Time: "<<(end3-start3)*1e6<<endl;
    cout<<"DFS Parallel Time: "<<(end4-start4)*1e6<<endl;
    
    return 0;
}