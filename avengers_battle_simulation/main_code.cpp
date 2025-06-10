#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
class QNS;
queue<QNS> avail;
class QNS
{
private:
  int powerlevel, durability, energystorage, heatlevel;

public:
  QNS()
  {
    powerlevel = 1000;
    durability = 500;
    energystorage = 300;
    heatlevel = 0;
  }
  QNS(int a, int b, int c, int d)
  {
    powerlevel = a;
    if(powerlevel>5000)powerlevel=5000;
    durability = b;
    energystorage = c;
    heatlevel = d;
  }
  QNS(const QNS &q)
  {
    powerlevel = q.getp();
    durability = q.getd();
    energystorage = q.gete();
    heatlevel = q.geth();
  }
  int getp() const
  {
    return powerlevel;
  }
  int getd() const
  {
    return durability;
  }
  int gete() const
  {
    return energystorage;
  }
  int geth() const
  {
    return heatlevel;
  }
  void setp(int x)
  {
    powerlevel = x;
  }
  void setd(int x)
  {
    durability = x;
  }
  void sete(int x)
  {
    energystorage = x;
  }
  void seth(int x)
  {
    heatlevel = x;
  }
  QNS &operator+(QNS &q)
  {
    powerlevel += q.gete();
    if(powerlevel>5000)powerlevel=5000;
    durability += q.getd();
    energystorage += q.getp();
    return *this;
  }
  QNS &operator-(int x)
  {
    durability -= x;
    energystorage += x;
    heatlevel += x;
    return *this;
  }
  QNS &operator*(int x)
  {
    heatlevel += x;
    energystorage += 5 * x;
    powerlevel += (powerlevel * (x)) / 100;
    if(powerlevel>5000)powerlevel=5000;
    return *this;
  }
  QNS &operator/(int x)
  {
    durability += x;
    heatlevel -= x;
    if (heatlevel < 0)
    {
      heatlevel = 0;
    }
    return *this;
  }
  void boostPower(int factor)
  {
    *this = (*this) * factor;
  }
  void boostPower(QNS &otherSuit)
  {
    *this = (*this) + otherSuit;
  }
  bool operator==(const QNS &q) const
  {
    if (powerlevel == q.getp() && durability == q.getd())
    {
      return true;
    }
    return false;
  }
  bool operator<(const QNS &q) const
  {
    if (powerlevel + durability < q.getp() + q.getd())
    {
      return true;
    }
    return false;
  }
};
class avenger
{
private:
  string name;
  QNS suit;
  int att_str;

public:
  avenger()
  {
    att_str = 0;
    name = "";
  }
  avenger(string nam, QNS q, int x)
  {
    name = nam;
    suit = q;
    att_str = x;
  }
  void setsuit(QNS &q)
  {
    suit = q;
  }
  string getn()
  {
    return name;
  }
  QNS &getsuit()
  {
    return suit;
  }
  void attack(avenger *enemy)
  {
    QNS q = enemy->getsuit() - att_str;
    enemy->setsuit(q);
  }
  void bpf(int x)
  {
    suit.boostPower(x);
  }
  void bp(QNS &q)
  {
    suit.boostPower(q);
  }
  bool upgradeSuit()
  {
    if (!avail.empty())
    {
      suit = suit + avail.front();
      avail.pop();
      return true;
    }
    return false;
  }
  void repair(int x)
  {
    suit = suit / x;
  }
  void printstatus()
  {
    cout << name << " " << suit.getp() << " " << suit.getd() << " " << suit.gete() << " " << suit.geth() << endl;
  }
};
class battle
{
private:
  vector<avenger> heroes;
  vector<avenger> enemies;
  vector<string> log;

public:
  void heradd(avenger a)
  {
    heroes.push_back(a);
  }
  void enadd(avenger a)
  {
    enemies.push_back(a);
  }
  void ladd(string s)
  {
    log.push_back(s);
  }
  avenger *retav(string nam)
  {
    for (int i = 0; i < heroes.size(); i++)
    {
      if (heroes[i].getn() == nam)
      {
        return &heroes[i];
      }
    }
    for (int i = 0; i < enemies.size(); i++)
    {
      if (enemies[i].getn() == nam)
      {
        return &enemies[i];
      }
    }
    return &heroes[0];
  }
  void startBattle()
  {
    string s;
    while (1)
    {
      cin >> s;
      if (s == "Attack")
      {
        string s1, s3;
        cin >> s1 >> s3;
        avenger *ap = retav(s1), *aq = retav(s3);
        if (ap->getsuit().getd() > 0 && ap->getsuit().geth() <= 500 && aq->getsuit().getd() > 0)
        {
          ap->attack(aq);
          string sin = s1 + " attacks " + s3;
          ladd(sin);
          if (aq->getsuit().getd() <= 0)
          {

            string sin1 = s3 + " suit destroyed";
            ladd(sin1);
          }
          else if (aq->getsuit().geth() > 500)
          {
            string sin1 = s3 + " suit overheated";
            ladd(sin1);
          }
        }
      }
      else if (s == "Repair")
      {
        string s1;
        int x;
        cin >> s1 >> x;
        retav(s1)->repair(x);
        string sin = s1 + " repaired";
        ladd(sin);
      }
      else if (s == "BoostPowerByFactor")
      {
        string s1;
        int x;
        cin >> s1 >> x;
        retav(s1)->bpf(x);
        string sin = s1 + " boosted";
        ladd(sin);
        if (retav(s1)->getsuit().geth() > 500)
        {
          string sin1 = s1 + " suit overheated";
          ladd(sin1);
        }
      }
      else if (s == "BoostPower")
      {
        string s1;
        int x, y, z, m;
        cin >> s1 >> x >> y >> z >> m;
        QNS q1(x, y, z, m);
        retav(s1)->bp(q1);
        string sin = s1 + " boosted";
        ladd(sin);
        if (retav(s1)->getsuit().geth() > 500)
        {
          string sin1 = s1 + " suit overheated";
          ladd(sin1);
        }
      }
      else if (s == "AvengerStatus")
      {
        string s1;
        cin >> s1;
        retav(s1)->printstatus();
      }
      else if (s == "Upgrade")
      {
        string s1;
        cin >> s1;
        bool f = retav(s1)->upgradeSuit();
        if (f)
        {
          string sin = s1 + " upgraded";
          ladd(sin);
        }
        else
        {
          string sin1 = s1 + " upgrade Fail";
          ladd(sin1);
        }
      }
      else if (s == "PrintBattleLog")
      {
        printBattleLog();
      }
      else if (s == "BattleStatus")
      {
        int xx = Result();
        if (xx == 1)
        {
          cout << "heroes are winning" << endl;
        }
        else if (xx == -1)
        {
          cout << "enemies are winning" << endl;
        }
        else
        {
          cout << "tie" << endl;
        }
      }
      else if (s == "End")
      {
        break;
      }
    }
  }
  void printBattleLog()
  {
    for (int i = 0; i < log.size(); i++)
    {
      cout << log[i] << endl;
    }
  }
  int Result()
  {
    int suh = 0, sue = 0;
    for (int i = 0; i < heroes.size(); i++)
    {
      if(heroes[i].getsuit().getd()> 0)
      suh += heroes[i].getsuit().getp() + heroes[i].getsuit().getd();
    }
    for (int i = 0; i < enemies.size(); i++)
    {
      if(enemies[i].getsuit().getd()> 0)
      sue += enemies[i].getsuit().getp() + enemies[i].getsuit().getd();
    }
    if (suh > sue)
    {
      return 1;
    }
    if (suh < sue)
    {
      return -1;
    }
    return 0;
  }
};
int main()
{
  int k, n, m;
  cin >> k >> n >> m;
  battle game;
  for (int i = 0; i < k; i++)
  {
    int pp, pq, pr, pl;
    cin >> pp >> pq >> pr >> pl;
    QNS qp(pp, pq, pr, pl);
    avail.push(qp);
  }
  for (int i = 0; i < n; i++)
  {
    string aname;
    int astr;
    cin >> aname >> astr;
    if (!avail.empty())
    {
      avenger a1(aname, avail.front(), astr);
      avail.pop();
      game.heradd(a1);
    }
    else
    {
      cout << aname << " is out of fight" << endl;
    }
  }
  for (int i = 0; i < m; i++)
  {
    string aname;
    int astr;
    cin >> aname >> astr;
    if (!avail.empty())
    {
      avenger a1(aname, avail.front(), astr);
      avail.pop();
      game.enadd(a1);
    }
    else
    {
      cout << aname << " is out of fight" << endl;
    }
  }
  string s;
  cin >> s;
  if(s=="BattleBegin"){
    game.startBattle();
  }
  return 0;
}
