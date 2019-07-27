using namespace std;

class DSU {
    public:
        DSU(vector<vector<int>>& edges) {
            _parent.assign(edges.size() + 1, 0);
            construct(edges);
        }

        ~DSU() {
            _parent.clear();
        }

        int construct(vector<vector<int>>& edges) {
            for (auto e : edges) {
                int v1 = e[0], v2 = e[1];
                // find the leader vertex
                while (parent[v1]) {
                    v1 = parent[v1];
                }
                while (parent[v2]) {
                    v2 = parent[v2];
                }
                parent[v1] = v2;
            }
        }

        bool same_comp(int u, int v) {
            return _parent[u] == _parent[v];
        }

    private:
        vector<int> _parent;

}
