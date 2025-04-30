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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// find_by_order(index), ordrer_of_key(value)
template<class T = ll, class MT = null_type, class CT = less<ll>>
class ordered_set: public tree<T, MT, CT, rb_tree_tag, tree_order_statistics_node_update>{};

#include <ext/rope>
using namespace __gnu_cxx;

mt19937 rng((uint32_t) chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution dist;
ll genRand(){ return dist(rng); }
ll genRand(ll l, ll r){ return dist(rng) % (r - l + 1) + l; }

vpll genTree(ll n)
{
    vpll edges;
    for (ll i{2}; i <= n; i++)
        edges.pb({genRand(1, i - 1), i});
    return edges;
}