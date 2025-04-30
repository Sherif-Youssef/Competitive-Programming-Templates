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

struct AhoCorasick
{
    struct Node
    {
        const static size_t K = 26;
        ll p, link;
        char pCh;
        bool terminal;
        vll next, go;
        Node(ll p, char pCh)
        : p(p), link(-1), pCh(pCh), terminal(0), next(K, -1), go(K, -1){}
    };
    vector<Node> nodes;
    AhoCorasick(){ addNode(-1, '$'); }
    ll addNode(ll p, char pCh){ nodes.pb(Node(p, pCh)); return nodes.size() - 1; }
    void insert(string s)
    {
        ll u = 0;
        for (auto &c: s)
        {
            ll idx = c - 'a';
            if (nodes[u].next[idx] == -1)
                nodes[u].next[idx] = addNode(u, c);
            u = nodes[u].next[idx];
        }
        nodes[u].terminal = 1;
    }
    ll getLink(ll u)
    {
        Node &node = nodes[u];
        ll &tar = node.link;
        if (tar == -1)
        {
            if (u == 0 || node.p == 0)
                tar = 0;
            else
                tar = go(getLink(node.p), node.pCh);
        }
        return tar;
    }
    ll go(ll u, char c)
    {
        ll idx = c - 'a';
        Node &node = nodes[u];
        ll &tar = node.go[idx];
        if (tar == -1)
        {
            if (node.next[idx] != -1)
                tar = node.next[idx];
            else
                tar = (u == 0 ? 0 : go(getLink(u), c));
        }
        return tar;
    }
};

struct Trie
{
    struct Node
    {
        const static size_t K = 26;
        ll cnt, terminal;
        vll next;
        Node(): terminal(0), cnt(0), next(K, -1){}
    };
    vector<Node> nodes;
    Trie(){ addNode(); }
    ll addNode(){ nodes.pb(Node()); return nodes.size() - 1; }
    void modify(string s, ll diff = 1)
    {
        ll u = 0;
        nodes[u].cnt += diff;
        for (auto &c: s)
        {
            ll idx = c - 'a';
            if (nodes[u].next[idx] == -1)
                nodes[u].next[idx] = addNode();
            u = nodes[u].next[idx];
            nodes[u].cnt += diff;
        }
        nodes[u].terminal += diff;
    }
    ll count(string s)
    {
        ll u = 0;
        for (auto &c: s)
        {
            ll idx = c - 'a';
            if (nodes[u].next[idx] == -1 || nodes[u].cnt == 0)
                return 0;
            u = nodes[u].next[idx];
        }
        return nodes[u].terminal;
    }
};

struct BiTrie
{
    vvll nodes;
    vll cnt;
    ll MSB;
    BiTrie(ll MSB): MSB(MSB){ addNode(), modify(0, 1); }
    void addNode(){ nodes.pb(vll(2, -1)), cnt.pb(0); }
    void modify(ll val, ll diff)
    {
        ll idx = 0;
        cnt[0] += diff;
        for (ll i{MSB}; i >= 0; i--)
        {
            bool bit = (val >> i) & 1;
            if (nodes[idx][bit] == -1)
                addNode(), nodes[idx][bit] = cnt.size() - 1;
            idx = nodes[idx][bit];
            cnt[idx] += diff;
        }
    }
    bool exists(ll idx, bool bit)
    { 
        return ~nodes[idx][bit] && cnt[nodes[idx][bit]];
    }
    ll getXor(ll val, bool maxi = 1)
    {
        ll res = 0, idx = 0;
        for (ll i{MSB}; i >= 0; i--)
        {
            bool bit = (val >> i) & 1;
            if (!exists(idx, bit) || (maxi && exists(idx, !bit)))
                bit ^= 1, res ^= (1ll << i);
            idx = nodes[idx][bit];
        }
        return res;
    }
};