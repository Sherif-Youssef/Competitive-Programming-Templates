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

struct SparseTable
{
    vvpll pre;
    vll lg;
    ll n;

    SparseTable() = default;
    SparseTable(vpll data): n(data.size())
    {
        lg.resize(n + 1);
        for (ll i{2}; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        pre.assign(n, vpll(lg[n] + 1));

        for (ll i{}; i < n; i++)
            pre[i][0] = data[i];
        for (ll p{1}; p <= lg[n]; p++)
            for (ll i{}; i + (1 << p) - 1 < n; i++)
                pre[i][p] = min(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
    }
    pll query(ll a, ll b)
    {
        ll p = lg[b - a + 1];
        return min(pre[a][p], pre[b - (1 << p) + 1][p]);
    }
};
 
struct LCA
{
    SparseTable table;
    vector<ll> pos, depth;
    vector<pll> euler;
    ll n;
 
    LCA(vector<vector<ll>> &adj, ll root = 1): n(adj.size())
    {
        pos = depth = vector<ll>(n);
        dfs(adj, root);
        table = SparseTable(euler);
    }
    void dfs(vector<vector<ll>> &adj, ll node = 1, ll par = -1, ll dep = 0)
    {
        pos[node] = euler.size();
        depth[node] = dep;
        euler.pb({node, dep});
        for (each e: adj[node])
            if (e != par)
                dfs(adj, e, node, dep + 1), euler.pb({node, dep});
    }
    ll query(ll u, ll v)
    {
        u = pos[u];
        v = pos[v];
        if (u > v)
            swap(u, v);
        return table.query(u, v).first;
    }
    ll distance(ll u, ll v)
    {
        ll d = depth[query(u, v)];
        return depth[u] + depth[v] - d * 2;
    }
};