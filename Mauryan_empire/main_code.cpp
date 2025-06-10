#include<bits/stdc++.h>
using namespace std;
int cnt_sena,cnt_danda,cnt_chatur;
class Sentinel{   //sentinel info class
  protected:
    int id;
    string name;
    string rank;
  public:
    virtual int countHigherRanked()=0;
    virtual string getrank()=0;
    virtual int getid()=0;
};
//child classes
class Senapathi: public Sentinel{
  public:
    Senapathi(){

    }
    Senapathi(int idn,string nam,string rnk){
        id=idn;
        name=nam;
        rank=rnk;
    }
    int countHigherRanked() override{
        return 0;
    }
    string getrank() override{
        return rank;
    }
    int getid(){
        return id;
    }
};
class Dandanayaka: public Sentinel{
  public:
    Dandanayaka(){

    }
    Dandanayaka(int idn,string nam,string rnk){
        id=idn;
        name=nam;
        rank=rnk;
    }
    int countHigherRanked() override{
        return cnt_sena;
    }
    string getrank() override{
        return rank;
    }
    int getid(){
        return id;
    }
};
class Chaturangini: public Sentinel{
  public:
    Chaturangini(){

    }
    Chaturangini(int idn,string nam,string rnk){
        id=idn;
        name=nam;
        rank=rnk;
    }
    int countHigherRanked() override{
        return cnt_danda+cnt_sena;
    }
    string getrank() override{
        return rank;
    }
    int getid(){
        return id;
    }
};
class comparerank{          //custom comparator
  public:
    bool operator()(Sentinel* s1,Sentinel* s2){
        if(s1->getrank()>s2->getrank()){
            return true;
        }
        if(s1->getrank()<s2->getrank()){
            return false;
        }
        return s1->getid()<s2->getid();
    }
};
template<typename T>
class Kingdom{
  private:
    vector<vector<int>> grf;   //kingdom graph
    vector<T> sentdent;   //sentinel at nodes
  public:
    Kingdom(){

    }
    Kingdom(int vers){
        grf.resize(vers);
        sentdent.resize(vers);
        cnt_sena=0;
        cnt_danda=0;
        cnt_chatur=0;
    }
    void add_road(int u,int v){
        grf[u].push_back(v);
        grf[v].push_back(u);
    }
    void setsent(int ind,string s1,string s2){  //s1 is name and s2 is rank
        T snt=nullptr;
        if(s2=="SENAPATI"){
            snt=new Senapathi(ind,s1,s2);
            cnt_sena++;
        }
        else if(s2=="DANDANAYAKA"){
            snt=new Dandanayaka(ind,s1,s2);
            cnt_danda++;
        }
        else {
            snt=new Chaturangini(ind,s1,s2);
            cnt_chatur++;
        }
        sentdent[ind]=snt;
    }
    int rec(vector<vector<int>> &dpp,int iind,int take,int par){
        if(iind>=grf.size()){
            return INT_MAX;
        }
        if(dpp[iind][take]!=-1){
            return dpp[iind][take];
        }
        int cnt=0;
        for(int i=0;i<grf[iind].size();i++){
            if(grf[iind][i]==par)continue;
            if(!take){
                cnt+= rec(dpp,grf[iind][i],1,iind);
            }
            else{
                cnt+= min(rec(dpp,grf[iind][i],1,iind),rec(dpp,grf[iind][i],0,iind));
            }
        }
        return dpp[iind][take]=(take?cnt+1:cnt);                
    }
    int min_vertex_cover(){
        vector<vector<int>> dp(grf.size(),vector<int>(2,-1));
        return min(rec(dp,0,1,-1),rec(dp,0,0,-1));
    }
    void sntsorted(){
        vector<T> dupe=sentdent;
        sort(dupe.begin(),dupe.end(),comparerank());
        for(int i=0;i<sentdent.size();i++){
            cout<<dupe[i]->getid()<<" ";
        }
        cout<<"\n";
    }
    int higherrank_cnt(int tid){  //for the count of sentinels with a higher rank than the sentinel with the given ID
        T snt=nullptr;
        string stemp=sentdent[tid]->getrank();
        if(stemp=="SENAPATI"){
            snt=new Senapathi();
            return snt->countHigherRanked();
        }
        else if(stemp=="DANDANAYAKA"){
            snt=new Dandanayaka();
            return snt->countHigherRanked();
        }
        else{
            snt=new Chaturangini();
            return snt->countHigherRanked();
        }
    }
};
int main(){
    int cnt_ver;
    cin>>cnt_ver;
    Kingdom<Sentinel*> kingdom(cnt_ver);
    for(int i=0;i<cnt_ver-1;i++){
        int u1,u2;
        cin>>u1>>u2;
        kingdom.add_road(u1,u2);
    }
    for(int i=0;i<cnt_ver;i++){
        string s1,s2;
        cin>>s1>>s2;
        kingdom.setsent(i,s1,s2);
    }
    int cnt_que;
    cin>>cnt_que;
    while(cnt_que--){
        int type;
        cin>>type;
        if(type==1){   // Output the minimum number of active sentinels required
            cout<<kingdom.min_vertex_cover()<<"\n";
        }
        else if(type==2){   //Output a sorted list of all sentinels based on rank
            kingdom.sntsorted();
        }
        else if(type==3){   //Output the count of sentinels with a higher rank than the sentinel with the given ID
            int t_id;
            cin>>t_id;
            cout<<kingdom.higherrank_cnt(t_id)<<"\n";
        }
    }
    return 0;
}