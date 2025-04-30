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


template<class T, class F>
struct CentroidDecomp
{
    vvll adj;
    vll marked, parCent, parDist, sz, dist;
    vector<T> val;
    vector<vector<T>> pre;
    vvll lens;
    F merge;
    CentroidDecomp(vvll adj, vector<T> val, ll start = 1)
    : adj(adj), val(val)
    { 
        ll n = adj.size();
        pre.resize(n), marked.resize(n);
        parCent.resize(n), parDist.resize(n);
        sz.resize(n), dist.resize(n);
        decompose(start);
    }
    void dfsSize(ll u, ll p = -1)
    {
        sz[u] = 1;
        for (auto &v: adj[u])
            if (v != p && !marked[v])
                dfsSize(v, u), sz[u] += sz[v];
    }
    ll dfsCent(ll n, ll u, ll p = -1)
    {
        for (auto &v: adj[u])
            if (v != p && !marked[v] && sz[v] > n / 2)
                return dfsCent(n, v, u);
        return u;
    }
    void dfsPP(vll &cur, ll u, ll p = -1, ll d = 0)
    {
        if (marked[u])
            return;
        dist[u] = d, cur.pb(u);
        for (auto &v: adj[u])
            if (v != p) 
                dfsPP(cur, v, u, d + 1);
    }
    void decompose(ll u, ll p = -1, ll d = 0)
    {
        dfsSize(u);
        ll n = sz[u], cent = dfsCent(n, u);
        vll cur;
        dfsPP(cur, cent);

        vpll tmp;
        for (auto &e: cur)
            tmp.pb({dist[e], e});
        sort(all(tmp));
        for (auto &[d, e]: tmp)
            lens[cent].pb(d), pre[cent].pb(val[e]);
        for (ll i{1}; i < n; i++)
            pre[cent][i] = merge(pre[cent][i - 1], pre[cent][i]);
        
        marked[cent] = 1, parCent[cent] = p, parDist[cent] = d;
        for (auto &v: adj[cent])
            if (!marked[v])
                decompose(v, cent, dist[v]);
    }
    T query(ll u, ll d)
    {
        T res = T();
        while (~u && d >= 0)
        {
            ll idx = upper_bound(all(lens[u]), d) - lens[u].begin() - 1;
            res = merge(res, pre[u][idx]);
            u = parCent[u], d -= parDist[d];
        }
        return res;
    }
};