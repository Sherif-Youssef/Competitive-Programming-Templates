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

template<class T, class M, class I>
struct BIT
{
    vector<T> bit;
    ll n;
    M merge;
    I inverse;
    BIT(ll n): n(n), bit(n + 1, T()){}
    ll LSB(ll x){ return x & -x; }
    T get(ll r)
    {
        r++;
        T res = T();
        while (r > 0)
            res = merge(res, bit[r]), r -= LSB(r);
        return res;
    }
    T get(ll l, ll r){ return inverse(get(l - 1), get(r)); }
    void modify(ll pos, T val)
    {
        pos++;
        while (pos <= n)
            bit[pos] = merge(bit[pos], val), pos += LSB(pos);
    }
    void set(ll pos, T val){ modify(pos, inverse(get(pos, pos), val)); }
};

template<class T, class M, class I>
struct BIT2D
{
    vector<vector<T>> bit;
    ll n, m;
    M merge;
    I inverse;
    BIT2D(ll n, ll m): n(n), m(m), bit(n + 1, vector<T>(m + 1)){}
    ll LSB(ll x){ return x & -x; }
    T get(ll x, ll y)
    {
        x++, y++;
        T res = T();
        for (ll i{x}; i > 0; i -= LSB(i))
            for (ll j{y}; j > 0; j -= LSB(j))
                res = merge(res, bit[i][j]);
        return res;
    }
    T get(ll x1, ll y1, ll x2, ll y2)
    { 
        T res = get(x2, y2);
        res = inverse(get(x1 - 1, y2), res);
        res = inverse(get(x2, y1 - 1), res);
        res = merge(res, get(x1 - 1, y1 - 1));
        return res;
    }
    void modify(ll x, ll y, T val)
    {
        x++, y++;
        for (ll i{x}; i <= n; i += LSB(i))
            for (ll j{y}; j <= m; j += LSB(j))
                bit[i][j] = merge(bit[i][j], val);
    }
    void set(ll x, ll y, T val){ modify(x, y, inverse(get(x, y, x, y), val)); }
};
