#include <bits/stdc++.h>
using namespace std;
class node
{
private:
   string room_no;
   vector<pair<node *, int>> child;

public:
   node(){}
   node(string tsr)  {room_no=tsr;}
   string getroomno() { return room_no; }
   vector<pair<node *, int>> &getchildren() { return child; }
   void addchild(pair<node *, int> x) { child.push_back(x); }
};
unordered_map<string, node> rooms;
template <typename T>
class minpriorityqueue
{
private:
   vector<T> queue;
   vector<int> distances; // Stores current distances
   size_t cursize;
   void percolateup(int x)
   {
      if (cursize == 0)
         return;
      T xtemp = queue[x];
      int dtemp = distances[x];
      while (x > 1 && dtemp < distances[x / 2])
      {
         queue[x] = queue[x / 2];
         distances[x] = distances[x / 2];
         x = x / 2;
      }
      queue[x] = xtemp;
      distances[x] = dtemp;
   }
   void percolatedown(int x)
   {
      if (cursize == 0)
         return;
      T xtemp = queue[x];
      int dtemp = distances[x];
      while (2 * x <= cursize)
      {
         int cld1 = 2 * x, cld2 = 2 * x + 1;
         int mincld = cld1;
         if (cld2 <= cursize && distances[cld2] < distances[cld1])
         {
            mincld = cld2;
         }
         if (dtemp <= distances[mincld])
         {
            break;
         }
         queue[x] = queue[mincld];
         distances[x] = distances[mincld];
         x = mincld;
      }
      queue[x] = xtemp;
      distances[x] = dtemp;
   }

public:
   minpriorityqueue()  {
      queue.resize(1);
      distances.resize(1);
      cursize=0;
   }
   size_t size() const { return cursize; }
   void push(const T &x, int dist)
   {
      queue.push_back(x);
      distances.push_back(dist);
      cursize++;
      percolateup(cursize);
   }
   void pop()
   {
      if (cursize == 0)
         return;
      queue[1] = queue[cursize];
      distances[1] = distances[cursize];
      queue.pop_back();
      distances.pop_back();
      cursize--;
      percolatedown(1);
   }
   const T &top() const { return queue[1]; }
   int top_dist() const { return distances[1]; }
   bool empty() const { return cursize == 0; }
};
int dijkstra(node &sver, node &dver)
{
   minpriorityqueue<node *> mpq;
   unordered_map<string, int> odd, even;
   unordered_map<string, bool> evenvisit, oddvisit;
   // Initialize distances
   for (auto &it : rooms)
   {
      odd[it.first] = even[it.first] = INT_MAX;
   }
   // Start with even distance 0
   even[sver.getroomno()] = 0;
   mpq.push(&sver, 0);
   while (!mpq.empty())
   {
      node *current = mpq.top();
      int current_dist = mpq.top_dist();
      string name = current->getroomno();
      mpq.pop();
      // Determine parity
      bool is_odd;
      if (current_dist == even[name] && current_dist != odd[name])
      {
         is_odd = false;
      }
      else if (current_dist == odd[name] && current_dist != even[name])
      {
         is_odd = true;
      }
      else
      {
         // Ambiguous case - skip
         continue;
      }
      // Skip if already processed with this parity
      if ((is_odd && oddvisit[name]) || (!is_odd && evenvisit[name]))
      {
         continue;
      }
      // Mark as processed
      if (is_odd)
         oddvisit[name] = true;
      else
         evenvisit[name] = true;
      for (auto &[neighbor, weight] : current->getchildren())
      {
         string neighbor_name = neighbor->getroomno();
         if (!is_odd)
         {
            if (even[name] + weight < odd[neighbor_name])
            {
               odd[neighbor_name] = even[name] + weight;
               mpq.push(neighbor, odd[neighbor_name]);
            }
         }
         else
         {
            if (odd[name] + weight < even[neighbor_name])
            {
               even[neighbor_name] = odd[name] + weight;
               mpq.push(neighbor, even[neighbor_name]);
            }
         }
      }
   }
   return even[dver.getroomno()] == INT_MAX ? -1 : even[dver.getroomno()];
}
int main()
{
   int n, m;
   cin >> n >> m;
   for (int i = 0; i < n; i++)
   {
      string input;
      cin >> input;
      rooms[input] = node(input);
   }
   for (int i = 0; i < m; i++)
   {
      string n1, n2;
      int wt;
      cin >> n1 >> n2 >> wt;
      rooms[n1].addchild({&rooms[n2], wt});
      rooms[n2].addchild({&rooms[n1], wt});
   }
   string start_vertex, dest_vertex;
   cin >> start_vertex >> dest_vertex;
   cout << dijkstra(rooms[start_vertex], rooms[dest_vertex]) << endl;
   return 0;
}