#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); i++)
#define forn(i,n) forr(i,0,n)
#define pb push_back

int const maxn = 200100;
vector<vector<int>> g1;
vector<vector<int>> g2;

using Forest = uint64_t;

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

Forest make_empty() { return 0; }
Forest sum(Forest a, Forest b) { return a + b; }

map<Forest, Forest> children_to_tree;
map<Forest, Forest> tree_to_children;
Forest add_root(Forest children) {
    if (children_to_tree.count(children)) {
        return children_to_tree[children];
    }
    Forest tree = Forest(rng());
    children_to_tree[children] = tree;
    tree_to_children[tree] = children;
    return tree;
}

Forest to_forest(vector<vector<int>>& g, int u, int p) {

    Forest child_set = make_empty();
    for (int v : g[u]) if (v != p) {
        child_set = sum(child_set, to_forest(g, v, u));
    }

    return add_root(child_set);
}

int main() {
    // int t; cin >> t; while(t--) { children_to_tree.clear(); tree_to_children.clear(); g1.clear(); g2.clear();

    int n; cin >> n;
    g1.resize(n);
    g2.resize(n);

    forn(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        g1[u].pb(v);
        g1[v].pb(u);
    }

    forn(i, n-1) {
        int u, v; cin >> u >> v;
        u--; v--;
        g2[u].pb(v);
        g2[v].pb(u);
    }

    Forest tree1 = to_forest(g1, 0, -1);
    Forest tree2 = to_forest(g2, 0, -1);

    if (tree1 == tree2) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    // }
}