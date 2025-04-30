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

struct Hash
{
    ll n, MOD;
    vll hash, revHash, powInv;
    Hash() = default;
    Hash(string s, ll p = 31, ll MOD = 1e9 + 7, char dil = 'a')
    : n(s.size()), MOD(MOD)
    {
        powInv = hash = revHash = vll(n + 1);
        for (ll i{}, curP{1}; i < n; i++, curP = curP * p % MOD)
        {
            hash[i + 1] = (hash[i] + (s[i] - dil + 1) * curP % MOD) % MOD;
            revHash[i + 1] = (revHash[i] + (s[n - i - 1] - dil + 1) * curP % MOD) % MOD;
        }
        powInv[n] = fastPow(fastPow(p, n), MOD - 2);
        for (ll i{n - 1}; i >= 0; i--)
            powInv[i] = p * powInv[i + 1] % MOD;
    }
    ll fastPow(ll x, ll p)
    {
        ll res = 1;
        for (; p > 0; p >>= 1, x = x * x % MOD)
             if (p & 1)
                res = res * x % MOD;
        return res;
    }
    ll comp(){ return hash[n]; }
    ll range(ll l, ll r, bool rev = 0)
    {
        if (l > r)
            return 0;
        l++, r++;
        vll &h = (rev ? revHash : hash);
        return (h[r] - h[l - 1] + MOD) * powInv[l - 1] % MOD;
    }
    bool isPal(ll l, ll r)
    {
        ll revL = n - r + 1, revR = n - l + 1;
        return range(l, r) == range(revL, revR, 1);
    }
};

struct DoubleHash
{
    Hash h1, h2;
    DoubleHash() = default;
    DoubleHash(string s, ll p1 = 53, ll p2 = 61, ll mod1 = 1e9 + 9, ll mod2 = 998244353)
    : h1(s, p1, mod1), h2(s, p2, mod2){}
    pll comp(){ return {h1.comp(), h2.comp()}; }
    pll range(ll a, ll b, bool rev = 0){ return {h1.range(a, b, rev), h2.range(a, b, rev)}; } 
    bool isPal(ll a, ll b){ return h1.isPal(a, b) && h2.isPal(a, b); }
};