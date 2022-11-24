//    OniGirichan
//    CP algorithms
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

using cd = complex<double>;
const double PI = acos(-1);

void FFT(vector<cd> &a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; ++j) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) for (auto & x : a) x /= n;
}

vector <ll> MULTIPLY(vector <int> const & a, vector <int> const & b) {
    vector <cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < (int)a.size() + (int)b.size()) n <<= 1;
    fa.resize(n); fb.resize(n);

    FFT(fa, false); FFT(fb, false);
    for (int i = 0; i < n; ++i) fa[i] *= fb[i]; // MOD if need

    FFT(fa, true);

    vector <ll> result(n);
    for (int i = 0; i < n; ++i) result[i] = round(fa[i].real());

    return result;
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);

    int test = 1; //cin >> test;
    while(test--);

    vector <int> fx = {1, 1, 1}, gx = {1, 3, 1};
//    fx = 1 + x + x^2    gx = 1 + 3x + x^2

    vector <ll> ans = MULTIPLY(fx, gx);
    for (auto & t : ans) cout << t << " ";
//    1 + 4x + 5x^2 + 4x^3 + x^4

    return 0;
}
