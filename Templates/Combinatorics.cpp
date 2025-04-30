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
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<vvpll> vvvpll;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef map<ll, ll> mll;
typedef set<ll> sll;

struct Combinatorics
{
    const ll MX, MOD;
    vll fact, modInv;
    Combinatorics(ll MX = 1e6 + 1, ll MOD = 1e9 + 7): MX(MX), MOD(MOD)
    {
        fact = modInv = vll(MX);
        fact[0] = 1;
        for (ll i{1}; i < MX; i++)
            fact[i] = i * fact[i - 1], fact[i] %= MOD;
        modInv[MX - 1] = fastPow(fact[MX - 1], MOD - 2);
        for (ll i{MX - 2}; i >= 0; i--)
            modInv[i] = (i + 1) * modInv[i + 1] % MOD;
    }
    ll fastPow(ll x, ll p)
    {
        if (!p)
            return 1;
        ll res = fastPow(x, p / 2);
        res = (res * res) % MOD;
        if (p % 2)
            res = (res * x) % MOD;
        return res;
    }
    ll nPr(ll n, ll r)
    {
        if (r > n)
            return 0;
        return fact[n] * modInv[n - r] % MOD;
    }
    ll nCr(ll n, ll r)
    {
        return nPr(n, r) * modInv[r] % MOD;
    }
    ll nCRr(ll n, ll r)
    {
        return nCr(n + r - 1, r);
    }
    ll catalan(ll n)
    {
        return (nCr(2 * n, n) - nCr(2 * n, n - 1) + MOD) % MOD;
    }
    // ( != )
    ll ballot(ll n, ll m)
    {
        return (nCr(n + m, m) - nCr(n + m, m - 1) + MOD) % MOD;
    }
    // ( != ) && k * ( at the start
    ll ballot(ll n, ll m, ll k)
    {
        ll res = nCr(n + m, m);
        if (m > k)
            res = (res - nCr(n + m, m - k - 1) + MOD) % MOD;
        return res;
    }
    ll allCombs(vll v)
    {
        ll n{};
        for (auto &e: v)
            n += e;
        ll ans{1};
        for (auto &e: v)
            ans = ans * nCr(n, e) % MOD, n -= e;
        return ans;
    }
    ll gridTravel(vll &v1, vll &v2)
    {
        vll v;
        ll n{};
        for (ll i{}; i < v1.size(); i++)
        {
            if (v2[i] < v1[i])
                return 0;
            v.pb(v2[i] - v1[i]);
        }
        return allCombs(v);
    }
};