#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100
INT_MAX = 100000000;

int graph[MAX_VERTICES][MAX_VERTICES];
int parent[MAX_VERTICES];
int key[MAX_VERTICES];
bool inMST[MAX_VERTICES];

void initialize(int n) {
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        inMST[i] = false;
    }
}

void prim(int n, int start) {
    key[start] = 0;
    parent[start] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }
        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
}

int main() {
    int n, start;
    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);
    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);

    initialize(n);

    FILE *file = fopen("inUnAdjMat.dat", "r");
    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    printf("Input:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &graph[i][j]);
        }
    }
    fclose(file);

    prim(n, start - 1);

    printf("Output:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == parent[j] || j == parent[i]) {
                printf("%d ", graph[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    int totalWeight = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            totalWeight += graph[i][parent[i]];
        }
    }
    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);

    return 0;
}