#include <iostream>
#include <vector>
#include <memory>

using namespace std; 

struct EdgeNode {
    int y;                                    // Вершина, к которой ведёт ребро
    int weight;                               // Вес ребра (если есть)
    shared_ptr<EdgeNode> next = nullptr;      // Указатель на следующее ребро в списке

    EdgeNode(int y, int weight = 0, shared_ptr<EdgeNode> next = nullptr)
        : y(y), weight(weight), next(next) {
    }
};


struct Graph {
    static const int MAXV = 1000;             // Максимальное количество вершин
    vector<shared_ptr<EdgeNode>> edges;       // Списки смежности
    vector<int> degree;                       // Степень каждой вершины
    int nvertices;                            // Количество вершин
    int nedges;                               // Количество рёбер
    bool directed;                            // Граф ориентированный?

    Graph(int maxVertices = MAXV, bool directed = false)
        : nvertices(0), nedges(0), directed(directed) {
        edges.resize(maxVertices + 1, nullptr);
        degree.resize(maxVertices + 1, 0);
    }
};

void initializeGraph(Graph& g, bool directed) {
    g.nvertices = 0;
    g.nedges = 0;
    g.directed = directed;

    for (int i = 0; i <= g.MAXV; ++i) {
        g.degree[i] = 0;
        g.edges[i] = nullptr;
    }
}


void addEdge(Graph& g, int x, int y, int weight = 0) {
    auto newEdge = make_shared<EdgeNode>(y, weight, g.edges[x]);
    g.edges[x] = newEdge;
    g.degree[x]++;

    if (!g.directed) {
        auto reverseEdge = make_shared<EdgeNode>(x, weight, g.edges[y]);
        g.edges[y] = reverseEdge;
        g.degree[y]++;
    }
    else {
        g.nedges++;
    }
}



void printGraph(const Graph& g) {
    for (int i = 1; i <= g.nvertices; ++i) {
        cout << "Вершина " << i << ":";
        auto current = g.edges[i];
        while (current != nullptr) {
            cout << " -> " << current->y << " (вес " << current->weight << ")";
            current = current->next;
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Graph g;

    
    initializeGraph(g, false); //неориентированный граф

    cout << "Введите количество вершин и рёбер: ";
    cin >> g.nvertices >> g.nedges;

    cout << "Введите рёбра (формат: вершина1 вершина2 [вес]):\n";
    for (int i = 0; i < g.nedges; ++i) {
        int x, y, weight = 0;
        cin >> x >> y;

    
        if (g.directed) {
            cin >> weight;
        }

        addEdge(g, x, y, weight);
    }

    cout << "\nСписок смежности графа:\n";
    printGraph(g);
    system("pause");


    return 0;
}
