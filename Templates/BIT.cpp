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

struct BIT
{
    vll bit;
    ll n;
    BIT(vll data): n(data.size())
    {
        bit.assign(n + 1, 0);
        build(data);
    }
    ll LSB(ll x){ return x & -x; }
    void build(vll &data)
    {   
        for (ll i{1}; i <= n; i++)
        {
            bit[i] += data[i - 1];
            if (i + LSB(i) <= n)
                bit[i + LSB(i)] += bit[i];
        }
    }
    ll get(ll r)
    {
        r++;
        ll res = 0;
        while (r > 0)
            res += bit[r], r -= LSB(r);
        return res;
    }
    ll get(ll l, ll r){ return get(r) - get(l - 1); }
    void modify(ll pos, ll val)
    {
        pos++;
        while (pos <= n)
            bit[pos] += val, pos += LSB(pos);
    }
    void set(ll pos, ll val){ modify(pos, val - get(pos, pos)); }
};

template<size_t K>
struct KD_BIT
{
    ll n;
    vector<KD_BIT<K - 1>> tree;
    KD_BIT(ll n): n(n), tree(n + 1, KD_BIT<K - 1>(n)){}
    ll LSB(ll x){ return x & -x; }
    ll get(vll coords)
    {
        ll pos = coords[0] + 1, res = 0;
        coords.erase(coords.begin());
        for (ll i{pos}; i > 0; i -= LSB(i))
            res += tree[i].get(coords);
        
        return res;
    }
    ll get(vll coords1, vll coords2, ll cnt = 0)
    {
        ll res = 0;
        for (ll mask{}; mask < (1 << K); mask++)
        {
            vll cur;
            for (ll i{}; i < K; i++)
            {
                if (mask & (1 << i))
                    cur.pb(coords2[i]);
                else    
                    cur.pb(coords1[i] - 1);
            }

            res += get(cur) * ((__builtin_popcountll(mask) & 1) ? 1 : -1);
        }
        if (!(K & 1))
            res *= -1;
        
        return res;
    }
    void modify(vll coords, ll val)
    {
        ll pos = coords[0] + 1;
        coords.erase(coords.begin());
        for (ll i{pos}; i <= n; i += LSB(i))
            tree[i].modify(coords, val);
    }
    void set(vll coords, ll val){ modify(coords, val - get(coords, coords)); }
};

template<>
struct KD_BIT<1>
{
    ll n;
    vector<ll> bit;
    KD_BIT(ll n): n(n), bit(n + 1){}
    ll LSB(ll x){ return x & -x; }
    ll get(vll coords)
    {
        ll res = 0;
        for (ll i{coords[0] + 1}; i > 0; i -= LSB(i))
            res += bit[i];
        return res;
    }
    ll get(vll coords1, vll coords2){ return get(coords2) - get({coords1[0]}); }
    void modify(vll coords, ll val)
    {
        for (ll i{coords[0] + 1}; i <= n; i += LSB(i))
            bit[i] += val;
    }
    void set(vll coords, ll val){ modify(coords, val - get(coords, coords)); }
};

struct BIT2D
{
    vvll bit;
    ll n, m;
    BIT2D(ll n, ll m): n(n), m(m)
    {
        bit.assign(n + 1, vll(m + 1));
    }
    ll LSB(ll x){ return x & -x; }
    ll get(ll x, ll y)
    {
        x++, y++;
        ll res = 0;
        for (ll i{x}; i > 0; i -= LSB(i))
            for (ll j{y}; j > 0; j -= LSB(j))
                res += bit[i][j];
        return res;
    }
    ll get(ll x1, ll y1, ll x2, ll y2)
    {
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
    void modify(ll x, ll y, ll val)
    {
        x++, y++;
        for (ll i{x}; i <= n; i += LSB(i))
            for (ll j{y}; j <= m; j += LSB(j))
                bit[i][j] += val;
    }
    void set(ll x, ll y, ll val) { modify(x, y, val - get(x, y, x, y)); }
};

struct BIT3D
{
    vvvll bit;
    ll n, m, l;
    BIT3D(ll n, ll m, ll l): n(n), m(m), l(l)
    {
        bit.assign(n + 1, vvll(m + 1, vll(l + 1)));
    }
    ll LSB(ll x){ return x & -x; }
    ll get(ll x, ll y, ll z)
    {
        x++, y++, z++;
        ll res = 0;
        for (ll i{x}; i > 0; i -= LSB(i))
            for (ll j{y}; j > 0; j -= LSB(j))
                for (ll k{z}; k > 0; k -= LSB(k))
                    res += bit[i][j][k];
        return res;
    }
    ll get(ll x1, ll y1, ll z1, ll x2, ll y2, ll z2)
    {
        return get(x2, y2, z2) 
        - get(x1 - 1, y2, z2) 
        - get(x2, y1 - 1, z2) 
        - get(x2, y2, z1 - 1) 
        + get(x1 - 1, y1 - 1, z2) 
        + get(x1 - 1, y2, z1 - 1)
        + get(x2, y1 - 1, z1 - 1)
        - get(x1 - 1, y1 - 1, z1 - 1);
    }
    void modify(ll x, ll y, ll z, ll val)
    {
        x++, y++, z++;
        for (ll i{x}; i <= n; i += LSB(i))
            for (ll j{y}; j <= m; j += LSB(j))
                for (ll k{z}; k <= l; k += LSB(k))
                    bit[i][j][k] += val;
    }
    void set(ll x, ll y, ll z, ll val) { modify(x, y, z, val - get(x, y, z, x, y, z)); }
};