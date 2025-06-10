#include<bits/stdc++.h>
using namespace std;
double dist(pair<double,double> p1,pair<double,double> p2){
    return sqrt(((p1.first-p2.first)*(p1.first-p2.first))+((p1.second-p2.second)*(p1.second-p2.second)));
}
class Island{ //parent abstract class
    protected:
        vector<int> dimen;  //stores the required coordinates and dimensions of a shape 
        string id;
    public:
        virtual void input(istream &in)=0;
        virtual void output(ostream &out)=0;
        virtual double long_radius()=0;   //virtual function to calcualte the longest radius obtained after rotations
        virtual pair<double,double> centre()=0;
        friend istream &operator>>(istream &in,Island& isl){
            isl.input(in);
            return in;
        }
        friend ostream &operator<<(ostream &out,Island *isl){
            isl->output(out);
            return out;
        }   
};
//child classes
class triangle:public Island{
    public:
        triangle(){

        }
        triangle(string s){
            id=s;
        }
        double long_radius()override{
            double x1=(dimen[0]+dimen[2]+dimen[4])/3.0;
            double y1=(dimen[1]+dimen[3]+dimen[5])/3.0;
            return max(max(dist({dimen[0],dimen[1]},{x1,y1}),dist({dimen[2],dimen[3]},{x1,y1})),dist({dimen[4],dimen[5]},{x1,y1}));
        } 
        pair<double,double>centre() override{
            return {(dimen[0]+dimen[2]+dimen[4])/3.0,(dimen[1]+dimen[3]+dimen[5])/3.0};
        }
        void input(istream &in)override{
            dimen.resize(6);
            for(int i=0;i<6;i++){
                in>>dimen[i];
            }
        }
        void output(ostream &out)override{
            out<<id<<" ";
        }
};
class rectangle:public Island{
    public:
        rectangle(){

        }
        rectangle(string s){
            id=s;
        }
        double long_radius()override{
            double x1=(dimen[0]+dimen[2]+dimen[4]+dimen[6])/4.0;
            double y1=(dimen[1]+dimen[3]+dimen[5]+dimen[7])/4.0;
            return max(max(max(dist({dimen[0],dimen[1]},{x1,y1}),dist({dimen[2],dimen[3]},{x1,y1})),dist({dimen[4],dimen[5]},{x1,y1})),dist({dimen[6],dimen[7]},{x1,y1}));
        }
        pair<double,double> centre()override{
            return {(dimen[0]+dimen[2]+dimen[4]+dimen[6])/4.0,(dimen[1]+dimen[3]+dimen[5]+dimen[7])/4.0};
        }
        void input(istream &in)override{
            dimen.resize(8);
            for(int i=0;i<8;i++){
               cin>>dimen[i];
            }
        }
        void output(ostream &out)override{
            out<<id<<" ";
        }
};
class circle:public Island{
    public:
        circle(){

        }
        circle(string s){
            id=s;
        }
        double long_radius()override{
            return dimen[2];
        }
        pair<double,double> centre ()override{
            return {dimen[0],dimen[1]};
        }
        void input(istream &in)override{
            dimen.resize(3);
            for(int i=0;i<3;i++){
                in>>dimen[i];
            }
        }
        void output(ostream &out)override{
            out<<id<<" ";
        }
};
class simulator{     //creates graph and perfroms dp to calcuate the required outputs
    private:
        vector<vector<int>> grf;  //graph that cpnnects the reachable islands
    public:
        simulator(){

        }
        simulator(int xn){
            grf.resize(xn);
        }
        void create_grf(vector<Island*> &isls){
            for(int i=0;i<isls.size();i++){
               for(int j=i+1;j<isls.size();j++){
                  if(isls[i]->long_radius()+isls[j]->long_radius()+1e-9>=dist(isls[i]->centre(),isls[j]->centre())){
                     grf[i].push_back(j);
                     grf[j].push_back(i);
                  }
               }
            }
        }
        void path(vector<Island*> &isls){   //finds required path
            int sz=grf.size();
            vector<vector<int>> dp((1<<sz),vector<int>(sz,0));
            vector<vector<int>> parent((1<<sz),vector<int>(sz,-1));
            for(int i=0;i<sz;i++){
               dp[1<<i][i]=1;
            }
            for(int mask=0;mask<(1<<sz);mask++){         
               for(int i=0;i<sz;i++){
                  if(!(mask&(1<<i)) || !dp[mask][i]){
                     continue;
                  }
                  for(int j=0;j<grf[i].size();j++){
                     if(!(mask&(1<<grf[i][j]))){
                        dp[mask|(1<<grf[i][j])][grf[i][j]]=1;
                        parent[mask|(1<<grf[i][j])][grf[i][j]]=i;
                     }
                  }
               }
            }
            int msk=(1<<sz)-1;
            bool flag=false;
            int ind=0;
            for(int i=0;i<sz;i++){
               if(dp[msk][i]==1){
                  flag=true;
                  ind=i;
                  break;
               }
            }
            if(flag){
               cout<<"YES\n";
               vector<int> h_path;
                int cur_mask=msk;
                int cur_node = ind;
                while (cur_node != -1) {
                    h_path.push_back(cur_node);
                    int prev = parent[cur_mask][cur_node];
                    cur_mask ^= (1 << cur_node);
                    cur_node = prev;
                }
               for(int i=h_path.size()-1;i>=0;i--){
                  cout<<isls[h_path[i]];
               }
               cout<<"\n";
            }
            else{
               cout<<"NO\n";
               vector<int> l_path;
               int bind=-1;
               int bmsk=-1;
               int mlen=0;
               for(int mk=(1<<sz)-1;mk>=0;mk--){
                   for(int mkk=0;mkk<sz;mkk++){
                       if(dp[mk][mkk]){
                       int cnt=__builtin_popcount(mk);
                       if(mlen<cnt){
                           mlen=cnt;
                           bind=mkk;
                           bmsk=mk;
                       }
                       }
                   }
               }
               int cmask=bmsk;
               int indx=bind;
               while(indx!=-1){
                   l_path.push_back(indx);
                   int par=parent[cmask][indx];
                   cmask^=(1<<indx);
                   indx=par;
               }
               cout<<l_path.size()<<"\n";
               for(int i=l_path.size()-1;i>=0;i--){
                  cout<<isls[l_path[i]];
               }
               cout<<"\n";
            }
        }
};
int main(){
    int no_islands;
    cin>>no_islands;
    vector<Island*> islands;
    for(int i=0;i<no_islands;i++){
        Island* islpoint=nullptr;
        string shape,sid;
        cin>>shape>>sid;
        if(shape=="TRIANGLE"){
            islpoint=new triangle(sid);
        }
        else if(shape=="RECTANGLE"){
            islpoint=new rectangle(sid);
        }
        else if(shape=="CIRCLE"){
            islpoint=new circle(sid);
        }
        if(islpoint){
            cin>>(*islpoint);
            islands.push_back(islpoint);
        }
    }
    simulator sim(no_islands);
    sim.create_grf(islands);
    sim.path(islands);
    return 0;
}