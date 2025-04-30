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

template<class T, class F>
struct SQRTDecomp
{
    ll n, len;
    F merge;
    vector<T> seg, data;
    SQRTDecomp(vector<T> data)
    : data(data), n(data.size())
    {
        len = cei(sqrt(n));
        seg.resize(len);
        for (ll i{}; i < n; i++)
            seg[i / len] = merge(seg[i / len], data[i]);
    }
    T get(ll l, ll r)
    {
        T res = T();
        for (ll i{l}; i <= r;)
        {
            if (i % len == 0 && i + len - 1 <= r)
                res = merge(res, seg[i / len]), i += len;
            else
                res = merge(res, data[i]). i++;
        }
        return res;
    }
    void set(ll pos, T val)
    {
        data[pos] = val;
        ll block = pos / len;
        seg[block] = T();
        for (ll i{}; i < min(len, n); i++)
            seg[block] = merge(seg[block], data[block * len + i]);
    }
};

// how many elements are greater than or equal to x in [l, r];
template<class T>
struct SQRTDecompBS
{
    ll n, len;
    vector<T> data;
    vector<vector<T>> seg;
    SQRTDecomp(vector<T> data)
    : data(data), n(data.size())
    {
        len = cei(sqrt(n));
        seg.resize(len);
        for (ll i{}; i < n; i++)
            seg[i / len].pb(data[i]);
        
        for (auto &v: seg)
            sort(all(v));
    }
    ll get(ll block, ll val)
    {
        return seg[block].end() - lower_bound(all(seg[block]), val);
    }
    ll get(ll l, ll r, ll val)
    {
        ll res = 0;
        for (ll i{l}; l <= r;)
        {
            if (i % len == 0 && i + len - 1 <= r)
                res += get(i / len, val), i += len;
            else
                res += data[i] >= val, i++;
        }
    }
    void set(ll pos, ll val)
    {
        data[pos] = val;
        ll block = pos / len;
        seg[block].clear();
        for (ll i{}; i < len && i < n; i++)
            seg[block].pb(data[block * len + i]);
        sort(all(seg[block]));
    }
};

const ll blockSize;
struct Query
{
    ll l, r, idx;
    bool operator<(Query &other)
    {
        if (l / blockSize != other.l / blockSize)
            return l / blockSize < other.l / blockSize;
        if (l / blockSize & 1)
            return r < other.r;
        return r > other.r;
    }
};

struct Mo
{
    mll mp;
    spll st;
    vll data;
    vll res;
    vector<Query> queries;
    Mo(vll &data, vector<Query> &queries)
    : data(data), queries(queries), res(queries.size())
    {
        sort(all(queries));
        ll cuL = 0, cuR = -1;
        for (auto &e: queries)
        {
            while (cuL > e.l)
                add(--cuL);
            while (cuR < e.r)
                add(++cuR);
            while (cuL < e.l)
                remove(cuL++);
            while (cuR > e.r)
                remove(cuR--);
            
            res[e.idx] = get();
        }
    }
    void update(ll val, ll diff)
    {
        st.erase({val, mp[val]});
        mp[val] += diff;
        st.insert({val, mp[val]});
    }
    void add(ll idx)
    {
        update(data[idx], 1);
    }
    void remove(ll idx)
    {
        update(data[idx], -1);
    }
    ll get()
    {
        return st.rbegin()->second;
    }
};