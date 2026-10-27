#include <bits/stdc++.h>
using namespace std;

#define forr(i,a,b) for(int i = int(a); i < int(b); i++)
#define forn(i,n) forr(i,0,n)
#define pb push_back

struct Tree {
    vector<Tree> children;
};

struct EdgeSet {
    vector<pair<int, int>> edges;
};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

Tree gen_tree(int n) {
    assert(n > 0);
    if (n == 1) return {};

    Tree tree;

    n --; // remove root

    int k = 1;
    for (int i = 1; i < n; ++i) {
        // cut with probability 2/(n-1)
        if (rng() % (n-1) < 2) {
            tree.children.pb(gen_tree(k));
            k = 1;
        } else {
            k++;
        }
    }
    tree.children.pb(gen_tree(k));

    return tree;
}

Tree permuted(Tree tree) {
    shuffle(tree.children.begin(), tree.children.end(), rng);
    for (auto& child : tree.children) {
        child = permuted(move(child));
    }
    return tree;
}

EdgeSet to_edge_set(Tree const& tree) {

    EdgeSet edges;
    int idx = 0;

    auto dfs = [&](auto&& dfs, Tree const& u) -> int {
        int u_idx = idx++;
        for (Tree const& v : u.children) {
            int v_idx = dfs(dfs, v);
            edges.edges.pb({u_idx, v_idx});
        }
        return u_idx;
    };
    dfs(dfs, tree);

    return edges;
}

EdgeSet permuted(EdgeSet edges, bool preserve_root) {
    int n = edges.edges.size() + 1;
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(preserve_root ? next(perm.begin()) : perm.begin(), perm.end(), rng);
    for (auto& edge : edges.edges) {
        edge = {perm[edge.first], perm[edge.second]};
    }
    for (auto& edge : edges.edges) {
        if (rng() % 2) {
            swap(edge.first, edge.second);
        }
    }
    shuffle(edges.edges.begin(), edges.edges.end(), rng);
    return edges;
}

int main() {
    int n; cin >> n;
    int mode; cin >> mode;


    if (mode == 1) { // print two isomorphic rooted trees

        Tree tree = gen_tree(n);
        EdgeSet edges = to_edge_set(tree);

        cout << n << "\n";

        edges = permuted(move(edges), true);
        for (auto [u, v] : edges.edges)
            cout << u + 1 << " " << v + 1 << "\n";

        edges = permuted(move(edges), true);
        for (auto [u, v] : edges.edges)
            cout << u + 1 << " " << v + 1 << "\n";
    }

    if (mode == 2) { // print two random trees (unlikely to be isomorphic)

        Tree tree1 = gen_tree(n);
        EdgeSet edges1 = to_edge_set(tree1);
        edges1 = permuted(move(edges1), false);

        Tree tree2 = gen_tree(n);
        EdgeSet edges2 = to_edge_set(tree2);
        edges2 = permuted(move(edges2), false);

        cout << n << "\n";

        for (auto [u, v] : edges1.edges)
            cout << u + 1 << " " << v + 1 << "\n";

        for (auto [u, v] : edges2.edges)
            cout << u + 1 << " " << v + 1 << "\n";
    }

}