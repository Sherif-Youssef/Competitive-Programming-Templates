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

struct LCA
{
    vvll goUp;
    vll depth;
    ll n, lg;

    LCA(vvll &adj, ll root = 1): n(adj.size()), lg(log2(n) + 1)
    {
        goUp.assign(n, vll(lg));
        depth.assign(n, 0);
        dfs(adj, root);
    }
    void dfs(vvll &adj, ll node, ll par = -1, ll dep = 0)
    {
        depth[node] = dep;
        goUp[node][0] = par;
        for (ll i{1}; i < lg && (1 << i) <= dep; i++)
            goUp[node][i] = goUp[goUp[node][i - 1]][i - 1];

        for (each e: adj[node])
            if (e != par)
                dfs(adj, e, node, dep + 1);
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
        if (depth[u] < depth[v])
            swap(u, v);
        u = getKthAnc(u, depth[u] - depth[v]);
        if (u == v)
            return u;
        for (ll i{lg - 1}; i >= 0; i--)
            if (goUp[u][i] != goUp[v][i])
                u = goUp[u][i], v = goUp[v][i];
        return goUp[u][0];
    }
    ll distance(ll u, ll v)
    {
        ll d = depth[query(u, v)];
        return depth[u] + depth[v] - d * 2;
    }
};