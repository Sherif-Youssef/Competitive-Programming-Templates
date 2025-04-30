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
#define Outsiders freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define FastAsFBoy ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;

template<class T>
istream &operator>>(istream &is, vector<T> &v)
{
    for (each e: v)
        is >> e;
    return is;
}

int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};
char di[] = {'U', 'R', 'D', 'L'};

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18, PMOD = 1e9 + 6, PPMOD = 5e8 + 6;

ll fastPow(ll x, ll p, ll m = MOD)
{
    if (!p)
        return 1;
    ll res = fastPow(x, p / 2, m);
    res = (res * res) % m;
    if (p % 2)
        res = (res * x) % m;
    return res;
}

ll sum(ll n)
{
    return n * (n + 1) / 2;
}

ll mult(ll a, ll b)
{
    return (a % MOD) * (b % MOD) % MOD;
}

ll add(ll a, ll b)
{
    return (a % MOD + b % MOD) % MOD;
}

ll subtract(ll a, ll b)
{
    return (a % MOD + b % MOD + MOD) % MOD;
}

ll geoSeries(ll x, ll n)
{
    return (((fastPow(x, n + 1) - 1 + MOD) % MOD) * fastPow(x - 1, PMOD - 1)) % MOD;
}

vector<pll> primes;
vector<ll> divs;
void getDivs(ll idx = 0, ll div = 1)
{
    if (idx == primes.size())
        divs.pb(div);
    else
        for (ll i{}; i <= primes[idx].second; i++)
            getDivs(idx + 1, div), div *= primes[idx].first;
}

ll numOfDivs(vector<pll>&primes, ll m = MOD)
{
    ll ans{1};
    for (each e: primes)
        ans *= (e.second + 1), ans %= m;
    return ans;
}

ll sumOfDivs(vector<pll>&primes)
{
    ll ans{1};
    for (each e: primes)
        ans *= geoSeries(e.first, e.second), ans %= MOD;
    return ans;
}

ll proOfDivs(vector<pll>&primes)
{
    ll ans{1}, total{numOfDivs(primes, PMOD)};
    for (each e: primes)
    {
        ll exp = ((sum(e.second) % PMOD) * ((total * fastPow(e.second + 1, PPMOD - 1, PMOD)) % PMOD)) % PMOD;
        ans *= fastPow(e.first, exp), ans %= MOD;
    }
    return ans;
}


void sieve(vector<ll> &prime, ll MX)
{
    for (ll i{2}; i * i < MX; i++)
        if (prime[i])
            for (ll j{i * i}; j < MX; j += i) 
                prime[j] = 0;
}

void factorize(ll n, map<ll, ll> &mp)
{
    for (ll i{2}; i * i <= n; i++)
        while (n % i == 0)
            mp[i]++, n /= i;
    if (n > 1)
        mp[n]++;
}

const ll MX = 1e7 + 1;
vector<ll> spf(MX);

void spfSieve()
{
    for (ll i {1}; i < MX; i++)
        spf[i] = i;
    for (ll i {2}; i * i < MX; i++)
        if (spf[i] == i)
            for (ll j{i * i}; j < MX; j += i)
                if (spf[j] == j)
                    spf[j] = i;
}

void fastFactorize(ll n, map<ll, ll> &mp)
{
    while (n > 1)
        mp[spf[n]]++, n /= spf[n];
}

ll gcd(ll a, ll b)
{
    if (b == 0) 
        return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b)
{
    return (a * b) / gcd(a, b);
}

ll totient(ll n)
{
    ll ans{1};
    map<ll, ll> factors;
    factorize(n, factors);
    for (each e: factors)
    {
        ans *= fastPow(e.first, e.second) - fastPow(e.first, e.second - 1);
    }
    return ans;
}

ll inverse_MOD(ll n, ll m)
{
    return fastPow(n, totient(m) - 1) % m;
}

// Combinatorics class
class Combinatorics
{
    public:
        const ll MX, MOD;
        vector<ll> fact, modInv;
        Combinatorics(ll MX = 1e6 + 1, ll MOD = 1e9 + 7): MX(MX), MOD(MOD)
        {
            fact = modInv = vector<ll>(MX);
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
        ll allCombs(vector<ll> v)
        {
            ll n{};
            for (each e: v)
                n += e;
            ll ans{1};
            for (each e: v)
                ans = ans * nCr(n, e) % MOD, n -= e;
            return ans;
        }
        ll gridTravel(vector<ll> &v1, vector<ll> &v2)
        {
            vector<ll> v;
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

// DSU class

struct Edge
{
    ll a, b, w;
};

class DSU
{
    vector<ll> p, r, nxt;
    ll sz;
    public:
        ll comps;
        DSU(ll n) : sz(n)
        {
            p = r = nxt = vector<ll>(sz + 1);
            for (ll i{1}; i <= sz; i++)
                p[i] = nxt[i] = i;
            comps = n;
        }
        ll get(ll a)
        {
            return p[a] = (p[a] == a ? a : get(p[a]));
        }
        bool unite(ll a, ll b)
        {
            a = get(a), b = get(b);
            if (a == b)
                return false;
            if (r[a] == r[b]) 
                r[a]++;
            if (r[a] > r[b]) 
                p[b] = a;
            else 
                p[a] = b;
            comps--;
            return true;
        }

        ll get_r(ll a)
        {
            return nxt[a] = (nxt[a] == a ? a : get_r(nxt[a]));
        }
        void unite_r(ll a, ll b)
        {
            for (ll d{get_r(a)}; d < b; d = get_r(d + 1))
            {
                unite(d, b);
                nxt[d] = b;
            }
        }
};


// Bipartite graph

class BiPGraph
{
    vector<ll> p, r, dis;
    ll sz;
    public:
        BiPGraph(ll n) : sz(n)
        {
            p = r = dis = vector<ll>(sz + 1);
            for (ll i{1}; i <= sz; i++)
                p[i] = i;
        }
        pll get(ll a)
        {
            if (a != p[a])
            {
                pll val = get(p[a]);
                p[a] = val.first, dis[a] += val.second, dis[a] %= 2;
            }
            return {p[a], dis[a]};
        }
        bool unite(ll a, ll b)
        {
            pll valA = get(a), valB = get(b);
            if (valA.first == valB.first)
                return dis[a] != dis[b];
            if (r[valA.first] == r[valA.first]) 
                r[valA.first]++;
            else if (r[valA.first] < r[valA.first]) 
                swap(a, b);
            p[valB.first] = valA.first;
            dis[valB.first] = valB.second + valA.second + 1, dis[valB.first] %= 2;
            return true;
        }
};

class SpreadedStack
{
    class Stack
    {
        vector<ll> data, g;
        public:
            Stack()
            {
                g.pb(0);
            }
            ll gcd()
            {
                return g.back();
            }
            void push(ll e)
            {
                data.pb(e);
                g.pb(__gcd(gcd(), e));
            }
            ll pop()
            {
                ll tmp = data.back();
                data.pop_back(), g.pop_back();
                return tmp;
            }
            bool empty()
            {
                return data.empty();
            }
    };
    Stack l, r;
    public:
        ll gcd()
        {
            return __gcd(l.gcd(), r.gcd());
        }
        bool extraGood()
        {
            if (l.empty() && r.empty())
                return false;
            ll tmp = pop();
            if (gcd() == 1)
                return true;
            l.push(tmp);
            return false;
        }
        void push(ll e)
        {
            r.push(e);
        }
        ll pop()
        {
            if (l.empty())
                while (!r.empty())
                    l.push(r.pop());
            return l.pop();
        }
};

struct Stack
{
    vll ori, mn;
    Stack(){ mn.pb(INF); }
    void push(ll x){ ori.pb(x), mn.pb(min(mn.back(), x)); }
    ll poll(){ return mn.back(); }
    ll pop(){ ll tmp = ori.back(); ori.popb(), mn.popb(); return tmp; }
    bool empty(){ return ori.empty(); }
};

struct SpreadedStack
{
    Stack l, r;
    void push(ll x){ l.push(x); }
    ll poll(){ return min(l.poll(), r.poll()); }
    void pop()
    {
        if (r.empty())
            while (!l.empty())
                r.push(l.pop());
        r.pop();
    }
};

class Hash
{
    // all one based
    public:
        ll n, MOD;
        vector<ll> hash, revHash, pows;
        Hash() = default;
        Hash(string s, ll p = 31, ll MOD = 1e9 + 7, char dil = 'a'): n(s.size()), MOD(MOD)
        {
            string rev = s;
            reverse(all(rev));
            hash = revHash = pows = vector<ll>(n + 1);
            pows[0] = 1;
            for (ll i{1}; i <= n; i++)
                pows[i] = (pows[i - 1] * p) % MOD;
            for (ll i{}; i < n; i++)
                hash[i + 1] = (hash[i] + ((s[i] - dil + 1) * pows[i]) % MOD) % MOD;
            for (ll i{}; i < n; i++)
                revHash[i + 1] = (revHash[i] + ((rev[i] - dil + 1) * pows[i]) % MOD) % MOD;
        }
        ll comp()
        {
            return hash[n];
        }
        ll operator[](ll i)
        {
            return hash[i];
        }
        ll jumpWithPow(ll h, ll r)
        {
            return h * pows[n - r] % MOD;
        }
        ll range(ll a, ll b)
        {
            if (a > b)
                return 0;
            return jumpWithPow((hash[b] - hash[a - 1] + MOD) % MOD, b);
        }
        ll revRange(ll a, ll b)
        {
            if (a > b)
                return 0;
            return jumpWithPow((revHash[b] - revHash[a - 1] + MOD) % MOD, b);
        }
        bool isPal(ll a, ll b)
        {
            ll x = n - b + 1, y = n - a + 1;
            return range(a, b) == revRange(x, y);
        }
};

class DoubleHash
{
    ll p1, p2, mod1, mod2;
    Hash h1, h2;
    DoubleHash() = default;
    DoubleHash(string s, ll p1 = 53, ll p2 = 61, ll mod1 = 1e9 + 9, ll mod2 = 998244353)
    : p1(p1), p2(p2), mod1(mod1), mod2(mod2)
    {
        h1 = Hash(s, p1, mod1);
        h2 = Hash(s, p2, mod2);
    }
    pll comp()
    {
        return {h1.comp(), h2.comp()};
    }
    pll operator[](ll i)
    {
        return {h1[i], h2[i]};
    }
    pll range(ll a, ll b)
    {
        return {h1.range(a, b), h2.range(a, b)};
    }
    bool isPal(ll a, ll b)
    {
        return h1.isPal(a, b) && h2.isPal(a, b);
    }
};

vector<ll> KMP(string s)
{
    ll n = s.size();
    vector<ll> pi(n);
    for (ll i{1}; i < n; i++)
    {
        ll j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<ll> zFn(string s) 
{
    ll n = s.size();
    vector<ll> z(n);
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

vector<ll> treeCenters(vector<vector<ll>> &adj)
{
    deque<ll> dq;
    ll n = adj.size() - 1;
    vector<ll> deg(n + 1);
    for (ll i{1}; i <= n; i++)
    {
        deg[i] = adj[i].size();
        if (deg[i] == 1 || deg[i] == 0)
            dq.pb(i), deg[i] = 0;
    }
    ll ctr = dq.size();
    while (ctr < n)
    {
        for (ll sz = dq.size(), i{}; i < sz; i++)
        {
            ll u = dq.front();
            dq.popf();
            for (each v: adj[u])
            {
                deg[v]--;
                if (deg[v] == 1)
                    dq.pb(v), ctr++;
            }
        }
    }
    return vector<ll>(all(dq));
}

string encodeTree(vector<vector<ll>> &adj, ll u, ll p = 0)
{
    vector<string> children;
    string cu{'('};
    for (each v: adj[u])
        if (v != p)
            children.pb(encodeTree(adj, v, u));
    sort(all(children));
    for (each e: children)
        cu.append(e);
    cu.pb(')');
    return cu;
}

ll encodeTreeHash(vector<vector<ll>> &adj, ll u, ll p = 0, ll dep = 53)
{
    ll hash{1};
    for (each v: adj[u])
        if (v != p)
            hash *= encodeTreeHash(adj, v, u, dep * 53 % MOD), hash %= MOD;
 
    return (hash + 1) * dep % MOD;
}

class SparseTable
{
    vector<vector<ll>> pre;
    vector<ll> lg;
    ll n, def;
    ll (*func)(ll, ll);
    public:
        SparseTable(vector<ll> data, ll (*func)(ll, ll), ll def = 0): n(data.size()), func(func), def(def)
        {
            lg = vector<ll>(n + 1);
            for (ll i{2}; i <= n; i++)
                lg[i] = lg[i / 2] + 1;

            pre = vector<vector<ll>>(n, vector<ll>(lg[n] + 1));
            for (ll i{}; i < n; i++)
                pre[i][0] = data[i];

            for (ll p{1}; p <= lg[n]; p++)
                for (ll i{}; i + (1 << p) - 1 < n; i++)
                    pre[i][p] = func(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
        }
        ll rangeOL(ll a, ll b)
        {
            ll p = lg[b - a + 1];
            return func(pre[a][p], pre[b - (1 << p) + 1][p]);
        }
        ll range(ll a, ll b)
        {
            ll ans{def};
            for (ll p{lg[n]}; p >= 0; p--)
            {
                if ((1 << p) <= b - a + 1)
                    ans = func(ans, pre[a][p]), a += (1 << p);
            }
            return ans;
        }
};

template<class T, class B = ll>
class SegTree
{
    void propegate(ll v, ll l, ll r)
    {
        if (l == r)
            return;
        seg[v * 2] = mergeValues(seg[v * 2], seg[v]);
    }
    void build(vector<B> &data, ll v, ll l, ll r)
    {
        if (l == r)
        {
            seg[v] = defaultVal(data[l], l);
        }
        else
        {
            ll m = (l + r) / 2;
            build(data, v * 2, l, m);
            build(data, v * 2 + 1, m + 1, r);
            seg[v] = mergeValues(seg[v * 2], seg[v * 2 + 1]);
        }
    }
    void set(ll v, ll pos, B val, ll l, ll r)
    {
        if (l == pos && r == pos)
        {
            seg[v] = defaultVal(val, pos);
        }
        else
        {
            ll m = (l + r) / 2;
            if (pos <= m)
                set(v * 2, pos, val, l, m);
            else
                set(v * 2 + 1, pos, val, m + 1, r);
            seg[v] = mergeValues(seg[v * 2], seg[v * 2 + 1]);
        }
    }
    T get(ll v, ll tarL, ll tarR, ll l, ll r)
    {
        if (tarL > tarR)
            return defaultVal(B(), -1);
        if (tarL == l && tarR == r)
            return seg[v];
        ll m = (l + r) / 2;
        return mergeValues(get(v * 2, tarL, min(m, tarR), l, m), get(v * 2 + 1, max(m + 1, tarL), tarR, m + 1, r));
    }
    ll getKth(ll v, ll k, ll l, ll r)
    {
        if (l == r)
            return (k == 1 ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= k)
            return getKth(v * 2, k, l, m);
        return getKth(v * 2 + 1, k - seg[v * 2], m + 1, r);
    }
    ll getLB(ll v, ll x, ll tarL, ll tarR, ll l, ll r)
    {
        if (tarL > tarR)
            return -1;
        if (l == r)
            return (seg[v] >= x && tarR >= r ? l : -1);
        ll m = (l + r) / 2;
        if (seg[v * 2] >= x)
        {
            ll idx = getLB(v * 2, x, tarL, min(m, tarR), l, m);
            if (~idx)
                return idx;
        }
        return getLB(v * 2 + 1, x, max(m + 1, tarL), tarR, m + 1, r);
    }
    vector<T> seg;
    vector<B> ops;
    ll n;
    B NO_OP;
    T (*mergeValues)(T, T);
    T (*defaultVal)(B, ll);
    public:
        SegTree(vector<B> data, T (*mergeValues)(T, T), T (*defaultVal)(B, ll)): n(data.size()), mergeValues(mergeValues), defaultVal(defaultVal), NO_OP(NO_OP)
        {
            seg = vector<T>(n * 4);
            build(data, 1, 0, n - 1);
        }
        void set(ll pos, ll val)
        {
            set(1, pos, val, 0, n - 1);
        }
        T get(ll l, ll r)
        {
            return get(1, l, r, 0, n - 1);
        }
        ll getKth(ll k)
        {
            return getKth(1, k, 0, n - 1);
        }
        ll getLB(ll x, ll l, ll r)
        {
            return getLB(1, x, l, r, 0, n - 1);
        }
};

struct Seg
{
    ll sum, pre, suf, maxSum;
};

Seg defaultVal(ll val, ll pos)
{
    return Seg{val, val, val, val};
}

Seg mergeValues(Seg a, Seg b)
{
    return Seg{
        a.sum + b.sum,
        max(a.pre, a.sum + b.pre),
        max(b.suf, b.sum + a.suf),
        max({a.maxSum, b.maxSum, a.suf + b.pre})
    };
}

ld mag(pll v)
{
    return sqrt(v.first * v.first + v.second * v.second);
}

ll dot(pll x, pll y)
{
    return x.first * y.first + x.second * y.second;
}

ld cross(pll x, pll y)
{
    return mag(x) * mag(y);
}

ld angleBetVectors(pll x, pll y)
{
    return (acos(dot(x, y) / cross(x, y))) / (2 * acos(0)) * 180;
}

int main()
{
    FastAsFBoy
    ll t;
    cin >> t;
    while (t--)
    {
        
    }
}
