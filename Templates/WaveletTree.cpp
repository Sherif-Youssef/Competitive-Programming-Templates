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

struct WaveletTree
{
    typedef vll::iterator it;
    struct Node
    {
        ll l, r;
        vll pre;
        Node() = default;
        Node(vll b, ll l, ll r): pre(b), l(l), r(r)
        {
            for (ll i{1}; i < pre.size(); i++)
                pre[i] += pre[i - 1];
        }
        ll get(ll l, ll r){ return pre[r] - pre[l - 1]; }
        ll get(ll r){ return (r < 0 ? 0 : pre[r]); }
    };
    vector<Node> nodes;
    ll lb, rb, root;
    WaveletTree(vll &data)
    {
        lb = *min_element(all(data));
        rb = *max_element(all(data));
        root = build(all(data), lb, rb);
    }
    ll newNode(vll b, ll l, ll r){ nodes.pb(Node(b, l, r)); return nodes.size() - 1; }
    ll build(it start, it end, ll l, ll r)
    {
        if (start == end || l == r)
            return -1;
        ll m = (l + r) / 2;
        vll b{0};
        for (it i = start; i != end; i++)
            b.pb(*i <= m);
        it pivot = stable_partition(start, end, [&](ll x){ return x <= m; });
        return newNode(b, build(start, pivot, l, m), build(pivot, end, m + 1, r));
    }
    ll getKth(ll v, ll l, ll r, ll tl, ll tr, ll k)
    {
        if (l == r)
            return l;
        ll m = (l + r) / 2, left = nodes[v].get(tl, tr);
        ll ntl = nodes[v].get(tl - 1), ntr = nodes[v].get(tr);
        if (k <= left)
            return getKth(nodes[v].l, l, m, ntl + 1, ntr, k);
        return getKth(nodes[v].r, m + 1, r, tl - ntl, tr - ntr, k - left);
    }
    // every thing is one based.
    ll getKth(ll l, ll r, ll k){ return getKth(root, lb, rb, l, r, k); }
};