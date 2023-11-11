#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int src, dest, weight;
} Edge;

typedef struct Graph {
    int V, E;
    Edge* edge;
} Graph;

Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    int xset = find(parent, x);
    int yset = find(parent, y);
    parent[xset] = yset;
}

int myComp(const void* a, const void* b) {
    Edge* a1 = (Edge*)a;
    Edge* b1 = (Edge*)b;
    return a1->weight - b1->weight;
}

void KruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;

    qsort(graph->edge, graph->E, sizeof(graph->edge[0]), myComp);

    int parent[V];

    for (int v = 0; v < V; ++v)
        parent[v] = v;

    printf("Edge Cost\n");
    int totalWeight = 0;

    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edge[i++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        if (x != y) {
            result[e++] = next_edge;
            Union(parent, x, y);
        }
    }

    for (i = 0; i < e; ++i) {
        if (result[i].src < result[i].dest) {
            printf("%d--%d %d\n", result[i].src, result[i].dest, result[i].weight);
        } else {
            printf("%d--%d %d\n", result[i].dest, result[i].src, result[i].weight);
        }
        totalWeight += result[i].weight;
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    Graph* graph = createGraph(V, E);

    for (int i = 0; i < E; i++) {
        scanf("%d %d %d", &graph->edge[i].src, &graph->edge[i].dest, &graph->edge[i].weight);
    }

    KruskalMST(graph);
    return 0;
}
