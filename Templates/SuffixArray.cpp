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
typedef vector<string> vs;

struct SuffixArray
{
    int n;
    string s;
    vector<int> suf, pos, lcp, lg;
    vector<vector<int>> pre;
    SuffixArray() = default;
    SuffixArray(string s): s(s){ build(); }
    pair<int, int> getPair(int i, int k){ return {pos[i], pos[(i + k) % n]}; }
    void build()
    {
        s.pb(0), n = s.size();
        suf.resize(n), pos.assign(all(s)), lcp.resize(n);
        vector<int> freq(max(n, 256)), sorted(n), nPos(n);
        iota(all(suf), 0);
 
        for (int k{}, cls{256}; k < n; k <<= 1, k = max(k, 1))
        {
            if (k)
                for (auto &e: suf)
                    e = (e - k + n) % n;
                
            fill(all(freq), 0);
            for (auto &e: pos)
                freq[e]++;
            for (int i{1}; i < cls; i++)
                freq[i] += freq[i - 1];
            for (int i{n - 1}; i >= 0; i--)
                sorted[--freq[pos[suf[i]]]] = suf[i];
            swap(suf, sorted);
 
            nPos[suf[0]] = 0;
            cls = 1;
            for (int i{1}; i < n; i++)
            {
                nPos[suf[i]] = nPos[suf[i - 1]];
                if (getPair(suf[i], k) != getPair(suf[i - 1], k))
                    nPos[suf[i]]++, cls++;
            }
            swap(pos, nPos);
            if (cls == n)
                break;
        }
        for (int i{}, k{}; i < n - 1; i++)
        {
            int j = suf[pos[i] - 1];
            while (s[i + k] == s[j + k])
                k++;
            lcp[pos[i]] = k;
            k = max(k - 1, 0);
        }
    }
    void print()
    {
        for (int i{}, pi{suf[i]}; i < n; i++, pi = suf[i])
            cout << lcp[i] << " " << pi << " " << s.substr(pi, n - pi) << endl;
    }
    void buildLCP()
    {
        lg.resize(n + 1);
        for (int i{2}; i <= n; i++)
            lg[i] = lg[i / 2] + 1;
        pre.assign(n, vector<int>(lg[n] + 1));

        for (int i{}; i < n; i++)
            pre[i][0] = lcp[i];
        for (int p{1}; p <= lg[n]; p++)
            for (int i{}; i + (1 << p) - 1 < n; i++)
                pre[i][p] = min(pre[i][p - 1], pre[i + (1 << (p - 1))][p - 1]);
    }
    int query(int i, int j)
    {
        if (i == j)
            return n - i - 1;
        i = pos[i], j = pos[j];
        if (i > j)
            swap(i, j);
        i++;
        int p = lg[j - i + 1];
        return min(pre[i][p], pre[j - (1 << p) + 1][p]);
    }
    pll search(string t)
    {
        ll m = t.size(), l = 0, r = n - 1, lb, ub;
        auto sub = [this, &m](ll i){ 
            return s.substr(suf[i], min(m, ll(n - suf[i]))); 
        };
        while (l < r)
        {
            ll mid = r - (r - l) / 2;
            (sub(mid) < t ? l = mid : r = mid - 1);
        }
        lb = l + 1, l = 0, r = n - 1;
        while (l < r)
        {
            ll mid = (l + r) / 2;
            (sub(mid) > t ? r = mid : l = mid + 1);
        }
        ub = (sub(l) > t ? l - 1 : n - 1);
        return pll(lb, ub);
    }
};

int LCS(string a, string b)
{
    SuffixArray arr(a + char(1) + b);
    int n = a.size(), m = b.size(), res = 0;
    for (int i{1}; i < arr.n; i++)
        if ((arr.suf[i] < n) != (arr.suf[i - 1] < n))
            res = max(res, arr.lcp[i]);
    return res;
}

int LCS(vs &v, int minOcc)
{
    ll m = v.size();
    string t;
    int res = 0;
    vector<int> lens;
    for (int i{}; i < m; i++)
        t += v[i], t.pb(i), lens.pb(t.size());
    
    SuffixArray arr(t);
    arr.buildLCP();
    int n = arr.n;
    vector<int> &suf(arr.suf), cls(n), freq(m);
    for (int i{1}; i < n; i++)
        cls[i] = upper_bound(all(lens), suf[i]) - lens.begin();
    
    for (int l{1}, r{1}, cnt{}; r < n; r++)
    {
        freq[cls[r]]++;
        cnt += (freq[cls[r]] == 1);
        while (freq[cls[l]] > 1 || cnt > minOcc)
        {
            freq[cls[l]]--;
            cnt -= (freq[cls[l]] == 1);
            l++;
        }
        if (cnt >= minOcc)
            res = max(res, arr.query(suf[l], suf[r]));
    }
    return res;
}