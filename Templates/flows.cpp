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

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18;

struct Dijkstra
{
    ll operator()(vvll &adj, vvll &cap, ll src, ll des, vll &par)
    {
        priority_queue<pll> pq;
        ll n = cap.size();
        vll flow(n, 0);
        par.resize(n, -1);
        pq.push({INF, src}), flow[src] = INF;
        while (!pq.empty() && pq.top().first > 0 && pq.top().second != des)
        {
            ll c, u;
            tie(c, u) = pq.top();
            pq.pop();
            if (flow[u] != c)
                continue;
            for (auto &v: adj[u])
            {
                if (flow[v] < min(flow[u], cap[u][v]))
                {
                    flow[v] = min(flow[u], cap[u][v]);
                    pq.push({flow[v], v});
                    par[v] = u;
                }
            }
        }
        return flow[des];
    }
};
 
struct BFS
{
    ll operator()(vvll &adj, vvll &cap, ll src, ll des, vll &par)
    {
        ll n = adj.size();
        vll flow(n, 0);
        par.resize(n, -1);
        deque<ll> dq;
        dq.pb(src), flow[src] = INF;
        while (!dq.empty() && dq.front() != des)
        {
            ll u = dq.front();
            dq.popf();
            for (auto &v: adj[u])
            {
                if (flow[v] < min(flow[u], cap[u][v]))
                {
                    flow[v] = min(flow[u], cap[u][v]);
                    dq.pb(v);
                    par[v] = u;
                }
            }
        }
        return flow[des];
    }
};

template<class PathAlgo>
struct FordFulkerson
{
    vvll adj, cap;
    vll vis;
    ll n, src, des, flow{-1};
    PathAlgo getPath;
    FordFulkerson(vvll &adj, vvll &cap, ll src, ll des)
    : n(cap.size()), adj(adj), cap(cap), src(src), des(des){}
    ll getMaxFlow()
    {
        flow = 0;
        ll newFlow;
        vll par;
        while (newFlow = getPath(adj, cap, src, des, par))
        {
            ll cur = des;
            while (cur != src)
            {
                cap[par[cur]][cur] -= newFlow;
                cap[cur][par[cur]] += newFlow;
                cur = par[cur];
            }
            flow += newFlow;
        }
        return flow;
    }
    void floodFill(ll u)
    {
        vis[u] = 1;
        for (auto &v: adj[u])
            if (!vis[v] && cap[u][v])
            floodFill(v);
    }
    vpll getMinCutEdges()
    {
        if (flow == -1)
            getMaxFlow();
        vis.assign(n, 0);
        vpll edges;
        floodFill(src);
        for (ll u{}; u < n; u++)
            for (auto &v: adj[u])
                if (vis[u] && !vis[v])
                    edges.pb({u, v});
        return edges;
    }
};

struct Kuhn
{
    ll n, m;
    vvll adj;
    vll top, bottom, vis;
    ll maxFlow;
    Kuhn(vvll &adj, ll n, ll m)
    : n(n), m(m), adj(adj), maxFlow(0)
    {
        top = vis = vll(n, -1);
        bottom = vll(m, -1);
        for (ll i{}; i < n; i++)
            maxFlow += canMatch(i, i);
    }
    bool canMatch(ll u, ll ori)
    {
        if (vis[u] == ori)
            return false;
        vis[u] = ori;
        for (auto v: adj[u])
        {
            if (bottom[v] == -1 || canMatch(bottom[v], ori))
            {
                top[u] = v, bottom[v] = u;
                return true;
            }
        }
        return false;
    }
    vpll getMatches()
    {
        vpll res;
        for (ll i{}; i < n; i++)
            if (top[i] != -1)
                res.pb({i, top[i]});
        return res;
    }
};