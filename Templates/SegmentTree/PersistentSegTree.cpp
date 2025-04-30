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


template<class T, class F>
struct PersistentSegTree
{
    struct Node
    {
        F merge;
        Node *l, *r;
        T val;
        Node(T val): val(val), l(NULL), r(NULL){}
        Node(Node *l, Node* r): val(), l(l), r(r)
        {
            if (l)
                val = merge(val, l->val);
            if (r)
                val = merge(val, r->val);
        }
    };
    ll n;
    F merge;
    vector<Node*> history;
    PersistentSegTree(vector<T> data): n(data.size())
    {
        history.pb(build(data, 0, n - 1));
    }
    Node* build(vector<T> &data, ll l, ll r)
    {
        if (l == r)
            return new Node(data[l]);
        ll m = (l + r) / 2;
        return new Node(build(data, l, m), build(data, m + 1, r));
    }
    Node* set(Node *v, ll l, ll r, ll pos, T val)
    {
        if (l == r)
            return new Node(val); 
        ll m = (l + r) / 2;
        if (pos <= m)
            return new Node(set(v->l, l, m, pos, val), v->r);
        return new Node(v->l, set(v->r, m + 1, r, pos, val));
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        if (l == tl && r == tr)
            return v->val;
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    ll getKth(Node *vl, Node *vr, ll l, ll r, ll k)
    {
        if (l == r)
            return l;
        ll m = (l + r) / 2, left = vr->l->val - vl->l->val;
        if (left >= k)
            return getKth(vl->l, vr->l, l, m, k);
        return getKth(vl->r, vr->r, m + 1, r, k - left);
    }
    void set(ll pos, T val)
    {
        history.pb(set(history.back(), 0, n - 1, pos, val));
    }
    T get(ll l, ll r, ll h){ return get(history[h], 0, n - 1, l, r); }
    T get(ll l, ll r){ return get(history.back(), 0, n - 1, l, r); }
    ll getKth(ll l, ll r, ll k)
    { 
        return getKth(history[l], history[r + 1], 0, n - 1, k);
    }
};

template<class F>
struct PersistentSegTreePaths
{
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
    struct Node
    {
        Node *l, *r;
        F merge;
        ll val;
        Node(ll val): val(val), l(NULL), r(NULL){}
        Node(Node *l, Node* r): val(), l(l), r(r)
        {
            if (l)
                val = merge(val, l->val);
            if (r)
                val = merge(val, r->val);
        }
    };
    
    ll n;
    F merge;
    vector<Node*> history, roots;
    LCA lca;
    PersistentSegTreePaths(vvll &adj, vll val)
    : lca(adj), roots(adj.size())
    {
        n = *max_element(all(val)) + 1;
        history.pb(build(0, n - 1));
        roots[0] = history.back();
        dfs(adj, val, 1, -1);
    }
    void dfs(vvll &adj, vll &val, ll u, ll p)
    {
        modify(val[u], 1);
        roots[u] = history.back();
        for (auto &v: adj[u])
            if (v != p)
                dfs(adj, val, v, u);
        modify(val[u], -1);
    }
    Node* build(ll l, ll r)
    {
        if (l == r)
            return new Node(0);
        ll m = (l + r) / 2;
        return new Node(build(l, m), build(m + 1, r));
    }
    
    Node* modify(Node *v, ll l, ll r, ll pos, ll val)
    {
        if (l == r)
            return new Node(v->val + val); 
        ll m = (l + r) / 2;
        if (pos <= m)
            return new Node(modify(v->l, l, m, pos, val), v->r);
        return new Node(v->l, modify(v->r, m + 1, r, pos, val));
    }
    ll get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return 0;
        if (l == tl && r == tr)
            return v->val;
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    ll getKth(Node *u, Node *v, Node *anc, Node *panc, ll l, ll r, ll k)
    {
        if (l == r)
            return l;
        ll m = (l + r) / 2;
        ll left = u->l->val + v->l->val - anc->l->val - panc->l->val;
        if (left >= k)
            return getKth(u->l, v->l, anc->l, panc->l, l, m, k);
        return getKth(u->r, v->r, anc->r, panc->r, m + 1, r, k - left);
    }
    
    void modify(ll pos, ll val)
    { 
        history.pb(modify(history.back(), 0, n - 1, pos, val)); 
    }
    ll getKth(ll u, ll v, ll k)
    {
        ll anc = lca.query(u, v);
        ll panc = (anc == 1 ? 0 : lca.getKthAnc(anc, 1));
        return getKth(roots[u], roots[v], roots[anc], roots[panc], 0, n - 1, k);
    }
    ll get(ll u, ll l, ll r){ return get(roots[u], 0, n - 1, l, r); }
};
