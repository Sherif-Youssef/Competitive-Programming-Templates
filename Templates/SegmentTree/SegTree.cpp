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

template<class T, class F>
struct SegTree
{
    vector<T> seg;
    ll n;
    F merge;
    SegTree(vector<T> data): n(data.size())
    {
        seg.assign(n * 4, T());
        build(data, 1, 0, n - 1);
    }
    void build(vector<T> &data, ll v, ll l, ll r)
    {
        if (l == r)
            return void(seg[v] = data[l]);
        ll m = (l + r) / 2;
        build(data, v * 2, l, m);
        build(data, v * 2 + 1, m + 1, r);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
    void set(ll v, ll l, ll r, ll pos, T val)
    {
        if (l == r && l == pos)
            return void(seg[v] = val);
        ll m = (l + r) / 2;
        if (pos <= m)
            set(v * 2, l, m, pos, val);
        else
            set(v * 2 + 1, m + 1, r, pos, val);
        seg[v] = merge(seg[v * 2], seg[v * 2 + 1]);
    }
    T get(ll v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        if (l == tl && r == tr)
            return seg[v];
        ll m = (l + r) / 2;
        return merge(
            get(v * 2, l, m, tl, min(tr, m)),
            get(v * 2 + 1, m + 1, r, max(m + 1, tl), tr)
        );
    }
    // op: sum
    ll getKth(ll v, ll l, ll r, ll k)
    {
        if (l == r)
            return (k == 1 ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= k)
            return getKth(v * 2, l, m, k);
        return getKth(v * 2 + 1, m + 1, r, k - seg[v * 2]);  
    }
    // op : max
    ll getLB(ll v, ll l, ll r, ll tl, ll tr, T val)
    {
        if (tl > tr)
            return -1;
        if (l == r)
            return (seg[v] >= val ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= val)
        {
            ll res = getLB(v * 2, l, m, tl, min(tr, m), val);
            if (~res)
                return res;
        }
        return getLB(v * 2 + 1, m + 1, r, max(tl, m + 1), tr, val);
    }
    // op: sum
    ll getMEX(ll v, ll l, ll r)
    {
        if (l == r)
            return (seg[v] == 0 ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] < m - l + 1)
            return getMEX(v * 2, l, m);
        return getMEX(v * 2 + 1, m + 1, r);  
    }
    void set(ll pos, T val){ set(1, 0, n - 1, pos, val); }
    T get(ll l, ll r){ return get(1, 0, n - 1, l, r); }
    ll getKth(ll k){ return getKth(1, 0, n - 1, k); }
    T getLB(ll l, ll r, T val){ return getLB(1, 0, n - 1, l, r, val); }
    ll getMEX(){ return getMEX(1, 0, n - 1); }
};


// max sum of any segment
struct Seg
{
    ll maxPre, maxSuf, maxSum, total;
    Seg(ll val = 0): Seg(val, val, val, val){}
    Seg(ll maxPre, ll maxSuf, ll maxSum, ll total)
    : maxPre(maxPre), maxSuf(maxSuf), maxSum(maxSum), total(total){}
};

struct Merge
{
    Seg operator()(Seg a, Seg b)
    {
        return Seg(
            max(a.maxPre, a.total + b.maxPre),
            max(b.maxSuf, b.total + a.maxSuf),
            max({a.maxSum, b.maxSum, a.maxSuf + b.maxPre}),
            a.total + b.total
        );
    }
};