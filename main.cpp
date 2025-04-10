// PradoPageRank.cpp
// C++ Implementation of PageRank on Prado Museum Dataset

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

class PradoPageRank {
private:
    unordered_map<string, set<string>> tagToPictures;
    unordered_map<string, set<string>> graph;
    unordered_map<string, double> pagerankScores;
    string filePath;

public:
    PradoPageRank(const string& filePath) : filePath(filePath) {}

    void loadData(vector<pair<string, vector<string>>>& data) {
        ifstream file(filePath);
        string line;

        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        getline(file, line); // skip header

        while (getline(file, line)) {
            stringstream ss(line);
            string picture_id, tags;

            getline(ss, picture_id, ',');
            getline(ss, tags);

            vector<string> tagList;
            stringstream tagStream(tags);
            string tag;

            while (getline(tagStream, tag, ';')) {
                tagList.push_back(tag);
                tagToPictures[tag].insert(picture_id);
            }

            data.push_back({picture_id, tagList});
        }

        file.close();
        cout << "Loaded " << data.size() << " entries." << endl;
    }

    void buildGraph(const vector<pair<string, vector<string>>>& data, bool weighted = false) {
        graph.clear();

        if (weighted) {
            unordered_map<string, unordered_map<string, int>> weights;

            for (const auto& entry : data) {
                const string& pic_id = entry.first;
                const vector<string>& tags = entry.second;

                for (const auto& tag : tags) {
                    for (const auto& neighbor : tagToPictures[tag]) {
                        if (pic_id != neighbor) {
                            weights[pic_id][neighbor]++;
                        }
                    }
                }
            }

            for (const auto& node : weights) {
                const string& from = node.first;
                for (const auto& edge : node.second) {
                    graph[from].insert(edge.first);
                }
            }

        } else {
            for (const auto& tagEntry : tagToPictures) {
                const auto& pics = tagEntry.second;
                for (auto it1 = pics.begin(); it1 != pics.end(); ++it1) {
                    for (auto it2 = next(it1); it2 != pics.end(); ++it2) {
                        graph[*it1].insert(*it2);
                        graph[*it2].insert(*it1);
                    }
                }
            }
        }

        cout << "Graph built with " << graph.size() << " nodes." << endl;
    }

    void computePageRank(double damping = 0.85, int max_iter = 100, double tol = 1e-6) {
        int n = graph.size();
        if (n == 0) return;

        double init_val = 1.0 / n;
        unordered_map<string, double> prev_rank;

        for (const auto& node : graph) {
            pagerankScores[node.first] = init_val;
        }

        for (int iter = 0; iter < max_iter; ++iter) {
            prev_rank = pagerankScores;
            for (const auto& node : graph) {
                double rank_sum = 0.0;
                for (const auto& neighbor : graph) {
                    if (neighbor.second.count(node.first)) {
                        rank_sum += prev_rank[neighbor.first] / neighbor.second.size();
                    }
                }
                pagerankScores[node.first] = (1 - damping) / n + damping * rank_sum;
            }

            double diff = 0.0;
            for (const auto& pr : pagerankScores) {
                diff += abs(pr.second - prev_rank[pr.first]);
            }
            if (diff < tol) break;
        }

        cout << "PageRank computed." << endl;
    }

    void showTopResults(int top_k = 10) const {
        multimap<double, string, greater<>> sortedScores;
        for (const auto& item : pagerankScores) {
            sortedScores.insert({item.second, item.first});
        }

        cout << "Top " << top_k << " pictures by PageRank:\n";
        int count = 0;
        for (const auto& score : sortedScores) {
            cout << score.second << " => " << score.first << endl;
            if (++count >= top_k) break;
        }
    }
};

int main() {
    PradoPageRank pagerank("prado.csv");
    vector<pair<string, vector<string>>> data;

    pagerank.loadData(data);
    pagerank.buildGraph(data, false); // unweighted
    pagerank.computePageRank();
    pagerank.showTopResults();

    pagerank.buildGraph(data, true); // weighted
    pagerank.computePageRank();
    pagerank.showTopResults();

    return 0;
}
