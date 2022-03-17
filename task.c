#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "graph.h"
#include "thread.h"

#define MAX 150
#define SIZE 50

int count = 0;
Vert* verts[SIZE + 1] = {NULL};

void make_verts(char * difinput){
  char * token = strtok(difinput, " ,->{}");
  char * head = token;
  //now get its dependents
  while (token != NULL){
    token = strtok(NULL, " ,->{}");
    //add head and dependent pair to vertices
    if (token != NULL){
      Vert* vert = new_vert(head, token);
      verts[count] = vert;
      printf("Vert is %s, %s\n", verts[count]->first, verts[count]->second);
      count++;
      }
  }
}

int main() {
  //char input[MAX];
 // int exit = 0;

  char difinput[] = "T1 -> {T2, T3, T4}";
  char difinput2[] = "T3 -> {T4}";

  make_verts(difinput);
  make_verts(difinput2);

  //create graph
  Graph* graph = new_graph(verts, count);
  save(graph);

  //initialize thread stuff
  int count_t = 0;
  pthread_t id[150];


  //now lets iterate through graph
   for (int i = 0; i < SIZE; i++){
    Node* ptr = graph->head[i];
    while (ptr != NULL){
      pthread_create(&id[count_t], NULL, run_me, &ptr);
      count_t++;
      ptr = ptr->next;
    }
  }
  //print_graph(graph);
  
  return 0;
}