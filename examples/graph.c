// Adjacency matrix undirected unweighted graph ADT implementation.
/*
 * REFERENCES:
 * https://youtu.be/9C2cpQZVRBA?si=ca7YjdCGVjwVHIwt 
 * https://youtu.be/PMMc4VsIacU?si=3qvuwU6ffdMvdTd1
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define VERTEX_AMOUNT 10

typedef struct sVertex {
    char data;
    bool visited;
} Vertex;

typedef struct sGraph {
    int size;
    int capacity;

    Vertex *vertexList;
    bool *adjMatrix;
} Graph;

Graph *InitGraph(){
    Graph *graph = malloc(sizeof(*graph));
    if(graph == NULL){
        fprintf(stderr, "ERROR: Couldn't allocate graph.\n");
        exit(1);
    }
    Vertex *vertexList = malloc(VERTEX_AMOUNT * sizeof(*vertexList));
    if(vertexList == NULL){
        fprintf(stderr, "ERROR: Couldn't allocate vertex list.\n");
        exit(2);
    }
    bool *adjMatrix = malloc(VERTEX_AMOUNT * VERTEX_AMOUNT * sizeof(*adjMatrix));
    if(adjMatrix == NULL){
        fprintf(stderr, "ERROR: Couldn't allocate adjacency matrix.\n");
        exit(3);
    }
    graph->size = 0;
    graph->capacity = VERTEX_AMOUNT;
    graph->vertexList = vertexList;
    graph->adjMatrix = adjMatrix;

    return graph;
}

void DeallocGraph(Graph *graph){
    free(graph->adjMatrix);
    free(graph->vertexList);
    free(graph);
}

void AddVertex(Graph *graph,char data){
    if(graph == NULL){
        fprintf(stdout, "Graph isn't initialized.\n");
        return;
    }
    if(graph->size == graph->capacity){
        fprintf(stdout, "Graph is full.\n");
        return;
    }
    graph->vertexList[graph->size].data = data;
    graph->vertexList[graph->size++].visited = false;
    return;
}

int FindVertexIndex(Graph *graph, char data){
    if(graph == NULL || graph->size == 0){
        fprintf(stdout, "Graph isn't initialized.\n");
        return -1;
    }
    for(int i = 0; i < graph->size; i++){
        if(graph->vertexList[i].data == data){
            return i;
        }
    }
    return -1;
}

void AddEdge(Graph *graph, char start, char end){
    if(graph == NULL || graph->size == 0){
        fprintf(stdout, "Graph isn't initialized.\n");
        return;
    }
    int startIndex = FindVertexIndex(graph, start);
    int endIndex = FindVertexIndex(graph, end);
    if(startIndex < 0 || endIndex < 0){
        fprintf(stdout, "Couldnt locate start or end index.\n");
        return;
    }
    graph->adjMatrix[graph->size * startIndex + endIndex] = true;
    graph->adjMatrix[graph->size * endIndex + startIndex] = true;
    return;
}

void DepthFirstSearch(Graph *graph, int vertexIndex){
    graph->vertexList[vertexIndex].visited = true;
    printf("%c ", graph->vertexList[vertexIndex].data);
    for(int i = 0; i < graph->size; i++){
        if(graph->adjMatrix[vertexIndex * graph->size + i] == 1 && graph->vertexList[i].visited == false){
            DepthFirstSearch(graph, i);
        }
    }
}

void pubDepthFirstSearch(Graph *graph, int rootVertexIndex){
    printf("\nDFS starting from \"%d:%c\":\n", rootVertexIndex, graph->vertexList[rootVertexIndex].data);
    DepthFirstSearch(graph, rootVertexIndex);
    printf("\n");
    for(int i = 0; i < graph->size; i++){
        graph->vertexList[i].visited = false;
    }
}

void PrintVertexList(Graph *graph){
    if(graph == NULL || graph->size == 0){
        fprintf(stdout, "Cant print empty graph\n");
        return;
    }
    for(int i = 0; i < graph->size; i++){
        printf("%d: %c\n", i, graph->vertexList[i].data);
    }
    return;
}

void PrintAdjMatrix(Graph *graph){
    if(graph == NULL || graph->size == 0){
        fprintf(stdout, "Cant print empty graph\n");
        return;
    }
    printf("    ");
    for(int i = 0; i < graph->size; i++){
        printf("%d ", i);
    }

    for(int i = 0; i < graph->size; i++){
        printf("\n");
        printf("%d [ ", i);
        for(int j = 0; j < graph->size; j++){
            printf("%d ", graph->adjMatrix[i * graph->size + j]);
        }
        printf("]");
    }
    printf("\n");
    return;
}

int main(void){
    Graph *graph = NULL;
    graph = InitGraph();

    AddVertex(graph, 'A');
    AddVertex(graph, 'B');
    AddVertex(graph, 'C');
    AddVertex(graph, 'D');
    AddVertex(graph, 'E');
    AddVertex(graph, 'F');
    AddVertex(graph, 'G');
    AddVertex(graph, 'H');

    AddEdge(graph, 'A', 'D');
    AddEdge(graph, 'A', 'C');
    AddEdge(graph, 'A', 'B');
    AddEdge(graph, 'C', 'G');
    AddEdge(graph, 'G', 'H');
    AddEdge(graph, 'H', 'D');
    AddEdge(graph, 'H', 'F');
    AddEdge(graph, 'H', 'E');
    AddEdge(graph, 'B', 'E');
    AddEdge(graph, 'B', 'F');

    PrintVertexList(graph);
    PrintAdjMatrix(graph);
    /*
     *  0: A
     *  1: B
     *  2: C
     *  3: D
     *  4: E
     *  5: F
     *  6: G
     *  7: H
     *
     *  0 1 2 3 4 5 6 7 
     *  0 [ 0 1 1 1 0 0 0 0 ]
     *  1 [ 1 0 0 0 1 1 0 0 ]
     *  2 [ 1 0 0 0 0 0 1 0 ]
     *  3 [ 1 0 0 0 0 0 0 1 ]
     *  4 [ 0 1 0 0 0 0 0 1 ]
     *  5 [ 0 1 0 0 0 0 0 1 ]
     *  6 [ 0 0 1 0 0 0 0 1 ]
     *  7 [ 0 0 0 1 1 1 1 0 ]
    */

    pubDepthFirstSearch(graph, 0);
    //DFS starting from "0:A":
    //A B E H D F G C 

    DeallocGraph(graph);
    return 0;
}
