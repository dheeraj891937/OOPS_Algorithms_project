#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define float long double
class custom_string
{
public:
   string str;
   custom_string()
   {
      str = "";
   }
   custom_string(string s)
   {
      str = s;
   }
   void setstring(string t)
   {
      str = t;
   }
   // Overload * operator to concatenate string multiple times
   custom_string operator*(int val)
   {
      string result = "";
      for (int i = 0; i < val; i++)
      {
         result += str;
      }
      return custom_string(result);
   }
   custom_string operator+(custom_string st)
   {
      return custom_string(str + st.str);
   }
};
template <typename T0> // template for complex class
class complex1
{ // class that defines complex numbers
public:
   T0 real, imag;
   complex1()
   {
      real = 0;
      imag = 0;
   }
   complex1(T0 a, T0 b)
   {
      real = a;
      imag = b;
   }
   complex1 operator*(complex1<T0> &tc)
   { //*operator overloaded to multiply 2 complex numbers of int or float type
      complex1<T0> res;
      res.real = (real * tc.real) - (imag * tc.imag);
      res.imag = (real * tc.imag) + (imag * tc.real);
      return res;
   }
   complex1 operator+(complex1<T0> tc)
   {
      complex1<T0> res;
      res.real = real + tc.real;
      res.imag = imag + tc.imag;
      return res;
   }
};
template <typename T>
class polynomial
{
public:
   vector<T> polyl;
   polynomial()
   {
   }
   polynomial(int sz)
   {
      polyl.resize(sz);
   }
   polynomial(vector<T> vec)
   {
      polyl = vec;
   }
   vector<T> karus_mul(polynomial<T> &p, int l1, int r1, int l2, int r2)
   {
      if (r1 - l1 <= 32 || r2 - l2 <= 32)
      {
         vector<T> res(r1 - l1 + r2 - l2 + 1, T{});
         for (int i = l1; i <= r1; i++)
         {
            for (int j = l2; j <= r2; j++)
            {
               res[i - l1 + j - l2] = res[i - l1 + j - l2] + (polyl[i] * p.polyl[j]);
            }
         }
         return res;
      }
      vector<T> mulres(r1 - l1 + r2 - l2 + 1, T{});
      int mid1 = l1 + (r1 - l1) / 2;
      int mid2 = l2 + (r2 - l2) / 2;
      if (mid1 <= l1 || mid2 <= l2)
         return {polyl[l1] * p.polyl[l2]};
      vector<T> v1 = karus_mul(p, l1, mid1 - 1, l2, mid2 - 1);
      vector<T> v2 = karus_mul(p, l1, mid1 - 1, mid2, r2);
      vector<T> v3 = karus_mul(p, mid1, r1, l2, mid2 - 1);
      vector<T> v4 = karus_mul(p, mid1, r1, mid2, r2);
      for (int i = 0; i < v1.size(); i++)
      {
         mulres[i] = mulres[i] + v1[i];
      }
      for (int i = 0; i < v2.size(); i++)
      {
         mulres[i + mid2 - l2] = mulres[i + mid2 - l2] + v2[i];
      }
      for (int i = 0; i < v3.size(); i++)
      {
         mulres[i + mid1 - l1] = mulres[i + mid1 - l1] + v3[i];
      }
      for (int i = 0; i < v4.size(); i++)
      {
         mulres[i + mid1 - l1 + mid2 - l2] = mulres[i + mid1 - l1 + mid2 - l2] + v4[i];
      }
      return mulres;
   }
   polynomial operator*(polynomial<T> &p)
   {                                                                               //*opeartor overloaded to multiply 2 polynomials of specified type
      return polynomial(karus_mul(p, 0, polyl.size() - 1, 0, p.polyl.size() - 1)); // multiplies polynomials of specified type                                                //uses divide and conquer approach , divide vectors into 2 halves and mutliply them recursively
   }
};
template <typename T1> // template for multiplication class
class multiplication
{
public:
   multiplication()
   {
   }
   polynomial<T1> multiply(polynomial<T1> &p1, polynomial<T1> &p2)
   {
      return p1 * p2;
   }
};
template <typename T2> // template differentiation class
class differentiation
{
public:
   polynomial<T2> differentiate(polynomial<T2> &p)
   { // differentiates the polynomial
      polynomial<T2> result;
      for (int i = 1; i < p.polyl.size(); i++)
      {
         result.polyl.push_back(i * p.polyl[i]);
      }
      return result;
   }
};
template <typename T3> // template for evaluation class
class evaluation
{
public:
   evaluation()
   {
   }
   T3 evaluate(polynomial<T3> &p, int &teval, T3 res)
   { // evaluates the polynomial at the given value
      int mul = pow(teval, p.polyl.size() - 1);
      for (int i = p.polyl.size() - 1; i >= 0; i--)
      {
         res = res + p.polyl[i] * mul;
         mul /= teval;
      }
      return res;
   }
};
int32_t main()
{
   int no_que;
   cin >> no_que; // no of queries
   while (no_que--)
   {
      int op_type; // operation type
      cin >> op_type;
      if (op_type == 1)
      { // multiplication
         string dattype;
         cin >> dattype;
         if (dattype == "integer")
         {
            int deg_p1;
            cin >> deg_p1;
            polynomial<int> pol1(deg_p1);
            for (int i = 0; i < deg_p1; i++)
            {
               cin >> pol1.polyl[i];
            }
            int deg_p2;
            cin >> deg_p2;
            polynomial<int> pol2(deg_p2);
            for (int i = 0; i < deg_p2; i++)
            {
               cin >> pol2.polyl[i];
            }
            multiplication<int> muleval;
            polynomial<int> product = muleval.multiply(pol1, pol2);
            for (int i = 0; i < product.polyl.size(); i++)
            {
               cout << product.polyl[i] << " ";
            }
            cout << endl;
         }
         else if (dattype == "float")
         {
            int deg_p1;
            cin >> deg_p1;
            polynomial<float> pol1(deg_p1);
            for (int i = 0; i < deg_p1; i++)
            {
               cin >> pol1.polyl[i];
            }
            int deg_p2;
            cin >> deg_p2;
            polynomial<float> pol2(deg_p2);
            for (int i = 0; i < deg_p2; i++)
            {
               cin >> pol2.polyl[i];
            }
            multiplication<float> muleval;
            polynomial<float> product = muleval.multiply(pol1, pol2);
            for (int i = 0; i < product.polyl.size(); i++)
            {
               cout << fixed << setprecision(6) << product.polyl[i];
               cout << " ";
            }
            cout << endl;
         }
         else if (dattype == "complex")
         {
            int deg_p1;
            cin >> deg_p1;
            polynomial<complex1<int>> pol1(deg_p1);
            for (int i = 0; i < deg_p1; i++)
            {
               cin >> pol1.polyl[i].real >> pol1.polyl[i].imag;
            }
            int deg_p2;
            cin >> deg_p2;
            polynomial<complex1<int>> pol2(deg_p2);
            for (int i = 0; i < deg_p2; i++)
            {
               cin >> pol2.polyl[i].real >> pol2.polyl[i].imag;
            }
            multiplication<complex1<int>> muleval;
            polynomial<complex1<int>> product = muleval.multiply(pol1, pol2);
            for (int i = 0; i < product.polyl.size(); i++)
            {
               cout << product.polyl[i].real << " " << product.polyl[i].imag << " ";
            }
            cout << endl;
         }
      }
      else if (op_type == 2)
      { // evaluation
         string dattype;
         cin >> dattype;
         int deg;
         cin >> deg;
         if (dattype == "integer")
         {
            polynomial<int> pol(deg);
            for (int i = 0; i < deg; i++)
            {
               cin >> pol.polyl[i];
            }
            int evalp;
            cin >> evalp;
            evaluation<int> evald;
            int res = evald.evaluate(pol, evalp, 0);
            cout << res << endl;
         }
         else if (dattype == "float")
         {
            polynomial<float> pol(deg);
            for (int i = 0; i < deg; i++)
            {
               cin >> pol.polyl[i];
            }
            int evalp;
            cin >> evalp;
            evaluation<float> evald;
            float res = evald.evaluate(pol, evalp, 0);
            cout << fixed << setprecision(6) << res;
            cout << endl;
         }
         else if (dattype == "string")
         {
            polynomial<custom_string> pol(deg);
            for (int i = 0; i < deg; i++)
            {
               string tem;
               cin >> tem;
               pol.polyl[i].setstring(tem);
            }
            int evalp;
            cin >> evalp;
            evaluation<custom_string> evald;
            custom_string res = evald.evaluate(pol, evalp, custom_string(""));
            cout << res.str << endl;
         }
      }
      else if (op_type == 3)
      { // differentiation
         string dattype;
         cin >> dattype;
         int deg;
         cin >> deg;
         if (dattype == "integer")
         {
            polynomial<int> pol(deg);
            for (int i = 0; i < deg; i++)
            {
               cin >> pol.polyl[i];
            }
            differentiation<int> difobj;
            polynomial<int> res = difobj.differentiate(pol);
            for (int i = 0; i < res.polyl.size(); i++)
            {
               cout << res.polyl[i] << " ";
            }
            cout << endl;
         }
         else if (dattype == "float")
         {
            polynomial<float> pol(deg);
            for (int i = 0; i < deg; i++)
            {
               cin >> pol.polyl[i];
            }
            differentiation<float> difobj;
            polynomial<float> res = difobj.differentiate(pol);
            for (int i = 0; i < res.polyl.size(); i++)
            {
               cout << fixed << setprecision(6) << res.polyl[i];
               cout << " ";
            }
            cout << endl;
         }
      }
   }
   return 0;
}

