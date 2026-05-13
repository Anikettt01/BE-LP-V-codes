#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

void bfss(int start,vector<vector<int>>&adj,vector<int>&visited){
    visited[start]=1;
    queue<int>q;
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
    visited[start]=1;
    queue<int>q;
    q.push(start);
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

void dfsp(int start,vector<vector<int>>&adj,vector<int>&visited,int depth){

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

            if(depth<3){

                #pragma omp task
                dfsp(i,adj,visited,depth+1);

            }
            else{
                dfsp(i,adj,visited,depth+1);
            }
        }
    }

    #pragma omp taskwait
}

int v=10000;

int main(){
    vector<vector<int>>adj(v);
    for(int i=0;i<v;i++){
        for(int j=0;j<5;j++){
            int node = rand()%v;
            if(i!=node){
                adj[node].push_back(i);
                adj[i].push_back(node);
            }
        }
    }
    
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
    double start4=omp_get_wtime();
    visited[0]=1;
    #pragma omp parallel
    {
        #pragma omp single
        {
            dfsp(0,adj,visited,0);
        }
    }
    double end4=omp_get_wtime();
    
    cout<<"bfs sequential: "<<end1-start1<<endl;
    cout<<"bfs parallel: "<<end2-start2<<endl;
    cout<<"dfs sequential: "<<end3-start3<<endl;
    cout<<"dfs parallel: "<<end4-start4<<endl;
}