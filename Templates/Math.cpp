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

ll sum(ll n){ return n * (n + 1) / 2; }
ll sumo(ll n){ return  n * n; }
ll sume(ll n){ return n * (n + 1); }
ll sum2(ll n){ return n * (n + 1) * (2 * n + 1) / 6; }
ll sum2o(ll n){ return n * (2 * n + 1) * (2 * n - 1) / 3; }
ll sum2e(ll n){ return 2 * n * (n + 1) * (2 * n + 1) / 3; }

ll xorSum(ll n)
{
    switch (n % 4)
    {
        case 0: 
            return n;
        case 1:
            return 1;
        case 2:
            return n + 1;
        default:
            return 0;
    }
}

ll xorSum(ll l, ll r){ return xorSum(r) ^ xorSum(l - 1); }

ll nim(vll v)
{
    sll st(all(v));
    v.assign(all(st));
    for (ll last{}, i{}; i < v.size(); last = v[i++])
        if (v[i] - last > 1)
            return i;
    return v.size() - 1;
}

ll getMEX(vll v)
{
    v.pb(-1), v.pb(1e18);
    sort(all(v));
    for (ll i{1};; i++)
        if (v[i] - v[i - 1] > 1)
            return v[i - 1] + 1;
}

void euclid(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
        x = 1, y = 0;
    else
        euclid(b, a % b, x, y), tie(x, y) = make_tuple(y, x - y * (a / b));
}

struct LDE
{
    ll a, b, c, g;
    LDE(ll a, ll b, ll c): a(a), b(b), c(c), g(__gcd(a, b)){}
    bool hasSol(){ return c % g == 0; }
    pll solve(ll a, ll b)
    {
        if (b == 0)
            return pll(1, 0);
        ll x, y;
        tie(x, y) = solve(b, a % b);
        return pll(y, x - y * (a / b));
    }
    pll solve()
    {
        ll x, y;
        tie(x, y) = solve(abs(a), abs(b));
        if (a < 0)
            x *= -1;
        if (b < 0)
            y *= -1;
        x *= c / g, y *= c / g;
        return pll(x, y);
    }
    pll smallestPos()
    {
        ll x, y;
        tie(x, y) = solve();
        ll cy = a / g, cx = b / g;
        if (x < 0)
        {
            ll co = abs(x) / cx;
            if (abs(x) % cx)
                co++;
            x += co * cx, y -= co * cy;
        }
        if (y < 0)
        {
            ll co = abs(y) / cy;
            if (abs(y) % cy)
                co++;
            x -= co * cx, y += co * cy;
        }
        ll cof = (a > b ? y / cy : -x / cx);
        x += cof * cx, y -= cof * cy;
        return pll(x, y);
    }
};


const ll MOD = 1e9 + 7;

ll modPro(ll a, ll b){ ll res = a * b; return (res >= MOD ? res % MOD : res); }
ll modSum(ll a, ll b){ ll res = a + b; return (res >= MOD ? res - MOD : res); }

template<class T>
struct Matrix
{
    ll n, m;
    vector<vector<T>> mat;
    Matrix(ll n = 0, ll m = 0)
    : n(n), m(m), mat(n, vector<T>(m)){}
    Matrix(vector<vector<T>> mat)
    : mat(mat), n(mat.size()), m(mat[0].size()){}
    static Matrix unit(ll n)
    {
        Matrix mat(n, n);
        for (ll i{}; i < n; i++)
            mat[i][i] = 1;
        return mat;
    }
    Matrix operator*=(Matrix oth)
    {
        vector<vector<T>> res(n, vector<T>(oth.m));
        for (ll i{}; i < n; i++)
            for (ll j{}; j < oth.m; j++)
                for (ll k{}; k < m; k++)
                    res[i][j] = (res[i][j] + mat[i][k] * oth.mat[k][j]) % MOD;
        mat = res;
        return *this;
    };
};

template<class T>
Matrix<T> fastPow(Matrix<T> &mat, ll p)
{
    if (p == 0)
        return Matrix<T>::unit(mat.n);
    Matrix<T> res = fastPow(mat, p / 2);
    res *= res;
    if (p & 1)
        res *= mat;
    return res;
}

struct XorBasis
{
    vll basis;
    ll MX, sz;
    XorBasis(ll MX = 63): MX(MX), basis(MX), sz(0){};
    bool insert(ll x)
    {
        for (ll i{MX - 1}; i >= 0; i--)
        {
            if ((x & (1ll << i)) == 0)
                continue;
            if (!basis[i])
            {
                basis[i] = x;
                sz++;
                return true;
            }
            x ^= basis[i];
        }
        return false;
    }
    // one based
    ll getKth(ll k)
    {
        ll res = 0, tot = (1ll << sz);
        for (ll i{MX - 1}; i >= 0; i--)
        {
            if (!basis[i])
                continue;
            tot /= 2;
            if (k > tot && (res & (1ll << i)) || k <= tot && !(res & (1ll << i)))
                res ^= basis[i];
            if (k > tot)
                k -= tot;
        }
        return res;
    }
    bool check(ll x)
    {
        ll cur = 0;
        for (ll i{MX - 1}; i >= 0; i--)
            if ((x & (1ll << i)) != (cur & (1ll << i)))
                cur ^= basis[i];
        return cur == x;
    }
};



ll maxHistogramArea(vll v)
{
    vll st;
    v.pb(0);
    ll res = 0, n = v.size();
    for (ll i{}; i < n; i++)
    {
        while (!st.empty() && v[st.back()] > v[i])
        {
            ll cu = st.back();
            st.popb();
            res = max(res, v[cu] * (st.empty() ? i : i - st.back() - 1));
        }
        st.pb(i);
    }
    return res;
}

string infixToPostfix(string s)
{
    map<char, ll> prec{
        {'*', 0}, {'/', 0}, {'+', 1}, {'-', 1} , {'(', 1e18} 
    };
    string sol, st;
    for (auto &c: s)
    {
        if (isdigit(c))
            sol.pb(c);
        else if (c == '(')
            st.pb(c);
        else if (c == ')')
        {
            while (st.back() != '(')
                sol.pb(st.back()), st.popb();
            st.popb();
        }
        else
        {
            while (!st.empty() && prec[st.back()] <= prec[c])
                sol.pb(st.back()), st.popb();
            st.pb(c);
        }
    }
    while (!st.empty())
        sol.pb(st.back()), st.popb();
    return sol;
}

template<class T = ll>
struct RunningMedian
{
    priority_queue<T> l;
    priority_queue<T, vector<T>, greater<T>> r;
    void insert(T e)
    {
        (l.empty() || e < l.top() ? l.push(e) : r.push(e));
        ll ls = l.size(), rs = r.size();
        if (ls - rs > 1)
            r.push(l.top()), l.pop();
        else if (rs - ls > 1)
            l.push(r.top()), r.pop();
    }
    T get()
    {
        T med;
        if (l.size() == r.size())
            med = (l.top() + r.top()) / 2;
        else 
            med = (l.size() > r.size() ? l.top() : r.top());
        return med;
    }
};


ld dis(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
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