#include <bits/stdc++.h>
using namespace std;
#define int long long int
map<vector<int>, int> um;
// Function to calculate Euclidean distance
long double dist_euclid(const vector<int> &points)
{
    return sqrt(((points[0] - points[2]) * (points[0] - points[2])) +
                ((points[1] - points[3]) * (points[1] - points[3])));
}
// Function to count inversions in a 1D array using a modified merge sort
int inv_count(vector<int> &temp, vector<int> &v, int l, int h)
{
    if (l >= h)
    {
        return 0;
    }
    int mid = (l + h) / 2;
    int countl = inv_count(temp, v, l, mid);
    int countr = inv_count(temp, v, mid + 1, h);
    int countcross = 0;
    int ileft = l;
    int iright = mid + 1;
    int itemp = l;
    while (ileft <= mid && iright <= h)
    {
        if (v[ileft] <= v[iright])
        {
            temp[itemp++] = v[ileft++];
        }
        else
        {
            countcross += mid - ileft + 1;
            temp[itemp++] = v[iright++];
        }
    }
    while (ileft <= mid)
    {
        temp[itemp++] = v[ileft++];
    }
    while (iright <= h)
    {
        temp[itemp++] = v[iright++];
    }
    for (int i = l; i <= h; i++)
    {
        v[i] = temp[i];
    }
    return countl + countr + countcross;
}
// Function to find the nearest pair of points in 2D space
vector<int> nearest2d(vector<vector<int>> &coord, int l, int h)
{
    if (l >= h)
    {
        return {};
    }
    if (l + 1 == h)
    {
        return {coord[l][0], coord[l][1], coord[h][0], coord[h][1]};
    }
    int mid = (l + h) / 2;
    vector<int> lnearest = nearest2d(coord, l, mid);
    vector<int> rnearest = nearest2d(coord, mid + 1, h);
    long double mind1 = INT_MAX;
    int p1x = 0, p1y = 0, p2x = 0, p2y = 0;
    if (!rnearest.empty())
    {
        long double distRight = dist_euclid({rnearest[0], rnearest[1], rnearest[2], rnearest[3]});
        if (distRight < mind1)
        {
            mind1 = distRight;
            p1x = rnearest[0];
            p1y = rnearest[1];
            p2x = rnearest[2];
            p2y = rnearest[3];
            if (um[{p1x, p1y}] > um[{p2x, p2y}])
            {
                p1x = rnearest[2];
                p1y = rnearest[3];
                p2x = rnearest[0];
                p2y = rnearest[1];
            }
        }
    }
    if (!lnearest.empty())
    {
        long double distLeft = dist_euclid({lnearest[0], lnearest[1], lnearest[2], lnearest[3]});
        if (distLeft <= mind1)
        {
            mind1 = distLeft;
            p1x = lnearest[0];
            p1y = lnearest[1];
            p2x = lnearest[2];
            p2y = lnearest[3];
            if (um[{p1x, p1y}] > um[{p2x, p2y}])
            {
                p1x = lnearest[2];
                p1y = lnearest[3];
                p2x = lnearest[0];
                p2y = lnearest[1];
            }
        }
    }
    vector<vector<int>> middle;
    for (int i = l; i <= h; i++)
    {
        if (abs(coord[i][0] - coord[mid][0]) <= mind1)
        {
            middle.push_back(coord[i]);
        }
    }
    sort(middle.begin(), middle.end(), [](const vector<int> &a, const vector<int> &b)
         { return a[1] < b[1]; });
    for (int i = 0; i < middle.size(); i++)
    {
        for (int j = i + 1; j < middle.size() && j < i + 16; j++)
        {
            long double dist = dist_euclid({middle[i][0], middle[i][1], middle[j][0], middle[j][1]});
            if (dist < mind1)
            {
                mind1 = dist;
                p1x = middle[i][0];
                p1y = middle[i][1];
                p2x = middle[j][0];
                p2y = middle[j][1];
                if (um[{p1x, p1y}] > um[{p2x, p2y}])
                {
                    p1x = middle[j][0];
                    p1y = middle[j][1];
                    p2x = middle[i][0];
                    p2y = middle[i][1];
                }
            }
            else if (dist == mind1)
            {
                int t1x = 0, t2x = 0, t1y = 0, t2y = 0;
                t1x = middle[i][0];
                t1y = middle[i][1];
                t2x = middle[j][0];
                t2y = middle[j][1];
                if (um[{p1x, p1y}] > um[{p2x, p2y}])
                {
                    t1x = middle[j][0];
                    t1y = middle[j][1];
                    t2x = middle[i][0];
                    t2y = middle[i][1];
                }
                if (p1x > t1x)
                {
                    p1x = t1x;
                    p1y = t1y;
                    p2x = t2x;
                    p2y = t2y;
                }
                else if (p1x == t1x)
                {
                    if (p1y > t1y)
                    {
                        p1x = t1x;
                        p1y = t1y;
                        p2x = t2x;
                        p2y = t2y;
                    }
                    else if (p1y == t1y)
                    {
                        if (p2x > t2x)
                        {
                            p1x = t1x;
                            p1y = t1y;
                            p2x = t2x;
                            p2y = t2y;
                        }
                        else if (p2x == t2x)
                        {
                            if (p2y > t2y)
                            {
                                p1x = t1x;
                                p1y = t1y;
                                p2x = t2x;
                                p2y = t2y;
                            }
                        }
                    }
                }
            }
        }
    }
    return {p1x, p1y, p2x, p2y};
}
// Class for managing a 2D chessboard
class chessboard
{
private:
    vector<vector<int>> quantum_state;

public:
    void CREATE_2D(int n)
    {
        quantum_state.resize(n, vector<int>(n));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> quantum_state[i][j];
            }
        }
    }
    void display()
    {
        for (const auto &row : quantum_state)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << endl;
        }
    }
    void countInversions()
    {
        int n = quantum_state.size();
        vector<int> flat;
        for (const auto &row : quantum_state)
        {
            flat.insert(flat.end(), row.begin(), row.end());
        }
        vector<int> temp(flat.size());
        cout << inv_count(temp, flat, 0, flat.size() - 1) << endl;
    }
    void SORT_2D(int order)
    {
        for (auto &row : quantum_state)
        {
            sort(row.begin(), row.end());
            if (order)
            {
                reverse(row.begin(), row.end());
            }
        }
    }
};
class players
{
private:
    vector<vector<int>> coords;

public:
    void closestpair(int n)
    {
        coords.resize(n, vector<int>(2));
        for (int i = 0; i < n; i++)
        {
            cin >> coords[i][0] >> coords[i][1];
        }
        for (int i = 0; i < n; i++)
        {
            um[coords[i]] = i;
        }
        sort(coords.begin(), coords.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[0] < b[0]; });
        vector<int> res = nearest2d(coords, 0, n - 1);
        if (!res.empty())
        {
            cout << res[0] << " " << res[1] << " " << res[2] << " " << res[3] << endl;
        }
    }
};
int32_t main()
{
    string ins;
    chessboard board;
    players participants;
    while (true)
    {
        cin >> ins;
        if (ins == "CREATE_2D")
        {
            int board_size;
            cin >> board_size;
            board.CREATE_2D(board_size);
        }
        else if (ins == "DISPLAY_2D")
        {
            board.display();
        }
        else if (ins == "INVERSION_2D")
        {
            board.countInversions();
        }
        else if (ins == "SORT_2D")
        {
            string ord;
            cin >> ord;
            board.SORT_2D(ord == "descending" ? 1 : 0);
        }
        else if (ins == "CLOSEST_2D")
        {
            int strength;
            cin >> strength;
            participants.closestpair(strength);
        }
        else if (ins == "END")
        {
            break;
        }
    }
    return 0;
}
