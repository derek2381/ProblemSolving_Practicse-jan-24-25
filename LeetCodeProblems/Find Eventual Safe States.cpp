// Problem Link
// https://leetcode.com/problems/find-eventual-safe-states/description/


 // Source Code
 class Solution {
public:
    vector<bool> isSafe;

    bool checkSafeState(vector<vector<int>>& graph, vector<int>& visited, int i) {
        // Mark the current node as visiting (in-progress)
        visited[i] = 1;

        for (int u : graph[i]) {
            if (visited[u] == 0) { // If the node is unvisited
                if (!checkSafeState(graph, visited, u)) {
                    return isSafe[i] = false; // If a cycle is found
                }
            } else if (visited[u] == 1) { // If the node is in-progress (cycle detected)
                return isSafe[i] = false;
            } else if (visited[u] == 2) { // If the node is already determined safe
                if (!isSafe[u]) {
                    return isSafe[i] = false;
                }
            }
        }

        // Mark the current node as fully visited (safe)
        visited[i] = 2;
        return isSafe[i] = true;
    }

    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();
        isSafe = vector<bool>(n, false); // Initialize all nodes as unsafe
        vector<int> visited(n, 0); // 0: unvisited, 1: visiting, 2: visited

        for (int i = 0; i < n; i++) {
            if (visited[i] == 0) {
                checkSafeState(graph, visited, i);
            }
        }

        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (isSafe[i]) {
                res.push_back(i); // Add safe nodes to the result
            }
        }

        return res;
    }
};