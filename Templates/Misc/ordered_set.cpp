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

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
// find_by_order(index), ordrer_of_key(value)
template<class T = ll, class MT = null_type, class CT = less<ll>>
class ordered_set: public tree<T, MT, CT, rb_tree_tag, tree_order_statistics_node_update>{};

ll getInv(vll v)
{
    ll res = 0;
    ordered_set<ll, null_type, greater<ll>> st;
    for (auto &e: v)
        res += st.order_of_key(e), st.insert(e);
    return res;
}

ll getRank(vll v)
{
    ll res = 1, cu = 1, fact = 1;
    ordered_set<ll, null_type, less<ll>> st;
    reverse(all(v));
    for (auto &e: v)
    {
        res += st.order_of_key(e) * fact, res %= MOD;
        st.insert(e);
        fact *= cu, fact %= MOD, cu++;
    }
    return res;
}

ll LIS(vll &v)
{
    vll res{INF};
    for (auto &e: v)
        if (e > res.back())
            res.pb(e);
        else
            *lower_bound(all(res), e) = e;
    return res.size();
}