#include <bits/stdc++.h>
using namespace std;
#define int long long int
vector<bool> prime10pow(1000001, true);
const int N = 1000000;
void primesunder() {
    prime10pow[0]=false;
    prime10pow[1] =false;
    for(int i=2;i*i<=N;i++) {
        if(prime10pow[i]){
            for(int j=i*i;j<=N;j+=i){
                prime10pow[j]=false;
            }
        }
    }
}
vector<bool> largeprimes(int l,int r) {
    vector<bool> vec(r-l+1,true);
    if(l==1)vec[0]=false;
    for (int it=2;it*it<=r;it++){
        if(!prime10pow[it]) continue;
        int j=max(it*it,(l+it-1)/it*it);
        while(j<=r){
            vec[j-l]=false;
            j+=it;
        }
    }
    return vec;
}
int partition(vector<int> &v,int l,int h) {
    int pivot=v[h];
    int i=l-1;
    for (int j=l;j<h;j++) {
        if (v[j] < pivot) {
            i++;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[h]);
    return i+1;
}
void quicksort(vector<int> &v,int l,int h) {
    if (l>=h) return; 
    int part =partition(v,l,h);
    quicksort(v,l,part-1);
    quicksort(v,part+1,h);
}
void matmul(vector<vector<int>> &v1,vector<vector<int>> &v3) {
    int a = v1[0][0], b = v1[0][1], c = v1[1][0], d = v1[1][1];
    int p = v3[0][0], q = v3[0][1], r = v3[1][0], l = v3[1][1];
    v1[0][0] = (a * p + b * r) % 1000000007;
    v1[0][1] = (a * q + b * l) % 1000000007;
    v1[1][0] = (c * p + d * r) % 1000000007;
    v1[1][1] = (c * q + d * l) % 1000000007;
}
vector<vector<int>> matpow(vector<vector<int>> m,int x) {
    vector<vector<int>> res = {{1,0},{0,1}}; 
    while(x>0){
        if(x%2==1)matmul(res,m);
        matmul(m,m);
        x/= 2;
    }
    return res;
}
class CurrencySorter {
public:
    void operator()(vector<int> &vec) {
        quicksort(vec,0,vec.size()-1);
    }
};
class FibonacciGenerator {
public:
    void operator()(int i) {
        if(i==0){
            cout<<0<<endl;
            return;
        }
        if(i==1){
            cout<<1<<endl;
            return;
        }
        vector<vector<int>> mat={{1,1},{1,0}};
        mat=matpow(mat,i-1);
        cout<<mat[0][0]<<endl;
    }
};
class PrimeCalculator {
private:
    int L;
public:
    PrimeCalculator(){

    }
    PrimeCalculator(int x){
        L=x;
    }
    void printprime(int R) {
        vector<bool> primes = largeprimes(L, R);
        for (int i=0;i<=R-L;i++){
            if(primes[i]){
                cout<<i+L<<" ";
            }
        }
        cout<<endl;
    }
    void printprimesum(int R) {
        int sum =0;
        vector<bool> primes =largeprimes(L,R);
        for(int i=0;i<=R-L;i++){
            if(primes[i]){
                sum+=i+L;
            }
        }
        cout<<sum<<endl;
    }
};
class NumberAnalyzer {
private:
    int n;
public:
    NumberAnalyzer(){
        n=0;
    }
    NumberAnalyzer(int x){
        n=x;
    }
    bool isSquareFree(){
        if (n==1)return true;
        int temp=n;
        for (int it=2;it*it<=n;it++) {
            if (prime10pow[it]) {
                int cnt=0;
                while(temp%it==0) {
                    cnt++;
                    temp/=it;
                    if(cnt>1)return false;
                }
            }
        }
        return true;
    }
    void countDivisors(){
        if(n==1){
            cout<<1<<endl;
            return;
        }
        int temp=n,c=1;
        for(int it=2;it*it<=n;it++){
            if(prime10pow[it]){
                int cnt=0;
                while(temp%it==0) {
                    cnt++;
                    temp/=it;
                }
                c*=(cnt+1);
            }
        }
        if(temp>1)c*= 2;
        cout<<c<<endl;
    }
    void sumOfDivisors(){
        if(n==1){  
            cout<<1<<endl;
            return;
        }
        int sum=1,temp=n;
        for (int it=2;it*it<=n&&it<=10000;it++){
            if(prime10pow[it]){
                int stemp=1,xi=it;
                while(temp%it==0){
                    stemp+=xi;
                    xi*=it;
                    temp/=it;
                }
                sum*=stemp;
            }
        }
        if(temp>1)sum*=(1+temp); 
        cout<<sum<<endl;
    }
};
int32_t main(){
    primesunder();
    int type;
    cin>>type;
    if(type==1){
        int t;
        cin>>t;
        while(t--){
            int n;
            cin>>n;
            vector<int> v(n);
            for(int i=0;i<n;i++){
                cin>>v[i];
            }
            CurrencySorter sorter; 
            sorter(v); 
            for(int i=0;i<n;i++){
                cout<<v[i]<<" ";
            }
            cout<<endl;
        }
    }
    else if(type==2){
        int t;
        cin>>t;
        while(t--){
            int i;
            cin>>i;
            FibonacciGenerator fibgen;
            fibgen(i);
        }
    }
    else if(type==3){
        int t;
        cin>>t;
        while(t--){
            string s;
            cin>>s;
            int l,r;
            cin>>l>>r;
            PrimeCalculator pc(l);
            if(s=="printPrimes"){
                pc.printprime(r);
            }
            else if(s=="printPrimeSum"){
                pc.printprimesum(r);
            }
        }
    }
    else if(type==4){
        int t;
        cin>>t;
        while(t--){
            string s;
            cin>>s;
            int x;
            cin>>x;
            NumberAnalyzer na(x);
            if(s=="isSquareFree"){
                if(na.isSquareFree()){
                    cout<<"yes"<<endl;
                }
                else{
                    cout<<"no"<<endl;
                }
            }
            else if(s=="countDivisors"){
                na.countDivisors();
            }
            else if(s=="sumOfDivisors"){
                na.sumOfDivisors();
            }
        }
    }
    return 0;
}
