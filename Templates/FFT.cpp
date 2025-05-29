#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<vvpll> vvvpll;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<vvs> vvvs;
typedef set<ll> sll;
typedef set<sll> ssll;
typedef set<pll> spll;
typedef set<spll> sspll;
typedef set<string> ss;
typedef set<ss> sss;
typedef map<ll, ll> mll;

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18, PI = acos(-1);

struct FFT
{
    typedef complex<double> cd;
 
    static void fft(vector<cd> &a, bool invert) 
    {
        int n = a.size();
 
        for (int i = 1, j = 0; i < n; i++) 
        {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1)
                j ^= bit;
            j ^= bit;
 
            if (i < j)
                swap(a[i], a[j]);
        }
        for (int len = 2; len <= n; len <<= 1) 
        {
            double ang = 2 * PI / len * (invert ? -1 : 1);
            cd wlen(cos(ang), sin(ang));
            for (int i = 0; i < n; i += len) 
            {
                cd w(1);
                for (int j = 0; j < len / 2; j++) 
                {
                    cd u = a[i + j], v = a[i + j + len / 2] * w;
                    a[i + j] = u + v;
                    a[i + j + len / 2] = u - v;
                    w *= wlen;
                }
            }
        }
 
        if (invert) 
        {
            for (auto &x: a)
                x /= n;
        }
    }
    static vll multiply(vll &a, vll &b) {
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int n = 1;
        while (n < a.size() + b.size()) 
            n <<= 1;
        fa.resize(n);
        fb.resize(n);
    
        fft(fa, false);
        fft(fb, false);
        for (int i = 0; i < n; i++)
            fa[i] *= fb[i];
        fft(fa, true);
    
        vll result(n);
        for (int i = 0; i < n; i++)
            result[i] = round(fa[i].real());
        return result;
    }
    static vll unit(ll n)
    {
        vll v(n);
        v[0] = 1;
        return v;
    }
    static vll fastPow(vll &v, ll p)
    {
        if (p == 0)
            return unit(v.size());
        vll res = fastPow(v, p / 2);
        res = multiply(res, res);
        if (p & 1)
            res = multiply(res, v);
        for (auto &e: res)
            e = min(e, 1ll);
        return res;
    }
};