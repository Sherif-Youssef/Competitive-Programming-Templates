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

vll prefixFn(string s)
{
    ll n = s.size();
    vll pi(n);
    for (ll i{1}; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        j += (s[i] == s[j]);
        pi[i] = j;
    }
    return pi;
}

vvll buildAutomaton(string s)
{
    ll n = s.size();
    vvll aut(n, vll(26));
    vll pi = prefixFn(s);
    for (ll i{}; i < n; i++)
    {
        for (ll c{}; c < 26; c++)
        {
            if (i == 0 || c + 'a' == s[i])
                aut[i][c] = i + (c + 'a' == s[i]);
            else    
                aut[i][c] = aut[pi[i - 1]][c];
        }
    }
    return aut;
}

vll zFn(string s) 
{
    ll n = s.size();
    vll z(n);
    ll l{}, r{};
    for(ll i{1}; i < n; i++) 
    {
        if(i < r) 
            z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) 
            z[i]++;
        if(i + z[i] > r) 
            l = i, r = i + z[i];
    }
    return z;
}

struct Manacher
{
    vll d;
    Manacher(string s){ build(s); }
    ll getOdd(ll i){ return d[2 * i + 1] / 2 - 1; }
    ll getEven(ll i){ return d[2 * (i + 1)] / 2; }
    void build(string s)
    {
        string tmp = "#";
        for (auto &c: s)
            tmp.pb(c), tmp.pb('#');
        s = tmp;

        ll n = s.size(), l = 0, r = 1;
        s = '^' + s + '$';
        d.assign(n + 2, 0);
        for (ll i{1}; i <= n; i++)
        {
            d[i] = max(min(r - i, d[l + (r - i)]), 0ll);
            while (s[i - d[i]] == s[i + d[i]])
                d[i]++;
            if (i + d[i] > r)
                l = i - d[i], r = i + d[i];
        }
        d.assign(d.begin() + 1, d.begin() + n);
    }
};