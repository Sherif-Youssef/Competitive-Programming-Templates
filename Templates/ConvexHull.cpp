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