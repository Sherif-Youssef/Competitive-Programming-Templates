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

template<class T, class M, class Op, class A>
struct DLSegTree
{
    struct Node
    {
        A applyOp;
        Node *l, *r;
        T val;
        Op op;
        Node(T val = T()): val(val), l(NULL), r(NULL), op(){}
        void extend(T cv = T())
        { 
            if (!l)
                l = new Node(cv);
            if (!r)
                r = new Node(cv); 
        }
        void apply(Op newOp)
        { 
            val = applyOp(val, newOp), op.apply(newOp); 
        }
        void propegate()
        {
            if (!l || !r)
                return;
            l->apply(op), r->apply(op);
            op = Op();
        }
    };
    ll lb, rb;
    M merge;
    Node *root;
    T defVal;
    DLazySegTree(ll lb, ll rb, T defVal = T())
    : lb(lb), rb(rb), defVal(defVal), root(new Node(defVal)){}
    void modify(Node *v, ll l, ll r, ll tl, ll tr, Op op)
    {
        if (tl > tr)
            return;
        v->extend(defVal), v->propegate();
        if (tl == l && tr == r)
            return void(v->apply(op));
        ll m = (l + r) / 2;
        modify(v->l, l, m, tl, min(tr, m), op);
        modify(v->r, m + 1, r, max(tl, m + 1), tr, op);
        v->val = merge(v->l->val, v->r->val);
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        v->extend(defVal), v->propegate();
        if (tl <= l && tr >= r)
            return v->val;
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    void modify(ll l, ll r, Op op){ modify(root, lb, rb, l, r, op); }
    T get(ll l, ll r){ return get(root, lb, rb, l, r); }
};