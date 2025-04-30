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

const ll INF = 1e18;

vll bfs(vvll &adj, vll start)
{
    ll n = adj.size();
    deque<ll> dq;
    vll dist(n, INF);
    for (auto &e: start)
        dist[e] = 0, dq.pb(e);
    while (!dq.empty())
    {
        ll u = dq.front();
        dq.popf();

        for (auto &v: adj[u])
            if (dist[v] > dist[u] + 1)
                dist[v] = dist[u] + 1, dq.pb(v);
    }
    return dist;
}

vll dijkstra(vvpll &adj, vll start)
{
    ll n = adj.size();
    priority_queue<pll> pq;
    vll dist(n, INF);
    for (auto &e: start)
        dist[e] = 0, pq.push({0, e});
    while (!pq.empty())
    {
        ll d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (-d != dist[u])
            continue;
        for (auto &[v, w]: adj[u])
            if (dist[v] > dist[u] + w)
                dist[v] = dist[u] + w, pq.push({-dist[v], v});
    }
    return dist;
}

struct Edge{ ll u, v, w; };

vll bellmanFord(vector<Edge> &edges, ll n, ll start)
{
    vll d(n + 1, INF);
    d[start] = 0;
    for (ll i{}; i < n - 1; i++)
        for (auto &[u, v, w]: edges)
            if (d[v] > d[u] + w)
                d[v] = d[u] + w;

    for (ll i{}; i < n - 1; i++)
        for (auto &[u, v, w]: edges)
            if (d[v] > d[u] + w)
                d[v] = -INF;
    return d;
}

// min distance between any two nodes
ll minDist(vector<Edge> &edges, ll n)
{
    vll d(n + 1, 0);
    for (ll i{}; i < n - 1; i++)
        for (auto &[u, v, w]: edges)
            d[v] = min(d[v], d[u] + w);

    for (ll i{}; i < n - 1; i++)
        for (auto &[u, v, w]: edges)
            if (d[v] > d[u] + w)
                return -INF;

    return *min_element(all(d));    
}

vvll floydWarshall(vvpll &adj)
{
    ll n = adj.size();
    vvll d(n, vll(n, INF));
    for (ll u{}; u < n; u++)
        d[u][u] = 0;

    for (ll u{}; u < n; u++)
        for (auto [v, c]: adj[u])
            d[u][v] = min(d[u][v], c);
    
    for (ll k{}; k < n; k++)
        for (ll i{}; i < n; i++)
            for (ll j{}; j < n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];

    for (ll k{}; k < n; k++)
        for (ll i{}; i < n; i++)
            for (ll j{}; j < n; j++)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = -INF;
    return d;
}

bool checkArbitrage(vvpll &adj)
{
    ll n = adj.size();
    vvll d(n, vll(n, 0));
    for (ll u{}; u < n; u++)
        d[u][u] = 1;
    
    for (ll u{}; u < n; u++)
        for (auto [v, c]: adj[u])
            d[u][v] = max(d[u][v], c);

    for (ll k{}; k < n; k++)
        for (ll i{}; i < n; i++)
            for (ll j{}; j < n; j++)
                if (d[i][j] < d[i][k] * d[k][j])
                    d[i][j] = d[i][k] * d[k][j];

    for (ll i{}; i < n; i++)
        for (ll j{}; j < n; j++)
            if (d[i][j] * d[j][i] > 1)
                return true;

    return false;
}

vll getEulerianPath(vector<multiset<ll>> &adj)
{
    ll n = adj.size(), start = 1, odd = 0, tot = 0;
    for (ll i{}; i < n; tot += adj[i++].size())
        if (adj[i].size() & 1)
            odd++, start = i;

    if (odd != 0 && odd != 2)
        return vll();
    
    vll res;
    function<void(ll)> dfs = [&](ll u){
        while (!adj[u].empty())
        {
            ll v = *adj[u].begin();
            adj[u].erase(adj[u].find(v));
            adj[v].erase(adj[v].find(u));
            dfs(v);
        }
        res.pb(u);
    };
    dfs(start);
    if (res.size() != tot / 2 + 1)
        return vll();
    
    return res;
}

vll getEulerianPathDi(vvll &adj)
{
    ll n = adj.size(), start{-1}, end{-1}, tot{};
    vll in(n), out(n);
    for (ll i{}; i < n; tot += adj[i++].size())
    {
        out[i] = adj[i].size();
        for (auto &e: adj[i])
            in[e]++;
    }
    bool pos = 1;
    for (ll i{}; i < n; i++)
    {
        if (in[i] - out[i] == 1)
            pos &= !~end, end = i;
        else if (in[i] - out[i] == -1)
            pos &= !~start, start = i;
        else if (in[i] != out[i])
            pos = 0;
    }
    if (!pos)
        return vll();

    if (!~start)
        for (ll i{}; i < n; i++)
            if (!adj[i].empty())
                start = i;

    vll res;
    static function<void(ll)> dfs = [&](ll u){
        while (out[u])
            dfs(adj[u][--out[u]]);
        res.pb(u);
    };

    dfs(start);
    reverse(all(res));
    if (res.size() != tot + 1)
        return vll();
    
    return res;
}

vll getTreeCenters(vvll &adj)
{
    deque<ll> leaves;
    ll n = adj.size();
    vll degree(n);
    for (ll u{}; u < n; u++)
        if ((degree[u] = adj[u].size()) < 2)
            leaves.pb(u);
    ll count = leaves.size();
    while (count < n)
    {
        ll sz = leaves.size();
        for (ll i{}; i < sz; i++)
        {
            ll u = leaves.front();
            leaves.popf();
            for (auto &v: adj[u])
                if (--degree[v] == 1)
                    leaves.pb(v), count++;
        }
    }
    return vll(all(leaves));
}

string encodeTree(vvll &adj, ll u, ll p = 0)
{
    vector<string> children;
    string cu{'('};
    for (auto &v: adj[u])
        if (v != p)
            children.pb(encodeTree(adj, v, u));
    sort(all(children));
    for (auto &e: children)
        cu.append(e);
    cu.pb(')');
    return cu;
}

ll encodeTreeHash(vvll &adj, ll u, ll p = 0, ll dep = 53, ll MOD = 1e9 + 7)
{
    ll hash{1};
    for (auto &v: adj[u])
        if (v != p)
            hash *= encodeTreeHash(adj, v, u, dep * 53 % MOD), hash %= MOD;

    return (hash + 1) * dep % MOD;
}
