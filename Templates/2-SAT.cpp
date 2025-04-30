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
    ll n, start;
    vvll adj;
    vll st, onSt, id, low;
    ll count, idCount;
    TarjanSCC() = default;
    TarjanSCC(vvll &adj, ll start = 1)
    : adj(adj), n(adj.size()), start(start)
    {
        onSt.assign(n, 0);
        low.assign(n, 0);
        id.assign(n, -1);
        count = idCount = 0;
        for (ll i{start}; i < n; i++)
            if (id[i] == -1)
                dfs(i);
        sll st(low.begin() + start, low.end());
        mll mp;
        for (auto &e: st)
            mp[e] = mp.size();
        for (auto &e: low)
            e = mp[e];
    }
    void dfs(ll u)
    {
        st.pb(u);
        onSt[u] = 1;
        low[u] = id[u] = idCount++;
        for (auto &v: adj[u])
        {
            if (id[v] == -1)
                dfs(v);
            if (onSt[v])
                low[u] = min(low[u], low[v]);
        }
        if (low[u] == id[u])
        {
            while (1)
            {
                ll v = st.back();
                low[v] = id[u];
                onSt[v] = 0;
                st.popb();
                if (v == u)
                    break;
            }
            count++;
        }
    }
    vvll getSccs()
    {
        vvll sccs(count);
        for (ll i{start}; i < n; i++)
            sccs[low[i]].pb(i);
        return sccs;
    }
    vvll getCondGraph()
    {
        vvll adjCond(count);
        for (ll u{start}; u < n; u++)
            for (auto &v: adj[u])
                if (low[u] != low[v])
                    adjCond[low[u]].pb(low[v]);
        return adjCond;
    }
};

struct TwoSAT
{
    ll n;
    vvll adj;
    TarjanSCC tar;
    TwoSAT(ll n): n(n), adj(2 * n + 1){}
    void assign(){ tar = TarjanSCC(adj); }
    ll getNode(ll x){ return (x > 0 ? x : abs(x) + n); }
    ll getOrig(ll x){ return (x > n ? x - n : x); }
    bool getVal(ll x){ return x <= n; }

    void implies(ll u, ll v){ adj[getNode(u)].pb(getNode(v)); }
    void OR(ll u, ll v){ implies(-u, v), implies(-v, u); }
    void AND(ll u, ll v){ OR(u, u), OR(v, v); }
    void XOR(ll u, ll v){ OR(u, v), OR(-u, -v); }
    void NOR(ll u, ll v){ AND(-u, -v); }
    void NAND(ll u, ll v){ OR(-u, -v); }
    void NXOR(ll u, ll v){ OR(u, -v), OR(-u, v); }

    bool check()
    {
        for (ll i{1}; i <= n; i++)
            if (tar.low[getNode(i)] == tar.low[getNode(-i)])
                return false;
        return true;
    }
    vll solve()
    {
        if (!check())
            return vll();
        vll res(n + 1, -1), vis(tar.count);
        vvll adj = tar.getCondGraph(), sccs = tar.getSccs();
        function<void(ll)> dfs = [&](ll u){
            vis[u] = 1;
            for (auto &v: adj[u])
                if (!vis[v])
                    dfs(v);
            for (auto &e: sccs[u])
                if (res[getOrig(e)] == -1)
                    res[getOrig(e)] = getVal(e);
        };
        for (ll i{}; i < tar.count; i++)
            if (!vis[i])
                dfs(i);
        // res.erase(res.begin());
        return res;
    }
};

// n: # of vars, m: sum of sizes of all comps
TwoSAT atMostOne(vvll comps, ll n, ll m)
{
    TwoSAT sat(n + m * 2);
    ll prev = 0;
    for (auto &c: comps)
    {
        ll sz = c.size();
        auto posA = [&](ll x){ return n + prev + x; };
        auto posB = [&](ll x){ return posA(x) + sz; };
        for (ll i{1}; i <= sz; i++)
        {
            ll e = c[i - 1];
            sat.implies(posA(i), -e);
            sat.implies(posB(i), -e);
            if (i < sz)
                sat.implies(posA(i), posA(i + 1)), sat.implies(e, posA(i + 1));
            if (i > 1)
                sat.implies(posB(i), posB(i - 1)), sat.implies(e, posA(i - 1));
        }
        prev += sz * 2;
    }
    return sat;
}