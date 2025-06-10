#include <bits/stdc++.h>
using namespace std;
class gnode
{ // class for a node of the graph
public:
   int score; // contains hype score and its children
   int ftime;
   int stime;
   char col;
   int pre;
   int val;
   int sccno;
   int max_hypesum;
   gnode()
   {
      max_hypesum = 0;
      score = 0;
      ftime = 0;
      stime = 0;
      pre = -1;
      val = 0;
      sccno = 0;
      col = 'w';
   }
   gnode(int y, int ftim, int tt)
   {
      val = y;
      ftime = ftim;
   }
   gnode(int x)
   {
      val = x;
   }
   gnode(int x, int ind)
   {
      score = x;
      val = ind;
      max_hypesum = x;
   }
};
vector<gnode *> events;
void dfsvisit(vector<vector<gnode *>> &grf, int v, int &timec)
{
   timec++;
   events[v]->col = 'g';
   events[v]->stime = timec;
   for (int i = 0; i < grf[v].size(); i++)
   {
      int neighbor = grf[v][i]->val;
      if (events[neighbor]->col == 'w')
      {
         events[neighbor]->pre = v;
         dfsvisit(grf, neighbor, timec);
      }
   }
   timec++;
   events[v]->col = 'b';
   events[v]->ftime = timec;
}
void dfs(vector<vector<gnode *>> &grf)
{
   for (int i = 0; i < events.size(); i++)
   {
      events[i]->col = 'w';
      events[i]->pre = -1;
   }
   int tim = 0;
   for (int i = 0; i < events.size(); i++)
   {
      if (events[i]->col == 'w')
      {
         dfsvisit(grf, i, tim);
      }
   }
}
bool dfsvisit1(vector<vector<gnode *>> &grf, int v, int &timec)
{
   timec++;
   events[v]->col = 'g';
   events[v]->stime = timec;
   for (int i = 0; i < grf[v].size(); i++)
   {
      int neighbor = grf[v][i]->val;
      if (events[neighbor]->col == 'w')
      {
         events[neighbor]->pre = v;
         if (dfsvisit1(grf, neighbor, timec))
            return true;
      }
      else if (events[neighbor]->col == 'g')
      {
         return true;
      }
   }
   timec++;
   events[v]->col = 'b';
   events[v]->ftime = timec;
   return false;
}
bool dfs1(vector<vector<gnode *>> &grf)
{
   bool result = false;
   for (int i = 0; i < events.size(); i++)
   {
      events[i]->col = 'w';
      events[i]->pre = -1;
   }
   int tim = 0;
   for (int i = 0; i < events.size(); i++)
   {
      if (events[i]->col == 'w')
      {
         result = result or dfsvisit1(grf, i, tim);
      }
   }
   return result;
}
void dfsvisit3(vector<vector<gnode *>> &grf3, int ind, int &timec, vector<gnode *> &dupx, int &siz)
{
   timec++;
   dupx[ind]->col = 'g';
   dupx[ind]->stime = timec;
   for (int i = 0; i < grf3[ind].size(); i++)
   {
      int neighbor = grf3[ind][i]->val;
      if (dupx[neighbor]->col == 'w')
      {
         dupx[neighbor]->pre = ind;
         dfsvisit3(grf3, neighbor, timec, dupx, siz);
      }
   }
   timec++;
   siz++;
   dupx[ind]->ftime = timec;
   dupx[ind]->col = 'b';
}
int dfs3(vector<vector<gnode *>> &grf, vector<gnode *> &dup1, int &cnt)
{
   int mxscc = 0;
   for (int i = 0; i < events.size(); i++)
   {
      dup1[i]->col = 'w';
      dup1[i]->pre = -1;
   }
   int tim = 0;
   for (int i = 0; i < dup1.size(); i++)
   {
      int v = dup1[i]->val;
      if (dup1[v]->col == 'w')
      {
         int size = 0;
         // mxscc=0;
         dfsvisit3(grf, v, tim, dup1, size);
         cnt++;
         mxscc = max(mxscc, size);
      }
   }
   return mxscc;
}
class GraphAlgorithm
{ // parent class
public:
   vector<vector<gnode *>> graph;
   GraphAlgorithm()
   {
   }
   GraphAlgorithm(int sz)
   { // resizes the vector to total no of events
      graph.resize(sz);
   }
   void addedge(int x, int y)
   { // adds dependencies between two events
      graph[x].push_back(events[y]);
   }
   virtual void Query()
   {
   }
};
// child classes
class isCycle : public GraphAlgorithm
{
public:
   void Query()
   {
      if (dfs1(graph))
      {
         cout << "YES" << endl;
      }
      else
         cout << "NO" << endl;
   }
};
class indepComponent : public GraphAlgorithm
{
public:
   void Query()
   {
      int count = 0, max_scc = 0;
      dfs(graph);
      vector<gnode *> dup;
      for (gnode *e : events)
      {
         dup.push_back(new gnode(e->val, e->ftime, 0));
      }
      sort(dup.begin(), dup.end(), [](gnode *a, gnode *b)
           { return a->ftime > b->ftime; });
      vector<vector<gnode *>> dupgraph(graph.size());
      for (int i = 0; i < graph.size(); i++)
      {
         for (gnode *neighbor : graph[i])
         {
            dupgraph[neighbor->val].push_back(events[i]);
         }
      }
      max_scc = dfs3(dupgraph, dup, count);
      cout << count << " " << max_scc << endl;
   }
};
class validOrder : public GraphAlgorithm
{
public:
   void Query()
   {
      if (dfs1(graph))
      {
         cout << "NO" << endl;
         return;
      }
      priority_queue<int, vector<int>, greater<int>> minheap;
      vector<int> result;
      vector<int> indegree(graph.size(), 0);
      for (int i = 0; i < graph.size(); i++)
      {
         for (int j = 0; j < graph[i].size(); j++)
         {
            indegree[graph[i][j]->val]++;
         }
      }
      for (int i = 0; i < indegree.size(); i++)
      {
         if (indegree[i] == 0)
         {
            minheap.push(i);
         }
      }
      while (!minheap.empty())
      {
         int indx = minheap.top();
         minheap.pop();
         result.push_back(indx);
         for (int j = 0; j < graph[indx].size(); j++)
         {
            indegree[graph[indx][j]->val]--;
            if (indegree[graph[indx][j]->val] == 0)
            {
               minheap.push(graph[indx][j]->val);
            }
         }
      }
      for (int i = 0; i < result.size(); i++)
      {
         cout << result[i] + 1 << " ";
      }
      cout << endl;
   }
};
int rec(vector<vector<gnode *>> &grf, int ver, vector<gnode *> &vec, vector<bool> &vstd)
{
   if (ver < 0 || ver >= grf.size() || ver >= vec.size())
      return 0;
   if (vstd[ver])
      return vec[ver]->max_hypesum;
   int maxi = 0;
   int tscore = vec[ver]->score;
   vstd[ver] = true;
   for (int i = 0; i < grf[ver].size(); i++)
   {
      maxi = max(maxi, rec(grf, grf[ver][i]->val, vec, vstd));
   }
   return vec[ver]->max_hypesum = tscore + maxi;
}
class maxHype : public GraphAlgorithm
{
public:
   void dfs5(vector<vector<gnode *>> &g, vector<bool> &visited, stack<int> &st, int node)
   {
      visited[node] = true;
      for (gnode *neighbor : g[node])
      {
         if (!visited[neighbor->val])
         {
            dfs5(g, visited, st, neighbor->val);
         }
      }
      st.push(node);
   }
   void dfs4(vector<vector<gnode *>> &g, int node, int scc_no, vector<int> &scc_map)
   {
      scc_map[node] = scc_no;
      for (gnode *neighbor : g[node])
      {
         if (scc_map[neighbor->val] == -1)
         {
            dfs4(g, neighbor->val, scc_no, scc_map);
         }
      }
   }
   void Query()
   {
      int n = events.size();
      vector<bool> visited(n, false);
      stack<int> st;
      for (int i = 0; i < n; i++)
      {
         if (!visited[i])
         {
            dfs5(graph, visited, st, i);
         }
      }
      vector<vector<gnode *>> revGraph(n);
      for (int i = 0; i < n; i++)
      {
         for (gnode *neighbor : graph[i])
         {
            revGraph[neighbor->val].push_back(events[i]);
         }
      }
      vector<int> scc_map(n, -1);
      int scc_count = 0;
      while (!st.empty())
      {
         int node = st.top();
         st.pop();
         if (scc_map[node] == -1)
         {
            dfs4(revGraph, node, scc_count++, scc_map);
         }
      }
      vector<int> scc_hype(scc_count, 0);
      vector<vector<int>> scc_adj(scc_count);
      for (int i = 0; i < n; i++)
      {
         scc_hype[scc_map[i]] += events[i]->score;
      }
      for (int i = 0; i < n; i++)
      {
         for (gnode *neighbor : graph[i])
         {
            if (scc_map[i] != scc_map[neighbor->val])
            {
               scc_adj[scc_map[i]].push_back(scc_map[neighbor->val]);
            }
         }
      }
      vector<int> inDegree(scc_count, 0);
      vector<int> dp(scc_count, 0);
      queue<int> q;
      for (int u = 0; u < scc_count; u++)
      {
         for (int v : scc_adj[u])
         {
            inDegree[v]++;
         }
      }
      for (int i = 0; i < scc_count; i++)
      {
         if (inDegree[i] == 0)
         {
            q.push(i);
            dp[i] = scc_hype[i];
         }
      }
      int maxHype = 0;
      while (!q.empty())
      {
         int u = q.front();
         q.pop();
         maxHype = max(maxHype, dp[u]);
         for (int v : scc_adj[u])
         {
            dp[v] = max(dp[v], dp[u] + scc_hype[v]);
            if (--inDegree[v] == 0)
            {
               q.push(v);
            }
         }
      }
      cout << maxHype << endl;
   }
};
int main()
{
   int n, m;
   cin >> n >> m;
   for (int i = 0; i < n; i++)
   {
      int scr;
      cin >> scr;
      events.push_back(new gnode(scr, i));
   }
   GraphAlgorithm *event_schedule = new GraphAlgorithm(n);
   for (int i = 0; i < m; i++)
   {
      int x1, x2;
      cin >> x1 >> x2;
      event_schedule->addedge(x1 - 1, x2 - 1);
   }
   int no_queries;
   cin >> no_queries;
   while (no_queries--)
   {
      int type;
      cin >> type;
      GraphAlgorithm *queryInstance = nullptr;
      if (type == 1)
         queryInstance = new isCycle();
      else if (type == 2)
         queryInstance = new indepComponent();
      else if (type == 3)
         queryInstance = new validOrder();
      else if (type == 4)
         queryInstance = new maxHype();
      if (queryInstance)
      {
         queryInstance->graph = event_schedule->graph;
         queryInstance->Query();
      }
   }
   return 0;
}
