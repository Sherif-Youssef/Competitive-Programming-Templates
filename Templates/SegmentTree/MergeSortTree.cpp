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

template<class T, class F, class M>
struct MSTree
{
    ll n;
    F func;
    M mergeFunc;
    vector<vector<T>>> seg;
    vector<T> merge(vector<T> &a, vector<T> &b)
    {
        vector<T> res(a.size() + b.size());
        merhe(all(a), all(b), res.begin());
        return res;
    }
    MSTree(vector<T> data): n(data.size())
    {
        seg.resize(n * 4), build(data, 1, 0, n - 1);
    }
    void build(vector<ll> &data, ll v, ll l, ll r)
    {
        if (l == r)
            return seg[v].pb(data[l]);
        ll m = (l + r) / 2;
        build(data, v * 2, l, m);
        build(data, v * 2 + 1, m + 1, r);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
    ll get(ll v, ll l, ll r, ll tl, ll tr, ll k)
    {
        if (tl > tr)
            return 0;
        if (l == tl && r == tr)
            return func(seg[v], k);
        ll m = (l + r) / 2;
        return mergeFunc(
            get(v * 2, l, m, tl, min(tr, m), k),
            get(v * 2 + 1, m + 1, r, max(m + 1, tl), tr, k)
        );
    }
    ll get(ll l, ll r, ll k){ return get(1, 0, n - 1, l, r, k); }
};

struct FuncGT
{
    ll operator()(vll &v, ll k){ return v.end() - upper_bound(all(v), k); }
};

struct FuncLS
{
    ll operator()(vll &v, ll k){ return lower_bound(all(v), k) - v.begin(); }
};

struct MergeFunc
{
    ll operator()(ll a, ll b){ return a + b; }
};