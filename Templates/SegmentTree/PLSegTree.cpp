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
struct PLSegTree
{
    struct Node
    {
        A applyOp;
        M merge;
        Node *l, *r;
        T val;
        Op op;
        bool hasOp;
        Node(T val): val(val), l(NULL), r(NULL), op(), hasOp(0){}
        Node(Node *l, Node *r): val(), l(l), r(r), op(), hasOp(0)
        {
            if (l)
                val = merge(val, l->val);
            if (r)
                val = merge(val, r->val);
        }
        void apply(Op newOp)
        { 
            val = applyOp(val, newOp), op.apply(newOp); 
            hasOp = 1;
        }
        static Node *newLazyNode(Node *v, Op op)
        {
            Node *node = new Node(*v);
            node->apply(op);
            return node;
        }
        void propegate()
        {
            if (!hasOp)
                return;
            if (l)
                l = newLazyNode(l, op);
            if (r)
                r = newLazyNode(r, op);
            op = Op(), hasOp = 0;
        }
    };
    ll n;
    M merge;
    vector<Node *> history;
    PLazySegTree(vector<T> data): n(data.size())
    {
        history.pb(build(data, 0, n - 1));
    }
    Node *build(vector<T> &data, ll l, ll r)
    {
        if (l == r)
            return new Node(data[l]);
        ll m = (l + r) / 2;
        return new Node(build(data, l, m), build(data, m + 1, r));
    }
    Node *modify(Node *v, ll l, ll r, ll tl, ll tr, Op op)
    {
        if (tl > tr)
            return v;
        if (tl == l && tr == r)
            return Node::newLazyNode(v, op);    
        v->propegate();
        ll m = (l + r) / 2;
        return new Node(
            modify(v->l, l, m, tl, min(tr, m), op),
            modify(v->r, m + 1, r, max(tl, m + 1), tr, op)
        );
    }
    T get(Node *v, ll l, ll r, ll tl, ll tr)
    {
        if (tl > tr)
            return T();
        if (tl == l && tr == r)
            return v->val;
        v->propegate();
        ll m = (l + r) / 2;
        return merge(
            get(v->l, l, m, tl, min(tr, m)),
            get(v->r, m + 1, r, max(m + 1, tl), tr)
        );
    }
    void modify(ll l, ll r, Op op)
    {
        history.pb(modify(history.back(), 0, n - 1, l, r, op)); 
    }
    T get(ll l, ll r){ return get(history.back(), 0, n - 1, l, r); }
    T get(ll l, ll r, ll h){ return get(history[h], 0, n - 1, l, r); }
};
