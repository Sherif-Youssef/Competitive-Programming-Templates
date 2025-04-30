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

// when doing HLD on edges:
// value for each node is the value of the edge that leads to its parent
// subtract one from the range query when the two nodes are in the same chain
template<class T, class F>
struct HLD
{
    ll n;
    F merge;
    vvll adj;
    vector<T> val, data;
    vll dep, sz, par, head, pos;
    SegTree<T, F> tree;
    HLD(vvll &adj, vector<T> val)
    : adj(adj), val(val), n(adj.size())
    {
        dep = sz = par = head = pos = vll(n);
        data.reserve(n);
        preprocess(1), decompose(1);
        tree = SegTree<T, F>(data);
    }
    void preprocess(ll u, ll p = 0)
    {
        sz[u] = 1, dep[u] = dep[p] + 1, par[u] = p;
        for (auto &v: adj[u])
            if (v != p)
                preprocess(v, u), sz[u] += sz[v];
    }
    void decompose(ll u, ll cnt = 1)
    {
        ll heavyCh = 0;
        for (auto &v: adj[u])
            if (v != par[u] && sz[v] > sz[heavyCh])
            heavyCh = v;

        if (heavyCh)
        {
            decompose(heavyCh, cnt + 1);
            for (auto &v: adj[u])
                if (v != par[u] && v != heavyCh)
                    decompose(v);
        }
        else
        {
            ll hd = u;
            for (ll i{1}; i < cnt; i++, hd = par[hd]);
            for (ll cu = u, i{}; i < cnt; cu = par[cu], i++)
            {
                pos[cu] = data.size();
                data.pb(val[cu]);
                head[cu] = hd;
            }
        }
    }
    T get(ll u, ll v)
    {
        T res = T();
        while (true)
        {
            if (head[u] == head[v])
            {
                if (pos[u] > pos[v])
                    swap(u, v);
                res = merge(res, tree.get(pos[u], pos[v]));
                break;
            }
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            res = merge(res, tree.get(pos[u], pos[head[u]]));
            u = par[head[u]];
        }
        return res;
    }
    void set(ll u, T val){ tree.set(pos[u], val); }
};

template<class T, class M, class Op, class A>
struct LazyHLD
{
    ll n;
    M merge;
    vvll adj;
    vector<T> val, data;
    vll dep, sz, par, head, pos;
    LazySegTree<T, M, Op, A> tree;
    LazyHLD(vvll &adj, vector<T> val)
    : adj(adj), val(val), n(adj.size())
    {
        dep = sz = par = head = pos = vll(n);
        data.reserve(n);
        preprocess(1), decompose(1);
        tree = LazySegTree<T, M, Op, A>(data);
    }
    void modify(ll u, ll v, Op op)
    {
        while (true)
        {
            if (head[u] == head[v])
            {
                if (pos[u] > pos[v])
                    swap(u, v);
                tree.modify(pos[u], pos[v], op);
                break;
            }
            if (dep[head[u]] < dep[head[v]])
                swap(u, v);
            tree.modify(pos[u], pos[head[u]], op);
            u = par[head[u]];
        }
    }
};