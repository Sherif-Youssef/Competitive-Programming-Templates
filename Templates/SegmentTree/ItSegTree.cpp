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
struct SegTree
{
    vector<T> seg;
    ll n;
    F merge;
    SegTree() = default;
    SegTree(vector<T> data): n(data.size())
    {
        seg.assign(n * 2, T());
        for (ll i{}; i < n; i++)
            seg[n + i] = data[i];
        for (ll i{n - 1}; i > 0; i--)
            seg[i] = merge(seg[i * 2], seg[i * 2 + 1]);
    }
    void set(ll pos, T val)
    {
        seg[pos += n] = val;
        while (pos /= 2)
            seg[pos] = merge(seg[pos * 2], seg[pos * 2 + 1]);
    }
    T get(ll l, ll r)
    {
        T resL = T(), resR = T();
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2)
        {
            if (l & 1)
                resL = merge(resL, seg[l++]);
            if (r & 1)
                resR = merge(seg[--r], resR);
        }
        return merge(resL, resR);
    }
};