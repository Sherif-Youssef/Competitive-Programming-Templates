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

template<class T, class F>
struct PDSegTree
{
    struct Node
    {
        F merge;
        Node *l, *r;
        T val;
        Node(T val = T()): val(val), l(NULL), r(NULL){}
        Node(Node *l, Node *r, ll df): l(l), r(r), val(df)
        {
            if (l)
                val = merge(val, l->val);
            if (r)
                val = merge(val, r->val);
        }
        void extend(T cv = T())
        { 
            if (!l)
                l = new Node(cv);
            if (!r)
                r = new Node(cv); 
        }
    };
    ll lb, rb;
    F merge;
    Node *root;
    T defVal;
    vector<Node *> history;
    PDSegTree(ll lb, ll rb, T defVal = T())
    : lb(lb), rb(rb), defVal(defVal), root(new Node(defVal)){ history.pb(root); }
    Node *set(Node *v, ll l, ll r, ll pos, T val)
    {
        if (l == r)
            return new Node(val);
        v->extend(defVal);
        ll m = (l + r) / 2;
        if (pos <= m)
            return new Node(set(v->l, l, m, pos, val), v->r, defVal);
        return new Node(v->l, set(v->r, m + 1, r, pos, val), defVal);
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        if (tl <= l && tr >= r)
            return v->val;
        v->extend(defVal);
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    void set(ll pos, T val){ history.pb(set(history.back(), lb, rb, pos, val)); }
    T get(ll l, ll r){ return get(history.back(), lb, rb, l, r); }
    T get(ll l, ll r, ll h){ return get(history[h], lb, rb, l, r); }
};