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

struct BigInt
{
    string value;
    BigInt(): value("0"){}
    BigInt(string value): value(value){}
    BigInt(long long value): value(to_string(value)){}
    BigInt operator+=(BigInt other)
    {
        if (other.value.size() < value.size())
            swap(other.value, value);
        int carry{};
        value = string(other.value.size() - value.size(), '0')  + value;
        for (ll i = value.size() - 1; i >= 0; i--)
        {
            int sum = value[i] + other.value[i] - 2 * '0' + carry;
            carry = sum / 10;
            value[i] = sum % 10 + '0';
        }
        if (carry)
            value = '1' + value;
        return *this;
    }
    BigInt operator+(BigInt other)
    {

        BigInt tmp(*this);
        tmp += other;
        return tmp;
    }
    BigInt operator=(BigInt other)
    {
        this->value = other.value;
        return *this;
    }
};