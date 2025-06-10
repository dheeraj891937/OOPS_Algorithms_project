#include<bits/stdc++.h>
using namespace std;
class graph{
  public:
    int nv,ne;
    unordered_map<int,set<int>> um;
    void operator+(graph &g){
        for(auto it=g.um.begin();it!=g.um.end();it++){
            if(um.find(it->first)==um.end()){
                um[it->first]=it->second;
                for(auto ixt:it->second){
                    um[ixt].insert(it->first);
                }
                nv++;
            }
            else{
                for(auto itt=it->second.begin();itt!=it->second.end();itt++){
                    if(um[it->first].find(*itt)==um[it->first].end()){
                        um[it->first].insert(*itt);
                        um[*itt].insert(it->first);
                        ne++;
                    }
                }

            }
        }
    }
    void operator-(graph &g){
        unordered_map<int,set<int>> num;
        for(auto it:um){
            for(auto itt:it.second){
                if(g.um.find(it.first)!=g.um.end()&&g.um[it.first].find(itt)!=g.um[it.first].end()){
                    num[it.first].insert(itt);
                }
            }
        }
        for(auto it=g.um.begin();it!=g.um.end();it++){
            if(num.find(it->first)==num.end()){
                num[it->first]={};
            }
        }
        for(auto it=um.begin();it!=um.end();it++){
            if(num.find(it->first)==num.end())
              num[it->first]={};
        }
        um=num;
    }
    void operator!(){
       unordered_map<int,set<int>> cx;
       for(int j=0;j<nv;j++){
           for(int i=0;i<nv;i++){
               if(i!=j&&um[j].find(i)==um[j].end()){
                   cx[j].insert(i);
               }
           }
       }
       for(auto it=um.begin();it!=um.end();it++){
           if(cx.find(it->first)==cx.end()){
               cx[it->first]={};
           }
       }
       um=cx;
       ne=nv*(nv-1)/2-ne;
    }
    void addEdge(int u,int v){
         if(u>=nv||v>=nv){
            return;
         }
         um[u].insert(v);
         um[v].insert(u);
         ne++;
    }
    void removeEdge(int u,int v){
         if(u>=nv||v>=nv){
            return;
         }
         if(um[u].find(v)!=um[u].end()){
            um[u].erase(v);
         }
         if(um[v].find(u)!=um[v].end()){
            um[v].erase(u);
         }
         ne--;
    }
    void dfs(vector<bool>& vstd,int a){
         vstd[a]=true;
         for(auto it=um[a].begin();it!=um[a].end();it++){
            if(vstd[*it]==false){
               vstd[*it]=true;
               dfs(vstd,*it);
            }
         }
    }
    void isReachable(int u,int v){
          vector<bool> visited(nv,false);
          dfs(visited,u);
          if(visited[v]==true){
            cout<<"Yes"<<endl;
          }
          else {
            cout<<"No"<<endl;
          }
    }
    friend istream& operator >> (istream& stream, graph& g);
    friend ostream& operator << (ostream& stream,graph &g );
};
istream& operator >> ( istream& stream,graph& g) {
    cin>>g.nv>>g.ne;
    for(int i=0;i<g.nv;i++){
        g.um[i]={};
    }
    for(int i=0;i<g.ne;i++){
        int x,y;
        cin>>x>>y;
        g.um[x].insert(y);
        g.um[y].insert(x);
    }
    return stream;
}
ostream& operator << (ostream& stream,graph& g){
    int nver=g.um.size();
    for(int i=0;i<nver;i++){
        stream<<"Vertex"<<" "<<i<<":"<<" ";
        priority_queue<int,vector<int>,greater<int>> pq;
        for(auto it=g.um[i].begin();it!=g.um[i].end();it++){
            pq.push(*it);
        }
        while(!pq.empty()){
            stream<<pq.top()<<" ";
            pq.pop();
        }
        stream<<endl;
    }
    return stream;
}
int main(){
   string s="";
   cin>>s;
   graph g;
   cin>>g;

   while(1){
      cin>>s;
      if(s=="union"){
          cin>>s;
         graph g1;
         cin>>g1;
         g+g1;
      }
      else if(s=="intersection"){
          cin>>s;
         graph g1;
         cin>>g1;
         g-g1;
      }
      else if(s=="complement"){
         !g;
      }
      else if(s=="isReachable"){
         int x,y;
         cin>>x>>y;
         g.isReachable(x,y);
      }
      else if(s=="add_edge"){
         int x,y;
         cin>>x>>y;
         g.addEdge(x,y);
      }
      else if(s=="remove_edge"){
         int x,y;
         cin>>x>>y;
         g.removeEdge(x,y);
      }
      else if(s=="printGraph"){
         cout<<g;
      }
      else if(s=="end"){
         break;
      }
   }
   return 0;
}