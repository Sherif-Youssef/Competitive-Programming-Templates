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

const ll N = 4e4 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18;

template<class T, class F>
struct LCA
{
    ll n, lg;
    F merge;
    vvll adj, goUp;
    vector<vector<T>> fn;
    vector<T> val;
    vll dep;

    LCA(vvll &adj, vector<T> &val, ll root = 1)
    : n(adj.size()), adj(adj), val(val), lg(log2(n) + 1)
    {
        goUp.assign(n, vll(lg));
        fn.assign(n, vector<T>(lg));
        dep.resize(n);
        dfs(root);
    }
    void dfs(ll u, ll p = 0, ll d = 0)
    {
        dep[u] = d;
        goUp[u][0] = p;
        fn[u][0] = val[p];
        for (ll i{1}; (1 << i) <= d; i++)
        {
            goUp[u][i] = goUp[goUp[u][i - 1]][i - 1];
            fn[u][i] = merge(fn[u][i - 1], fn[goUp[u][i - 1]][i - 1]);
        }
        for (auto &v: adj[u])
            if (v != p)
                dfs(v, u, d + 1);
    }
    ll getKthAnc(ll u, ll k)
    {
        for (ll i{lg - 1}; i >= 0 && k; i--)
            if ((1 << i) <= k)
                u = goUp[u][i], k -= (1 << i);
        return u;
    }
    ll query(ll u, ll v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        u = getKthAnc(u, dep[u] - dep[v]);
        if (u == v)
            return u;
        for (ll i{lg - 1}; i >= 0; i--)
            if (goUp[u][i] != goUp[v][i])
                u = goUp[u][i], v = goUp[v][i];
        return goUp[u][0];
    }
    ll distance(ll u, ll v)
    {
        ll d = dep[query(u, v)];
        return dep[u] + dep[v] - d * 2;
    }
    T getKthFn(ll u, ll k)
    {
        T cu = val[u];
        for (ll i{lg - 1}; i >= 0 && k; i--)
            if ((1 << i) <= k)
                cu = merge(cu, fn[u][i]), u = goUp[u][i], k -= (1 << i);
        return cu;
    }
    T getFn(ll u, ll v)
    {
        if (dep[u] > dep[v])
            swap(u, v);
        ll d = dep[query(u, v)];
        return merge(getKthFn(u, dep[u] - d), getKthFn(v, dep[v] - d - 1), 1);
    }
};

ll pows[N];
struct Seg
{
    ll hash, revHash, len;
    Seg(): hash(0), revHash(0), len(0){}
    Seg(char c): hash(c - 'a' + 1), revHash(c - 'a' + 1), len(1) {}
    Seg(ll hash, ll revHash, ll len): hash(hash), revHash(revHash), len(len){}
};

struct Merge
{
    Seg operator()(Seg a, Seg b, bool rev = false)
    {
        if (rev)
            swap(b.hash, b.revHash);
        ll hash = a.hash + b.hash * pows[a.len];
        ll revHash = a.revHash * pows[b.len] + b.revHash;
        hash %= MOD, revHash %= MOD;
        return Seg(hash, revHash, a.len + b.len);
    }
};