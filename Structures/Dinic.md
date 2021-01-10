* Dinic's algorithm

``` C++
#define INF 123456789
template <typename T>
struct edge {
    int end;
    T capacity;
    T flow;
};

template <typename T>
struct Dinic {
    int graphSize;
    int edgesNum;
    vector<vector<int>> graph; // stores indices to edges
    vector <edge<T>> allEdges;
    vector <bool> blacklisted;
    int sink, source;

    Dinic(int source, int sink, int n) : sink(sink - 1), source(source - 1), graphSize(n) {
        graph.resize(n, vector<int>());
        blacklisted.resize(n);
        edgesNum = 0;
    }

    void addNewEdge(int a, int b, T capacity) {
        a--; b--;
        graph[a].push_back(edgesNum);
        graph[b].push_back(edgesNum + 1);
        allEdges.push_back({b, capacity, 0});
        allEdges.push_back({a, 0, 0});
        edgesNum += 2;
    }

    vector<int> prepareLevels() {
        queue <int> q; q.push(source);
        vector <int> levels(graphSize, -1); levels[source] = 0;
        while (!q.empty()) {
            int w = q.front();
            q.pop();
            for (const auto &p : graph[w]) {
                const auto &sas = allEdges[p];
                if (sas.capacity > 0 && levels[sas.end] == -1) {
                    levels[sas.end] = levels[w] + 1;
                    q.push(sas.end);
                }
            }
        }
        return levels;
    }

    void updateFlow(int edgeIndex, T pushedWater) {
        allEdges[edgeIndex].capacity -= pushedWater;
        allEdges[edgeIndex].flow += pushedWater;
        allEdges[edgeIndex ^ 1].capacity += pushedWater;
        allEdges[edgeIndex ^ 1].flow -= pushedWater;
    }

    // Returns volume of pushed water if augmentation path does exist.
    // Returns 0 otherwise.
    T findAugmentationPath(int v, T pushedWater, const vector<int> &levels) {
        if (v == sink) {
            return pushedWater;
        }
        for (const auto &p : graph[v]) {
            auto sas = allEdges[p];
            // Found possible edge.
            if (sas.capacity > 0 && levels[sas.end] > levels[v] && !blacklisted[sas.end]) {
                T pushingResult = findAugmentationPath(sas.end, min(pushedWater, sas.capacity), levels);
                if (pushingResult == 0) {
                    // Blacklisting so I don't visit this vertex anymore.
                    blacklisted[sas.end] = true;
                    // I'm trying to check if any other adjacent vector will create augmentation path.
                    continue;
                } else {
                    // Found augmentation path, updating edges.
                    updateFlow(p, pushingResult);
                    return pushingResult;
                }
            }
        }
        // I haven't found any augmentation path, so I return 0.
        return 0;
    }

    T findMaximumFlow() {
        bool foundAugmentationPath = true;
        while (foundAugmentationPath) {
            auto levels = prepareLevels();
            foundAugmentationPath = false;
            fill(blacklisted.begin(), blacklisted.end(), false);
            while (findAugmentationPath(source, INF, levels)) {
                foundAugmentationPath = true;
            }
        }
        T result = 0;
        for (auto c : graph[source]) {
            result += allEdges[c].flow;
        }
        return result;
    }

};
```