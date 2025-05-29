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


struct Line 
{
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};
 
struct DynamicConvexHull: multiset<Line, less<>> 
{
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LONG_LONG_MAX;
	ll div(ll a, ll b) 
    { 
        // floored division
		return a / b - ((a ^ b) < 0 && a % b); 
    }
	bool isect(iterator x, iterator y) 
    {
		if (y == end()) 
            return x->p = inf, 0;
		if (x->k == y->k) 
            x->p = x->m > y->m ? inf : -inf;
		else 
            x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll m, ll b) 
    {
		auto z = insert({m, b, 0}), y = z++, x = y;
		while (isect(y, z)) 
            z = erase(z);
		if (x != begin() && isect(--x, y)) 
            isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll get(ll x) 
    {
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

typedef complex<ll> point;
struct ConvexHull
{
    vector<point> hull, vecs;
    ConvexHull() = default;
    ll dot(point a, point b){ return (conj(a) * conj(b)).real(); }
    ll cross(point a, point b){ return (conj(a) * b).imag(); }
    void addLine(ll m, ll b)
    {
        point nw{m, b};
        while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) 
            hull.pop_back(), vecs.pop_back();
        if(!hull.empty())
            vecs.push_back(point(1i) * (nw - hull.back()));
        hull.push_back(nw);
    }
    ll get(ll x)
    {
        point query = {x, 1};
        auto it = lower_bound(all(vecs), query, [this](point a, point b) {
            return cross(a, b) > 0;
        });
        return dot(query, hull[it - vecs.begin()]);
    }
};
