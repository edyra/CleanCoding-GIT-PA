/*parcurgerge  graf cu DFS/BFS*/

//Imi cer scuze in avans
//of :(

#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int number_vertices;
    int *visited_nodes;
    struct Node **adjacency_lists;
} GRAPH;
/// utils

NODE *createNode(int value) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}

GRAPH *createGraph(int number_vertices) {
    int i;
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->number_vertices = number_vertices;
    graph->adjacency_lists = malloc(number_vertices * sizeof(NODE *));
    graph->visited_nodes = malloc(sizeof(int) * number_vertices);

    for (int i = 0; i < number_vertices; i++){
        graph->adjacency_lists[i] = NULL;
        graph->visited_nodes[i] = 0;
    }

    return graph;
}

void addEdge(GRAPH *graph, int source, int destination){
    NODE *new_node = createNode(destination);
    new_node->next = graph->adjacency_lists[source];
    graph->adjacency_lists[source] = new_node;

    new_node = createNode(source);
    new_node->next = graph->adjacency_lists[destination];
    graph->adjacency_lists[destination] = new_node;
}
void insertEdges(int nr_of_vertices, int nr_of_edges, GRAPH *graph){
    int source, destination, i;
    printf("adauga %d muchii (de la 0 la %d)\n", nr_of_edges, nr_of_vertices);
    for (i = 0; i < nr_of_edges; i++) {
        scanf("%d%d", &source, &destination);
        addEdge(graph, source, destination);
    }
}
/// bfs utils
int isEmpty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *new_node = createNode(data);
    if (isEmpty(*queue)) {
        *queue = new_node;
    }
    else {
        NODE *copy = *queue;
        while (copy->next) {
            copy = copy->next;
        }
        copy->next = new_node;
    }
}

int dequeue(NODE **queue){
    int data = (*queue)->data;
    NODE *copy = *queue;
    *queue = (*queue)->next;
    free(copy);
    return data;
}

void printGraph(GRAPH *graph) {
    int i;
    for (i = 0; i < graph->number_vertices; i++){
        NODE *copy = graph->adjacency_lists[i];
        while (copy){
            printf("%d ", copy->data);
            copy = copy->next;
        }
        printf("\n");
    }
}

void printQueue(NODE *queue){
    while (queue != NULL){
        printf("%d ", queue->data);
        queue = queue->next;
    }
}

void resetVisitedNodes(GRAPH *graph, int number_vertices){
    for (int i = 0; i < number_vertices; i++) {
        graph->visited_nodes[i] = 0;
    }
}
// parcurgeri
void depthFirstSearch(GRAPH *graph, int current_vertex){
    if (graph == NULL || graph->adjacency_lists == NULL) {
        return;
    }

    NODE *adjancency_list = graph->adjacency_lists[current_vertex];
    NODE *current_node = adjancency_list;
    graph->visited_nodes[current_vertex] = 1;
    printf("%d ", current_vertex);

    while (current_node != NULL){
        int connected_vertex = current_node->data;
        if (graph->visited_nodes[connected_vertex] == 0){
            depthFirstSearch(graph, connected_vertex);
        }
    current_node = current_node->next;
    }
}

void breadthFirstSearch(GRAPH *graph, int start_vertex) {
    NODE *queue = NULL;
    graph->visited_nodes[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!isEmpty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);
        NODE *current_node = graph->adjacency_lists[current_vertex];
        while (current_node){
            int adjancency_vertex = current_node->data;

            if (graph->visited_nodes[adjancency_vertex] == 0) {
                graph->visited_nodes[adjancency_vertex] = 1;
                enqueue(&queue, adjancency_vertex);
            }
            current_node = current_node->next;
        }
    }
}

int main(){
    int number_vertices;
    int number_edges;
    int starting_vertex;

    printf("Cate noduri are graful?");
    scanf("%d", &number_vertices);

    printf("Cate muchii are graful?");
    scanf("%d", &number_edges);

    GRAPH *graph = createGraph(number_vertices);
    insertEdges(number_vertices, number_edges, graph);

    printf("De unde plecam in DFS (depth-first search) ?");
    scanf("%d", &(starting_vertex)); // =)))

    printf("Parcurgere cu DFS (depth-first search):");
    depthFirstSearch(graph, starting_vertex);
    resetVisitedNodes(graph, number_vertices);
    printf("\n");

    printf("De unde plecam in BFS (breadth-first search) ?");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS (breadth-first search): ");
    breadthFirstSearch(graph, starting_vertex);
    return 0;
}
