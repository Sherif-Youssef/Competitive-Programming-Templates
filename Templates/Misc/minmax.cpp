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


void FastAsFBoy()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #else
        // freopen("inputFileName.in", "r", stdin);
        // freopen("outputFileName.out", "w", stdout);
    #endif
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
}

template<class T>
istream &operator>>(istream &is, vector<T> &v)
{
    for (auto &e: v)
        is >> e;
    return is;
}

int dx[] = {-1, 0, 1, 0, -1, -1, 1, 1};
int dy[] = {0, 1, 0, -1, -1, 1, -1, 1};
char di[] = {'U', 'R', 'D', 'L'};

const ll N = 2e5 + 1, MX = 1e1, MOD = 1e9 + 7, INF = 1e18;

bool win(vs v)
{
    vs tv(4, string(4, '.'));
    for (ll i{}; i < 4; i++)
        for (ll j{}; j < 4; j++)
            tv[i][j] = v[j][i];
    for (ll i{}; i < 4; i++)
        if (
            set<char>(all(v[i])).size() == 1 && v[i][0] != '.'
            || set<char>(all(tv[i])).size() == 1 && tv[i][0] != '.'
        )
            return 1;
    set<char> diax, diay;
    for (ll i{}; i < 4; i++)
        diax.insert(v[i][i]), diay.insert(v[i][3 - i]);
    if (
        diax.size() == 1 && *diax.begin() != '.'
        || diay.size() == 1 && *diay.begin() != '.'
    )
        return 1;
    return 0;
}

bool draw(vs v)
{
    ll cnt{};
    for (auto &e: v)
        cnt += count(all(e), '.');
    return cnt == 0;
}

char getTurn(vs v)
{
    ll cntx{}, cnty{};
    for (ll i{}; i < 4; i++)
        for (ll j{}; j < 4; j++) 
            if (v[i][j] == 'x')
                cntx++;
            else if (v[i][j] == 'o')
                cnty++;
    return (cntx > cnty ? 'o' : 'x');
}

map<vs, ll> dp;
ll solve(vs v)
{
    if (win(v))
        return -1;
    if (draw(v))
        return 0;
    if (!dp.count(v))
    {
        ll &res = dp[v];
        char turn = getTurn(v);
        bool allWin = 1;
        for (ll i{}; i < 4; i++)
        {
            for (ll j{}; j < 4; j++)
            {
                if (v[i][j] != '.')
                    continue;
                v[i][j] = turn;
                ll next = solve(v);
                if (next != 1)
                    allWin = 0;
                if (next == -1)
                    res = 1;
                v[i][j] = '.';
            }
        }
        if (allWin)
            res = -1;
    }
    return dp[v];
}

int main()
{
    FastAsFBoy();
    char c;
    while (cin >> c)
    {
        if (c == '$')
            break;
        vs v(4);
        cin >> v;
        if (solve(v) != 1)
            cout << "#####";
        else
        {
            char turn = getTurn(v);
            pll move{-1, -1};
            for (ll i{}; i < 4 && !~move.first; i++)
            {
                for (ll j{}; j < 4 && !~move.first; j++)
                {
                    if (v[i][j] != '.')
                        continue;
                    v[i][j] = turn;
                    if (solve(v) == -1)
                        move = {i, j};
                    v[i][j] = '.';
                }
            }
            cout << "(" << move.first << "," << move.second << ")";
        }
        cout << endl;
    }
}