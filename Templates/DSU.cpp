#include <bits/stdc++.h>
#define each auto &
#define endl '\n'
#define all(v) v.begin(), v.end()
#define pb push_back
#define pf push_front
#define popb pop_back
#define popf pop_front
#define fi first
#define se second
using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vector<ll>> vvll;
typedef vector<vector<pll>> vvpll;
typedef map<ll, ll> mll;
typedef set<ll> sll;

struct DSU
{
    ll comps;
    vll sz, par;
    DSU(ll n): sz(n + 1, 1), par(n + 1), comps(n){ iota(all(par), 0); }
    ll get(ll a){ return par[a] = (a == par[a] ? a : get(par[a])); }
    bool con(ll a, ll b){ return get(a) == get(b); }
    bool unite(ll a, ll b)
    {
        a = get(a), b = get(b);
        if (a == b)
            return false;
        if (sz[a] < sz[b])
            swap(a, b);
        par[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

struct BiPGraph
{
    vll p, r, dis;
    ll sz;
    BiPGraph(ll n): sz(n)
    {
        p = r = dis = vll(sz + 1);
        for (ll i{1}; i <= sz; i++)
            p[i] = i;
    }
    pll get(ll a)
    {
        if (a != p[a])
        {
            pll val = get(p[a]);
            p[a] = val.first, dis[a] += val.second, dis[a] %= 2;
        }
        return {p[a], dis[a]};
    }
    bool unite(ll a, ll b)
    {
        pll valA = get(a), valB = get(b);
        if (valA.first == valB.first)
            return dis[a] != dis[b];
        if (r[valA.first] == r[valA.first]) 
            r[valA.first]++;
        else if (r[valA.first] < r[valA.first]) 
            swap(a, b);
        p[valB.first] = valA.first;
        dis[valB.first] = valB.second + valA.second + 1, dis[valB.first] %= 2;
        return true;
    }
};
