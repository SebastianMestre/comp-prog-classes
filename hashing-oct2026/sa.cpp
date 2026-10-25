#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); ++i)
#define forn(i,n) forr(i,0,n)
#define all(x) begin(x),end(x)
#define sz(x) (int((x).size()))
#define dbg(x) cerr<<#x" = "<<(x)<<"\n";

using pii = pair<int,int>;

template<class It>
vector<int> compress(It l, It r) {
    vector v(l, r);
    sort(all(v));
    v.erase(unique(all(v)), end(v));

    vector<int> res;
    for (auto it = l; it != r; ++it) {
        res.push_back(distance(begin(v), lower_bound(all(v), *it)));
    }

    return res;
}

vector<int> suffix_array(string s) {

    int const n = sz(s);

    int l = 1;
    while (l < n) l *= 2;

    int const N = n-1+l;
    s.resize(N, '\0');

    // invariante: compressed representa strings de longitud l
    vector<int> compressed = compress(all(s));

    l = 1;

    while (l < n) {

        int n_ = N - l*2 + 1;

        vector<pii> items(n_);
        forn(i, n_) {
            items[i] = {compressed[i], compressed[i+l]};
        }

        compressed = compress(all(items));
        l *= 2;
    }


    vector<int> result(n);
    forn(i, n) {
        result[compressed[i]] = i;
    }

    return result;
}

int main() {

    string s;
    cin >> s;

    auto sa = suffix_array(s);
    int const n = sz(sa);

    forn(i, n) {
        cout << sa[i] << " \n"[i==n-1];
    }


}