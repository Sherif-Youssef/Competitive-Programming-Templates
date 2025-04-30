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

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18, PMOD = 1e9 + 6, PPMOD = 5e8 + 6;

ll fastPow(ll x, ll p, ll m = 1e9 + 7)
{
    if (p == 0)
        return 1;
    ll res = fastPow(x, p / 2, m);
    res = res * res % m;
    if (p % 2 == 1)
        res = res * x % m;
    return res;
}

vll sieve(ll n)
{
    vll prime(n, 1);
    for (ll i{2}; i < n; i++)
        if (prime[i])
            for (ll j{i * i}; j < n; j += i)
                prime[j] = 0;
    return prime;
}

vll spfSieve(ll n)
{
    vll spf(n);
    for (ll i{2}; i < n; i++)
        spf[i] = i;
    for (ll i{2}; i < n; i++)
        if (spf[i] == i)
            for (ll j{i * i}; j < n; j += i)
                if (spf[j] == j)
                    spf[j] = i;
    return spf;
}

vpll factorize(ll n, vll &spf)
{
    mll mp;
    while (n > 1)
        mp[spf[n]]++, n /= spf[n];
    return vpll(all(mp));
}

vpll factorize(ll n)
{
    mll mp;
    for (ll i{2}; i * i <= n; i++)
        while (n % i == 0)
            mp[i]++, n /= i;
    if (n > 1)
        mp[n]++;
    return vpll(all(mp));
}

vll getDivisors(vpll factors)
{
    vll divisors;
    function<void(ll, ll)> getDivs = [&factors, &divisors, &getDivs](ll i, ll curDiv){
        if (i == factors.size())
        {
            divisors.pb(curDiv);
            return;
        }
        for (ll j{}, cu{1}; j <= factors[i].second; j++, cu *= factors[i].first)
            getDivs(i + 1, curDiv * cu);
    };
    getDivs(0, 1);
    return divisors;
}

vll getDivisors(ll n)
{
    vll divs;
    for (ll i{1}; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            divs.pb(i);
            if (i * i < n)
                divs.pb(n / i);
        }
    }
    return divs;
}

ll phi(vpll factors)
{
    ll res{1};
    for (each e: factors)
        res *= fastPow(e.first, e.second) - fastPow(e.first, e.second - 1);
    return res;
}

ll geoSeries(ll x, ll n)
{
    return (((fastPow(x, n + 1) - 1 + MOD) % MOD) * fastPow(x - 1, PMOD - 1)) % MOD;
}

ll numOfDivs(vpll primes, ll m = MOD)
{
    ll ans{1};
    for (each e: primes)
        ans *= (e.second + 1), ans %= m;
    return ans;
}

ll sumOfDivs(vpll primes, ll m = MOD)
{
    ll ans{1};
    for (each e: primes)
        ans *= geoSeries(e.first, e.second), ans %= m;
    return ans;
}

ll proOfDivs(vpll primes)
{
    auto sum = [](ll n){
        return n * (n + 1) / 2;
    };
    ll ans{1}, total{numOfDivs(primes, PMOD)};
    for (each e: primes)
    {
        ll exp = ((sum(e.second) % PMOD) * ((total * fastPow(e.second + 1, PPMOD - 1, PMOD)) % PMOD)) % PMOD;
        ans *= fastPow(e.first, exp), ans %= MOD;
    }
    return ans;
}

ll inverseMod(ll n, ll m)
{
    return fastPow(n, phi(factorize(m)) - 1) % MOD;
}