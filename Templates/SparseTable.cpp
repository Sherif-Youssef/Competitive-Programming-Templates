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

template<class T, class F>
struct SparseTable
{
    vector<vector<T>> pre;
    vll lg;
    ll n;
    F merge;

    SparseTable() = default;
    SparseTable(vector<T> data): n(data.size())
    {
        lg.resize(n + 1);
        for (ll i{2}; i <= n; i++)
            lg[i] = lg[i / 2] + 1;

        pre.assign(n, vector<T>(lg[n] + 1));
        for (ll i{}; i < n; i++)
            pre[i][0] = data[i];

        for (ll p{1}; p <= lg[n]; p++)
            for (ll i{}; i + (1 << p) - 1 < n; i++)
                pre[i][p] = merge(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
    }
    T get(ll l, ll r)
    {
        T res;
        bool start = 1;
        for (ll rem{r - l + 1}, i{l}, p{lg[rem]}; rem > 0; i += (1 << p), rem -= (1 << p), p = lg[rem])
            res = (start ? pre[i][p] : merge(res, pre[i][p])), start = 0;
        return res;
    }
    T getOL(ll l, ll r)
    {
        ll p = lg[r - l + 1];
        return merge(pre[l][p], pre[r - (1 << p) + 1][p]);
    }
};