#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100
#define V 10

typedef struct point
{
    int verNum;
    int weight;
}point;

typedef struct pqueue
{
    point data[MAX];
    int rear,front;
}pqueue;

// Array to store constructed MST
int constructedMST[V];
// minWeightEdge values used to pick minimum weight edge in cut
int minWeightEdge[V];
// To represent set of vertices not yet included in MST
bool minSpanningTree[V];

void initialize(pqueue *p);
int empty(pqueue *p);
void enqueue(pqueue *p, point x);
point dequeue(pqueue *p);

int find(int i){
    while (constructedMST[i] != i)
        i = constructedMST[i];
    return i;
}

void union1(int i, int j){
    int a = find(i);
    int b = find(j);
    constructedMST[a] = b;
}

int printMST(int constructedMST[], int graph[V][V], int numOfVertices)
{
  int outputMatrix[V][V];
  printf("\n Output Matrix from Prim's algorithm:\n");
  for (int i=0;i<numOfVertices;i++) {
    for (int j=0;j<numOfVertices;j++){
      outputMatrix[i][j] = 0;
    }
  }

  for (int i=0;i<numOfVertices;i++) {
    for (int j=0;j<numOfVertices;j++){
      if(j == constructedMST[i]){
        outputMatrix[i][j] = graph[i][constructedMST[i]];
        outputMatrix[j][i] = graph[i][constructedMST[i]];
      }
    }
  }

  printf("\n Matrix of input data:\n");
  for (int i=0;i<numOfVertices;i++) {
    for (int j=0;j<numOfVertices;j++)
       printf("%d \t",outputMatrix[i][j]);
    printf("\n");
  }

  printf("Edge \tWeight\n");
  for (int i = 1; i < numOfVertices; i++)
    printf("%d - %d \t%d \n", constructedMST[i], i, graph[i][constructedMST[i]]);
}


void PrimsCalculate(int graph[V][V], int numOfVertices)
{
    // Initialize all minWeightEdges as INFINITE
    for (int i = 0; i < numOfVertices; i++)
        minWeightEdge[i] = INT_MAX, minSpanningTree[i] = false;

    // Always include first 1st vertex in MST.
    // Make minWeightEdge 0 so that this vertex is picked as first vertex.
    minWeightEdge[0] = 0;
    constructedMST[0] = -1; // First node is always root of MST

    pqueue q;
    initialize(&q);

    point initData;
    initData.verNum = 0;
    initData.weight = 0;

    enqueue(&q, initData);

    while(!empty(&q)){
      point temp = dequeue(&q);
      minSpanningTree[temp.verNum] = true;
      int u = temp.verNum;

      for (int v = 0; v < numOfVertices; v++){
        if (graph[u][v] && minSpanningTree[v] == false && graph[u][v] < minWeightEdge[v]){
          temp.verNum = v;
          temp.weight = graph[u][v];
          constructedMST[v] = u;
          minWeightEdge[v] = graph[u][v];
          enqueue(&q, temp);
        }
      }

    }

    printMST(constructedMST, graph, numOfVertices);
}

void kruskalCalculate(int cost[V][V], int numOfVertices)
{
    int outputMatrix[V][V];

    for (int i=0;i<numOfVertices;i++) {
      for (int j=0;j<numOfVertices;j++){
        outputMatrix[i][j] = 0;
      }
    }


    // Initialize sets of disjoint sets.
    for (int i = 0; i < numOfVertices; i++)
        constructedMST[i] = i;

    // Include minimum weight edges one by one
    int noOfEdges = 0;
    while (noOfEdges < numOfVertices - 1) {
        int min = INT_MAX, temp1 = -1, temp2 = -1;
        for (int i = 0; i < numOfVertices; i++) {
            for (int j = 0; j < numOfVertices; j++) {
                if (find(i) != find(j) && cost[i][j] < min) {
                    min = cost[i][j];
                    temp1 = i;
                    temp2 = j;
                }
            }
        }

        union1(temp1, temp2);
        printf("%d - %d \t%d \n", temp1, temp2, min);
        noOfEdges++;
        outputMatrix[temp1][temp2] = min;
        outputMatrix[temp2][temp1] = min;

    }

    printf("Output Matrix from Kruskal's algorithm:\n");
    for (int i=0;i<numOfVertices;i++) {
      for (int j=0;j<numOfVertices;j++)
         printf("%d \t",outputMatrix[i][j]);
      printf("\n");
    }
}

int main()
{
  int inputMatrix[V][V];
  int noOfVertices;
  int noOfEdges;
  int option;

  printf("Enter the number of vertices between 5 to 10:\n");
  scanf("%d",&noOfVertices);

  //Initial matrix
  for (int i=0;i<noOfVertices;i++) {
    for (int j=0;j<noOfVertices;j++)
      if(i==j)
       inputMatrix[i][j]=0;
      else if(i < j){
        inputMatrix[i][j]=rand() % 9 + 1;
        inputMatrix[j][i] = inputMatrix[i][j];
      }
  }

  /*
  //testing with prof's input
  inputMatrix[V][V] = { { 0, 4, 10, 6, 4 },
                      { 4, 0, 10, 3, 10 },
                      { 10, 10, 0, 5, 5 },
                      { 6, 3, 5, 0, 10 },
                      { 4, 10, 5, 10, 0 } };
  */
  printf("\n Matrix of input data:\n");
  for (int i=0;i<noOfVertices;i++) {
    for (int j=0;j<noOfVertices;j++)
       printf("%d \t",inputMatrix[i][j]);
    printf("\n");
  }

  while(true){


    printf("Choose option to calculate :\n");
    printf("Enter 1 for Prim's algorithm\n");
    printf("Enter 2 for Kruskal’s algorithm\n");
    scanf("%d",&option);

    switch (option) {
        case 1:
          printf("Calculating spanning tree with Prim's algorithm\n");
          PrimsCalculate(inputMatrix, noOfVertices);
          break;

        case 2:
          printf("Calculating spanning tree with Kruskal's algorithm\n");
          kruskalCalculate(inputMatrix, noOfVertices);
          break;
        default: break;
    }
  }



  return 0;
}

void initialize(pqueue *p)
{
    p->rear=-1;
    p->front=-1;
}

int empty(pqueue *p)
{
    if(p->rear==-1)
        return(1);

    return(0);
}

void enqueue(pqueue *p, point x)
{
  int i;
  if(empty(p))
  {
    p->rear=p->front=0;
    p->data[0]=x;
  }
  else
  {
    i=p->rear;

      while(x.weight < p->data[i].weight)
      {
          p->data[(i+1)%MAX]=p->data[i];
          i=(i-1+MAX)%MAX; //anticlockwise movement inside the queue
          if((i+1)%MAX==p->front)
              break;
      }

      //insert x
      i=(i+1)%MAX;
      p->data[i]=x;

      //re-adjust rear
      p->rear=(p->rear+1)%MAX;
  }
}

point dequeue(pqueue *p)
{
    point x;

    if(empty(p))
    {
        printf("Underflow..\n");
    }
    else
    {
        x=p->data[p->front];
        if(p->rear==p->front)   //delete the last element
            initialize(p);
        else
            p->front=(p->front +1)%MAX;
    }

    return(x);
}
