#include<bits/stdc++.h>
using namespace std;
//parent class
class event{
    protected:
        int start;
        int end;
    public:
        virtual double cal_profit()=0; 
        virtual void input(istream &in)=0;
        virtual int getend()=0;
        virtual int getstart()=0;
        friend istream &operator>>(istream &in,event &isl){
            isl.input(in);
            return in;
        }
};
//child classes
class concert:public event{
    private:
        int tprice;   //ticket price
        int tsold;    //no of tickets sold
        int artistfee;
        int log_cost;   //logistic cost
    public:
        concert(){

        }
        concert(int s,int e,int tp,int ts,int af,int lc){
            start=s;
            end=e;
            tprice=tp;
            tsold=ts;
            artistfee=af;
            log_cost=lc;
        }
        void input(istream &in)override{
            int s,e,tp,ts,af,lc;
            in>>s>>e>>tp>>ts>>af>>lc;
            start=s;
            end=e;
            tprice=tp;
            tsold=ts;
            artistfee=af;
            log_cost=lc;
        }
        int getend()override{
            return end;
        }
        int getstart()override{
            return start;
        }
        double cal_profit()override{
            double tickt_rev=tprice*tsold;
            tickt_rev=tickt_rev-(0.18*tickt_rev);
            double cost=artistfee+log_cost;
            double prft=tickt_rev-cost;
            return (prft>2*cost)?0.7*prft:prft;
        }
};
class theatreshow:public event{
    private:
        int baseprice;
        int totalseats;
        int venuecost;
    public:
        theatreshow(){

        }
        theatreshow(int s,int e,int bp,int ts,int vc){
            start=s;
            end=e;
            baseprice=bp;
            totalseats=ts;
            venuecost=vc;
        }
        void input(istream &in)override{
            int s,e,bp,ts,vc;
            in>>s>>e>>bp>>ts>>vc;
            start=s;
            end=e;
            baseprice=bp;
            totalseats=ts;
            venuecost=vc;
        }
        int getend()override{
            return end;
        }
        int getstart()override{
            return start;
        }
        double cal_profit()override{
            double tickt_rev=0.25 * totalseats * (2 * baseprice) + 0.75 * totalseats * baseprice;
            tickt_rev=tickt_rev-(0.18*tickt_rev);
            double pop_rev=0.25*150*totalseats;
            double prft=tickt_rev+pop_rev-venuecost;
            return prft;
        }
};
class wedding:public event{
    private:
        int baseamnt;  //base amount
        int deccost;  //decoration cost
        int guestcnt;  //guest counnt
        int venuecost;
    public:
        wedding(){

        }
        wedding(int s,int e,int ba,int dc,int gc,int vc){
            start=s;
            end=e;
            baseamnt=ba;
            deccost=dc;
            guestcnt=gc;
            venuecost=vc;
        }
        void input(istream &in)override{
            int s,e,ba,dc,gc,vc;
            in>>s>>e>>ba>>dc>>gc>>vc;
            start=s;
            end=e;
            baseamnt=ba;
            deccost=dc;
            guestcnt=gc;
            venuecost=vc;
        }
        int getend()override{
            return end;
        }
        int getstart()override{
            return start;
        }
        double cal_profit()override{
            double tvc=(guestcnt > 200) ? venuecost*3 : venuecost;  //total venue cost
            double cat_cost=(guestcnt > 100) ? guestcnt * 70 :  guestcnt * 100 ;//catering cost
            double prft=baseamnt-deccost-tvc-cat_cost;
            return prft;
        }
};
//custom comparator class to sort events based on end times
class comparator{
    public:
        bool operator()(event* a,event* b){
            return a->getend()<b->getend();
        }
};
//scheduler class
class event_scheduler{
    private:
        vector<event*> evnts;  //vector of events* objects
    public:
        event_scheduler(){

        }
        event_scheduler(vector<event*> &vec){
            evnts=vec;
        }
        double max_profit(){    //function that returns max profit
            vector<event*> ets=evnts;
            sort(ets.begin(),ets.end(),comparator());
            vector<int> e(evnts.size(),-1);   //contains index of the right most inetrval in sorted vector which is nompatible with that interval
            vector<double> dp(evnts.size()+1,0);
            dp[1]=ets[0]->cal_profit();
            for(int k=evnts.size()-1;k>=1;k--){
                int l=0,h=k-1;
                while(l<=h){
                    int mid=l+(h-l)/2;           //performs binary search to find the vector e
                    if(ets[k]->getstart()>=ets[mid]->getend()){
                        l=mid+1;
                    }
                    else if(ets[k]->getstart()<ets[mid]->getend()){
                        h=mid-1;
                    }
                }
                e[k]=h;
            }
            for(int i=2;i<=evnts.size();i++){
                if(dp[e[i-1]]==-1)dp[i]=max(dp[i-1],ets[i-1]->cal_profit());
                else dp[i]=max(dp[i-1],ets[i-1]->cal_profit()+dp[e[i-1]+1]);
            }
            return dp[evnts.size()];
        }
};
int main(){
    int n;    //no of events
    cin>>n;
    event* ptr=nullptr;  //points to one of the child 
    vector<event*> events;  //stores all events
    while(n--){
        int type;   //type of event
        cin>>type;
        if(type==1){
            ptr=new concert();
        }
        else if(type==2){
            ptr=new theatreshow();
        }
        else if(type==3){
            ptr=new wedding();
        }
        if(ptr){
            cin>>*ptr;
            events.push_back(ptr);
        }
    }
    event_scheduler evnt_sdlr(events);
    cout << fixed << setprecision(2) << evnt_sdlr.max_profit() << "\n";
    return 0;
}


