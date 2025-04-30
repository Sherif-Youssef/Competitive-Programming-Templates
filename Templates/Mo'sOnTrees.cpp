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


const ll blockSize;
struct Query
{
    ll l, r, idx, anc = -1;
    bool operator<(Query &other)
    {
        if (l / blockSize != other.l / blockSize)
            return l / blockSize < other.l / blockSize;
        if (l / blockSize & 1)
            return r < other.r;
        return r > other.r;
    }
};

template<class LCA>
struct MosTrees
{
    vll freq, freqNode;
    ll cnt;
    vvll adj;
    vll trav, val, st, en;
    vector<Query> queries;
    vpll tQueries;
    MosTrees(vvll &adj, vll val, vpll tQueries)
    : adj(adj), val(val), tQueries(tQueries)
    {
        ll n = adj.size(), m = tQueries.size();
        cnt = 0;
        freq.resize(n);
        freqNode.resize(n);
        st.resize(n);
        en.resize(n);
        trav.reserve(2 * n);
        queries.resize(m);
        LCA lca(adj);
        dfs(1);
        for (ll i{}; i < m; i++)
        {
            ll u, v;
            tie(u, v) = tQueries[i];
            if (st[u] > st[v])
                swap(u, v);
            ll anc = lca.query(u, v);
            Query &cu = queries[i];
            if (anc == u)
                cu.l = st[u], cu.r = st[v];
            else
                cu.l = en[u], cu.r = st[v], cu.anc = st[anc];
            cu.idx = i;
        }
    }
    void add(ll val)
    {
        freq[val]++;
        if (freq[val] == 1)
            cnt++;
    }
    void remove(ll val)
    {
        freq[val]--;
        if (freq[val] == 0)
            cnt--;
    }
    void update(ll idx, ll diff = 1)
    {
        ll u = trav[idx];
        freqNode[u] += diff;
        (freqNode[u] == 1 ? add(val[u]) : remove(val[u]));
    }
    ll get(){ return cnt; }
    void dfs(ll u, ll p = 0)
    {
        st[u] = trav.size();
        trav.pb(u);
        for (auto &v: adj[u])
            if (v != p)
                dfs(v, u);
        en[u] = trav.size();
        trav.pb(u);
    }
    vll run()
    {
        vll res(queries.size());
        sort(all(queries));
        ll cuL = 0, cuR = -1;
        for (auto &e: queries)
        {
            while (cuL > e.l)
                update(--cuL);
            while (cuR < e.r)
                update(++cuR);
            while (cuL < e.l)
                update(cuL++, -1);
            while (cuR > e.r)
                update(cuR--, -1);
            if (~e.anc)
                update(e.anc);
            res[e.idx] = get();
            if (~e.anc)
                update(e.anc, -1);
        }
        return res;
    }
};
