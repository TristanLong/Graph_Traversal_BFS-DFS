#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

const int MAX = 20;

struct maTrix {
    int maTranKe[MAX][MAX];
    int soDinh;
};

void readFile(maTrix& mtk) {
    ifstream inFile("AdjacencyMatrix.txt");
    if (!inFile.is_open()) {
        cout << "\nKhong the mo tep";
        return;
    }

    inFile >> mtk.soDinh;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            inFile >> mtk.maTranKe[i][j];
        }
    }
    inFile.close();
}

void outputMaTrix(maTrix mtk) {
    cout << "\nMA TRAN KE: " << endl;
    for (int i = 0; i < mtk.soDinh; i++) {
        for (int j = 0; j < mtk.soDinh; j++) {
            cout << mtk.maTranKe[i][j] << "\t";
        }
        cout << endl;
    }
}

bool visited[MAX] = { false };

void BFS(int u, maTrix graph) {
    queue<int> hangDoi;
    hangDoi.push(u);
    visited[u] = true;

    while (!hangDoi.empty()) {
        int v = hangDoi.front();
        hangDoi.pop();
        cout << v << " ";

        for (int i = 0; i < graph.soDinh; ++i) {
            if (graph.maTranKe[v][i] != 0 && !visited[i]) {
                hangDoi.push(i);
                visited[i] = true;
            }
        }
    }
}

void DFS(int u, maTrix graph) {
    cout << u << " ";
    visited[u] = true;

    for (int i = 0; i < graph.soDinh; ++i) {
        if (graph.maTranKe[u][i] != 0 && !visited[i]) {
            DFS(i, graph);
        }
    }
}

int main() {
    maTrix graph;
    readFile(graph);
    outputMaTrix(graph);

    cout << "\nBFS Traversal: ";
    for (int i = 0; i < graph.soDinh; ++i) {
        if (!visited[i]) {
            BFS(i, graph);
        }
    }

    // Reset mảng visited ( mảng viếng thăm )
    for (int i = 0; i < MAX; i++) {
        visited[i] = false;
    }

    cout << "\nDFS Traversal: ";
    for (int i = 0; i < graph.soDinh; ++i) {
        if (!visited[i]) {
            DFS(i, graph);
        }
    }
}
