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

struct Sack
{
    ll n;
    vvll adj;
    vll sz, dep, val, res;
    vector<bool> vis;
    Sack(vvll adj, vll val)
    : n(adj.size()), adj(adj), val(val)
    {
        dep.resize(n);
        sz.resize(n);
        res.resize(n);
        vis.resize(n);
        for (ll i{1}; i < n; i++)
            if (!vis[i])
                dfsPP(i), dfs(i);
    }
    void dfsPP(ll u, ll p = 0)
    {
        sz[u] = 1, dep[u] = dep[p] + 1, vis[u] = 1;
        for (auto &v: adj[u])
            if (v != p)
                dfsPP(v, u), sz[u] += sz[v];
    }
    void modify(ll u, ll p, ll largeCh, ll diff)
    {
        // adding / removing values here
        

        for (auto &v: adj[u])
            if (v != p && v != largeCh)
                modify(v, u, -1, diff);
    }
    void dfs(ll u, ll p = 0, bool large = 0)
    {
        ll largeCh = 0;
        for (auto &v: adj[u])
            if (v != p && sz[v] > sz[largeCh])
                largeCh = v;
        for (auto &v: adj[u])
            if (v != p && v != largeCh)
                dfs(v, u, 0);
        if (largeCh)
            dfs(largeCh, u, 1);

        modify(u, p, largeCh, 1);

        // processing here

        if (!large)
            modify(u, p, -1, -1);
    }
};