# Dinic's algorithm

``` C++
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
    vector<vector<int>> graph;
    vector <edge<T>> allEdges;
    vector <bool> blacklisted;
    vector <int> ptr;
    int sink, source;
    T sourceCapacity;

    Dinic(int source, int sink, int n, T sourceCapacity) : 
            sink(sink - 1), 
            source(source - 1), 
            graphSize(n), 
            sourceCapacity(sourceCapacity) {
        graph.resize(n, vector<int>());
        blacklisted.resize(n);
        ptr.resize(n);
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
        for (auto& i = ptr[v]; i < graph[v].size(); i++) {
            auto sas = allEdges[graph[v][i]];
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
                    updateFlow(graph[v][i], pushingResult);
                    return pushingResult;
                }
            }
        }
        // I haven't found any augmentation path, so I return 0.
        return 0;
    }

    T findMaximumFlow() {
        bool foundAugmentationPath = true;
        T sumOfFlows = 0;
        while (foundAugmentationPath && sourceCapacity) {
            auto levels = prepareLevels();
            foundAugmentationPath = false;
            fill(blacklisted.begin(), blacklisted.end(), false);
            fill(ptr.begin(), ptr.end(), 0);
            while (T r = findAugmentationPath(source, sourceCapacity, levels)) {
                foundAugmentationPath = true;
                sourceCapacity -= r;
                sumOfFlows += r;
            }
        }
        return sumOfFlows;
    }
};
```

# Tasks

[Maximum flow](https://www.spoj.com/problems/FASTFLOW/)
