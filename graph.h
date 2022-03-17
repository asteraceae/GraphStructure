#include <stdio.h>
#include <stdlib.h>


#define SIZE 50

typedef struct Node{
  int taskno; //task number
  char * task_name; //name of task
  char * end; //adjacent
  struct Node* next;  //store next node
  int done;
} Node;

//Graph will store the head so that we know where to start when printing
typedef struct Graph{
  Node* head[51];
  pthread_mutex_t mutex;
  pthread_cond_t cond;
  
} Graph;

typedef struct Vert{
  char * first;
  char * second;
} Vert;

typedef struct Task{
  char * name;
  int taskno;
} Task;

Node* new_node(int taskn, char * start, char * task, Node* next);
Vert* new_vert(char * first, char * second);
Graph* new_graph(Vert* verts[], int count);
Task* new_task(char * name, int taskno);
Task* find(Task* tasks[], char * str, int n);
void print_graph(Graph* graph);
void delete_node(Graph* graph, char * taskname);
void edit_node(Graph* graph, char * newname);
void find_node(Graph* graph, char * taskname);