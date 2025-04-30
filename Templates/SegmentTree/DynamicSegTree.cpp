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
struct DynamicSegTree
{
    struct Node
    {
        Node *l, *r;
        T val;
        Node(T val = T()): val(val), l(NULL), r(NULL){}
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
    DynamicSegTree(ll lb, ll rb, T defVal = T())
    : lb(lb), rb(rb), defVal(defVal), root(new Node(defVal)){}
    void set(Node *v, ll l, ll r, ll pos, T val)
    {
        if (l == r)
            return void(v->val = val);
        v->extend(defVal);
        ll m = (l + r) / 2;
        if (pos <= m)
            set(v->l, l, m, pos, val);
        else
            set(v->r, m + 1, r, pos, val);
        v->val = merge(v->l->val, v->r->val);
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (!v || tl > tr)
            return T();
        if (tl <= l && tr >= r)
            return v->val;
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    void set(ll pos, T val){ set(root, lb, rb, pos, val); }
    T get(ll l, ll r){ return get(root, lb, rb, l, r); }
};