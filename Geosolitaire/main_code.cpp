#include <bits/stdc++.h>
using namespace std;
#define int long long int
class Card
{
public:
   vector<int> dimen; // stores the dimensions of the shape
   bool operator<=(Card *crd)
   {
      return this->getarea() <= crd->getarea();
   }
   virtual void input(istream &in) = 0;
   virtual void output(ostream &out) = 0;
   virtual int getarea() = 0; // gives area of the shape
   friend istream &operator>>(istream &in, Card &crd)
   {
      crd.input(in);
      return in;
   }
   friend ostream &operator<<(ostream &ot, Card &crd)
   {
      crd.output(ot);
      return ot;
   }
};
class square : public Card
{
public:
   int getarea() override
   {
      return dimen[0] * dimen[0];
   }
   void input(istream &in) override
   {
      dimen.resize(1);
      in >> dimen[0];
   }
   void output(ostream &out) override
   {
      out << "SQUARE" << " " << dimen[0] << "\n";
   }
};
class rectangle : public Card
{
public:
   int getarea() override
   {
      return dimen[0] * dimen[1];
   }
   void input(istream &in) override
   {
      dimen.resize(2);
      in >> dimen[0] >> dimen[1];
   }
   void output(ostream &ot) override
   {
      ot << "RECTANGLE" << " " << dimen[0] << " " << dimen[1] << "\n";
   }
};
class triangle : public Card
{
public:
   int getarea() override
   {
      return dimen[0] * dimen[1] / 2;
   }
   void input(istream &in) override
   {
      dimen.resize(2);
      in >> dimen[0] >> dimen[1];
   }
   void output(ostream &ot) override
   {
      ot << "TRIANGLE" << " " << dimen[0] << " " << dimen[1] << "\n";
   }
};
vector<Card *> setofcards; // contains the cards that are given
vector<int> indss;
vector<int> prevs;
class CardOrganizer
{
public:
   vector<int> tops;
   int crdcnt;
   CardOrganizer()
   {
      crdcnt = 0;
   }
   void addCard(Card *crd)
   { // Finds a suitable pile and inserts the card in it.
      if (tops.size() == 0)
      {
         prevs.resize(1);
         prevs[0] = -1;
         tops.push_back(crd->getarea());
         indss.push_back(crdcnt);
         crdcnt++;
         return;
      }
      int l = 0;
      int h = tops.size() - 1;
      while (l <= h)
      {
         int mid = l + (h - l) / 2;
         if (crd->getarea() <= tops[mid])
         {
            h = mid - 1;
         }
         else if (crd->getarea() > tops[mid])
         {
            l = mid + 1;
         }
      }
      if (l == tops.size())
      {
         tops.push_back(crd->getarea());
         indss.push_back(crdcnt);
      }
      else
      {
         tops[l] = crd->getarea();
         indss[l] = crdcnt;
      }
      if (l == 0)
      {
         prevs.push_back(-1);
      }
      else
      {
         prevs.push_back(indss[l - 1]);
      }
      crdcnt++;
   }
   size_t getPileCount() const   // Returns the number of piles created so far.
   { 
      return tops.size();
   }
   vector<Card *> getLIS() const
   {
      vector<Card *> res;
      for (int i = indss[indss.size() - 1]; i >= 0; i = prevs[i])
      {
         res.push_back(setofcards[i]);
      }
      return res;
   }
};
int32_t main()
{
   int no_que; // no of queries
   cin >> no_que;
   CardOrganizer gameorg;
   while (no_que--)
   {
      int type;
      cin >> type;
      if (type == 1)
      {
         string shape;
         cin >> shape;
         Card *inpcard = nullptr;
         if (shape == "SQUARE")
         {
            inpcard = new square();
         }
         else if (shape == "RECTANGLE")
         {
            inpcard = new rectangle();
         }
         else if (shape == "TRIANGLE")
         {
            inpcard = new triangle();
         }
         if (inpcard)
         {
            cin >> *inpcard;
            setofcards.push_back(inpcard);
            gameorg.addCard(inpcard);
         }
      }
      else if (type == 2)
      {
         cout << gameorg.getPileCount() << "\n";
      }
      else if (type == 3)
      {
         vector<Card *> vec = gameorg.getLIS();
         cout << vec.size() << "\n";
         for (int i = vec.size() - 1; i >= 0; i--)
         {
            cout << *vec[i];
         }
         cout << "\n";
      }
   }
   return 0;
}