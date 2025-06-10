#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
class Book{
    private:
      string isbn;
      int copiesAvailable;
      int totalCopies ;
    public:
      string title;
      string author;
      Book(){
        isbn="ISBN";
        copiesAvailable=0;
        totalCopies=5;
        title="UnknownTitle";
        author="UnknownAuthor";
      }
      Book(string tit,string ath,string isb,int x,int y){
         title=tit;
         author=ath;
         isbn=isb;
         copiesAvailable=x;
         totalCopies=y;
      }
      Book(Book &b,string isb){
        title=b.title;
        author=b.author;
        isbn=isb;
        copiesAvailable=b.get_nocop();
        totalCopies=b.get_totcop();

      }
      string getisbn(){
        return isbn;
      }
      int get_nocop(){
        return copiesAvailable;
      }
      int get_totcop(){
        return totalCopies;
      }
      void updateborrow(int x){
        if(copiesAvailable+x>=0)
            copiesAvailable+=x;
      }
      void updateCopies(int count){
        if(copiesAvailable+count>=0&&totalCopies+count>=0){
            copiesAvailable+=count;
            totalCopies+=count;
        }
        else cout<<"Invalid request! Count becomes negative"<<endl;
      }
      bool borrowBook(){
        if(copiesAvailable-1>=0){
            copiesAvailable--;
            return true;
      }
        cout<<"Invalid request! Copy of book not available"<<endl;
        return false;
      }
      bool returnBook(){
        if(copiesAvailable+1<=totalCopies){
            copiesAvailable++;
            return true;
        }
            cout<<"Invalid request! Copy of book exceeds total copies"<<endl;
            return false;
      }
      void printDetails(){
        cout<<title<<" "<<author<<endl;
      }
      bool operator < (const Book& b) const {
         return isbn < b.isbn;
     }

};
class Member{
    private:
      string memberID;
      map<string,int> borrowedBooks;
      int borrowLimit;
      int nboo;
    public:
      string name;
    Member(){
        borrowLimit=3;
        nboo=0;
    }
    Member(string mid,string nam,map<string,int> bbo){
        memberID=mid;
        borrowedBooks=bbo;
        name=nam;
        borrowLimit=3;
        nboo=0;
    }
    Member(string mid,string nam,map<string,int> bbo,int bl){
        memberID=mid;
        borrowedBooks=bbo;
        name=nam;
        borrowLimit=bl;
        nboo=0;
    }
    map<string,int> bbooks(){
      return borrowedBooks;
    }
    string getmid(){
      return memberID;
    }
    bool lmt(){
      if(nboo>borrowLimit){
         return true;
      }
      return false;
    }
    bool borrowBook(string isbn){
        if(nboo<borrowLimit){
            nboo++;
            borrowedBooks[isbn]++;
            return true;
        }
        cout<<"Invalid request! Borrow limit exceeded"<<endl;
        return  false;
    }
    int getnboo(){
      return nboo;
    }
    bool returnBook(string isbn){
        if(borrowedBooks.find(isbn)!=borrowedBooks.end()&&borrowedBooks[isbn]>0){
            nboo--;
            borrowedBooks[isbn]--;
            if(borrowedBooks[isbn]==0){
                borrowedBooks.erase(isbn);
            }
            return true;
        }
        cout<<"Invalid request! Book not borrowed"<<endl;
        return false;
    }
    void printDetails(){
        if(nboo){
            for(auto it=borrowedBooks.begin();it!=borrowedBooks.end();it++){
                cout<<memberID<<" "<<name<<" "<<it->first<<" "<<it->second<<endl;
            }
        }
    }
};
class Library{
    private:
      vector<Book*> books;
      vector<Member*> members;
    public:
      bool addBook(Book* bx){
        int f=1;
        for(int i=0;i<books.size();i++){
            if(bx->getisbn()==books[i]->getisbn()){
                f=0;
            }
        }
        if(f==1){
            books.push_back(bx);
            return true;
        }
        cout<<"Invalid request! Book with same isbn already exists"<<endl;
        return false;
      }
      bool registerMember(Member* m){
        int f=1;
        for(int i=0;i<members.size();i++){
            if(m->getmid()==members[i]->getmid()){
                f=0;
         }
        }
        if(f==1){
            members.push_back(m);
            return true;
        }
        cout<<"Invalid request! Member with same id already exists"<<endl;
        return false;
      }
      bool borrowBook(string memberID, string isbn){
         int f=1;
         int t=-1;
          for(int i=0;i<members.size();i++){
            if(members[i]->getmid()==memberID){
               if(members[i]->lmt()){
                  return false;
               }  
            }
         }
         for(int i=0;i<books.size();i++){
            if(isbn==books[i]->getisbn()){
               if(books[i]->get_nocop()==0){
                   cout<<"Invalid request! Copy of book not available"<<endl;
                   return false;
               }
               t=i;
               f=0;
            }
        }
        if(f==1){
            cout<<"Invalid request! Copy of book not available"<<endl;
            return false;
        }
            bool fl=false;
            for(int i=0;i<members.size();i++){
                if(members[i]->getmid()==memberID){
                  fl= members[i]->borrowBook(isbn);
                }
             }
             if(fl){
                   books[t]->updateborrow(-1);
                   return true;
             }
             return false;
        }
      bool returnBook(string memberID, string isbn){
         bool fl=false,f=false;
         int t=-1;
         for(int i=0;i<books.size();i++){
            if(isbn==books[i]->getisbn()){
               t=i;
               fl=books[i]->returnBook();
            }
         }
         if(fl){
            for(int i=0;i<members.size();i++){
               if(memberID==members[i]->getmid()){
                   f=members[i]->returnBook(isbn);
                   if(f) return true;
                   books[t]->updateborrow(-1);
                   return false;
               }
            }
         }
         return false;
      }
      void printLibraryDetails(){
         for(int i=0;i<books.size();i++){
            cout<<books[i]->title<<" "<<books[i]->author<<" "<<books[i]->get_nocop()<<endl;
         }
         for(int i=0;i<members.size();i++){
            cout<<members[i]->getmid()<<" "<<members[i]->name<<endl;
         }
      }
};
int main(){
   string s="";
   map<Book*,int> book;
   vector<Member*> member;
   Library* l=new Library();
   while(1){
      cin>>s;
      if(s=="Done")break;
      else if(s=="Book"){
         string s1;
         cin>>s1;
         if(s1=="None"){
            Book* b=new Book();
            book[b]++;
            l->addBook(b);
         }
        else if(s1=="ExistingBook"){
            string s4,s3;
            cin>>s3>>s4;
            for(auto it : book){
               Book *xy=it.first;
               if(s3==xy->getisbn()){
                  Book* b=new Book(*xy,s4);
                  book[b]++;
                  l->addBook(b);
               }
            }
         }
         else{
            string s3,s4;
            int x,y;
            cin>>s3>>s4>>x>>y;
            Book* b=new Book(s1,s3,s4,x,y);
            book[b]++;
            l->addBook(b);
         }
      }
     else if(s=="UpdateCopiesCount"){
         string s1;
         int x;
         cin>>s1>>x;
         for(auto it:book){
            Book* xz=it.first;
            if(xz->getisbn()==s1){
                xz->updateCopies(x);
            }
         }
      }
     else if(s=="Member"){
         string s1;
         cin>>s1;
         if(s1=="NoBorrowLimit"){
            string s3,s4;
            cin>>s3>>s4;
            map<string,int> mp;
            Member* m1=new Member(s3,s4,mp);
            member.push_back(m1);
            l->registerMember(m1);
         }
         else{
            string s3;
            int x;
            cin>>s3>>x;
            map<string,int> mp;
            Member* m1=new Member(s1,s3,mp,x);
            member.push_back(m1);
            l->registerMember(m1);
         }
      }
      else if(s=="Borrow"){
         string s3,s4;
         cin>>s3>>s4;
         l->borrowBook(s3,s4);
      }
     else if(s=="Return"){
         string s3,s4;
         cin>>s3>>s4;
         l->returnBook(s3,s4);
      }
      else if(s=="PrintBook"){
         string s1;
         cin>>s1;
         for(auto it:book){
            Book* xy=it.first;
            if(xy->getisbn()==s1){
               cout<<xy->title<<" "<<xy->author<<endl;
            }
         }
      }
     else if(s=="PrintMember"){
         string s1;
         cin>>s1;
         for(int i=0;i<member.size();i++){
            if(member[i]->getmid()==s1){
               map<string,int> m1=member[i]->bbooks();
               for(auto it:m1){
                  cout<<s1<<" "<<member[i]->name<<" "<<it.first<<" "<<it.second<<endl;
               }
            }
         }
      }
      else if(s=="PrintLibrary"){
         l->printLibraryDetails();
      }
   }
   return 0;
}
