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

struct TarjanSCC
{
    ll n, start, count, curId;
    vvll adj;
    vll st, onSt, id, low;
    TarjanSCC(vvll &adj, ll start = 1)
    : adj(adj), n(adj.size()), start(start)
    {
        count = curId = 0;
        onSt.resize(n);
        id.assign(n, -1), low.resize(n);

        for (ll i{start}; i < n; i++)
            if (id[i] == -1)
                dfs(i);
        
        compress();
    }
    void compress()
    {
        vll sizes(n), cls(n);
        for (ll i{start}; i < n; i++)
            sizes[low[i]]++;

        ll cnt = 0;
        for (ll i{}; i < n; i++)
            cls[i] = cnt, cnt += sizes[i] > 0;
        
        for (ll i{start}; i < n; i++)
            low[i] = cls[low[i]];
    }
    void dfs(ll u)
    {
        st.pb(u);
        onSt[u] = 1;
        low[u] = id[u] = curId++;

        for (auto &v: adj[u])
        {
            if (id[v] == -1)
                dfs(v);
            if (onSt[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == id[u])
        {
            while (true)
            {
                ll v = st.back();
                low[v] = low[u], onSt[v] = 0;
                st.popb();
                if (u == v)
                    break;
            }
            count++;
        }
    }
    vvll getSCCs()
    {
        vvll SCCs(count);
        for (ll i{start}; i < n; i++)
            SCCs[low[i]].pb(i);
        return SCCs;
    }
    vvll getCondGraph(bool rev = 0)
    {
        vvll adjCond(count);
        for (ll u{start}; u < n; u++)
            for (auto &v: adj[u])
                if (low[u] != low[v])
                    (rev ? adjCond[low[v]].pb(low[u]) : adjCond[low[u]].pb(low[v]));
        
        for (auto &v: adjCond)
        {
            sll st(all(v));
            v.assign(all(st));
        }
        return adjCond;
    }
};

struct ArtPoints
{
    ll n, tmr;
    vvll adj;
    vll vis, tin, low, cut, points, sz;
    ArtPoints(vvll &adj): adj(adj), n(adj.size())
    {
        tmr = 0;
        vis.resize(n), low.resize(n);
        tin.resize(n), cut.resize(n);
        sz.resize(n);

        for (ll i{}; i < n; i++)
            if (!vis[i])
                dfs(i);
    }
    void dfs(ll u, ll p = -1)
    {
        vis[u] = 1;
        tin[u] = low[u] = tmr++;
        ll children = 0;
        for (auto &v: adj[u])
        {
            if (!vis[v])
            {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                sz[u] += ~p && low[v] >= tin[u];
                children++;
            }
            else if (v != p)
                low[u] = min(low[u], tin[v]);
        }
        sz[u] += (p == -1 ? children : 1);
        
        cut[u] = sz[u] > 1;
        if (cut[u])
            points.pb(u);
    }
};

struct Bridges
{
    ll n, m, tmr, start;
    vvpll adj;
    vll vis, tin, low, cut, bridges;
    Bridges(vvpll &adj, ll m, ll start = 1)
    : adj(adj), n(adj.size()), m(m), start(start)
    {
        tmr = 0;
        vis.resize(n), tin.resize(n), low.resize(n);
        cut.resize(m);
        for (ll i{start}; i < n; i++)
            if (!vis[i])
                dfs(i);

        for (ll i{}; i < m; i++)
            if (cut[i])
                bridges.pb(i);
    }
    ll dfs(ll u, ll p = -1)
    {
        vis[u] = 1;
        tin[u] = low[u] = tmr++;
        bool skippedPar = false;
        for (auto &[v, i]: adj[u])
        {
            if (v == p && !skippedPar)
                skippedPar = true;
            else if (!vis[v])
                low[u] = min(low[u], dfs(v, u)), cut[i] |= low[v] > tin[u];
            else    
                low[u] = min(low[u], tin[v]);
        }
        return low[u];
    }
    vpll getBridgeNodes()
    {
        vpll res;
        for (ll u{start}; u < n; u++)
            for (auto &[v, i]: adj[u])
                if (v > u && cut[i])
                    res.pb({u, v});
        return res;
    }
    pair<vvll, vll> getCondGraph()
    {
        fill(all(vis), 0);
        vll comp(n), sz;
        function<ll(ll)> dfsCond = [&](ll u){
            vis[u] = 1;
            comp[u] = sz.size();
            ll res = 1;
            for (auto &[v, i]: adj[u])
                if (!vis[v] && !cut[i])
                    res += dfsCond(v);
            return res;
        };
        for (ll i{start}; i < n; i++)
            if (!vis[i])
                sz.pb(dfsCond(i));

        vvll adjCond(sz.size());
        for (auto [u, v]: getBridgeNodes())
            u = comp[u], v = comp[v], adjCond[u].pb(v), adjCond[v].pb(u);
        
        return {adjCond, sz};
    }
};

vpll directGraph(vpll &edges, ll n)
{
    n++;
    vvpll adj(n);
    ll m = edges.size(), idx = 0;
    for (auto &[a, b]: edges)
        adj[a].pb({b, idx}), adj[b].pb({a, idx}), idx++;
    
    vector<sll> adjSt(n);
    Bridges bridges(adj, m);
    vpll res;

    for (ll i{}; i < m; i++)
    {
        ll a, b;
        tie(a, b) = edges[i];
        if (bridges.cut[i])
            res.pb({a, b}), res.pb({b, a});
        else
            adjSt[a].insert(b), adjSt[b].insert(a);
    }

    static function<void(ll)> dfs = [&](ll u){
        while (!adjSt[u].empty())
        {
            ll v = *adjSt[u].begin();
            adjSt[u].erase(v), adjSt[v].erase(u);
            res.pb({u, v});
            dfs(v);
        }
    };

    for (ll i{}; i < n; i++)
        dfs(i);
    
    return res;
}
