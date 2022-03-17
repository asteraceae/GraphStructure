#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "graph.h"

#define SIZE 50

Task* find(Task* tasks[], char * str, int n){
  for (int k = 0; k < n; k++){
    if (tasks[k] != NULL){
      if (strcmp(tasks[k]->name, str) == 0){
        return tasks[k];
      }
    }
  }
  return NULL;

}
Node* new_node(int taskno, char * start, char * task, Node* next){
  Node* new_node = (Node*) malloc(sizeof(*new_node));
  new_node->taskno = taskno;
  new_node->task_name = task;
  new_node->next = next;
  new_node->end = start;
  new_node->done = 0;
  
  return new_node;
}


Task* new_task(char * name, int taskno){
  Task* new_task = (Task*) malloc(sizeof(*new_task));

  new_task->name = name;
  new_task->taskno = taskno;
  
  return new_task;
}

Graph* new_graph(Vert* verts[], int count){
  Graph* new_graph = (Graph*) malloc(sizeof(*new_graph));
  int taskno = 0;
  Task* endt;
  Task* begint;
  Task* tasks[SIZE + 1] = {NULL};
  char * begin;
  char * end;

  for (int i = 0; i < SIZE; i++){
   new_graph->head[i] = NULL;
  }

  for (int i = 0; i < count; i++){
    begin = verts[i]->first;
    end = verts[i]->second;
    //printf("DEBUG %s", begin);
   
    if (find(tasks, begin, SIZE) == NULL){
      begint = new_task(begin, taskno);
      tasks[taskno] = begint;
      taskno++;
    }
    else {
      begint = find(tasks, begin, SIZE);
    }
    if (find(tasks, end, SIZE) == NULL){
      endt = new_task(end, taskno);
      tasks[taskno] = endt;
      taskno++;
    }
    else {
      endt = find(tasks, begin, SIZE);
    }

    Node* endn = new_node(endt->taskno, end, begin, new_graph->head[endt->taskno]);
    new_graph->head[endn->taskno] = endn;
    Node* beginn = new_node(begint->taskno, end, begin, new_graph->head[endt->taskno]);
    new_graph->head[beginn->taskno] = beginn;
  }

  return new_graph;
}

Vert* new_vert(char * first, char * second){
  Vert* new_vert = (Vert*) malloc(sizeof(new_vert));
  char * store1 = first;
  char * store2 = second;
  new_vert->first = store1;
  new_vert->second = store2;
  return new_vert;
}

void print_graph(Graph* graph){
  for (int i = 0; i < SIZE; i++){
    Node* ptr = graph->head[i];
    while (ptr != NULL){
      printf("%s -> %s\t\n", ptr->task_name, ptr->end);
      ptr = ptr->next;
    }
  }
}

void delete_node(Graph* graph, char * taskname){
  for (int i = 0; i < SIZE; i++){
    Node* ptr = graph->head[i];
    while (ptr != NULL){
      if (strcmp(ptr->task_name, taskname) == 0){
        ptr = NULL;
        break;
      }
      ptr = ptr->next;
    }
  }
}

void edit_node(Graph* graph, char * newname){
  for (int i = 0; i < SIZE; i++){
    Node* ptr = graph->head[i];
    while (ptr != NULL){
      if (strcmp(ptr->task_name, newname) == 0){
        ptr->task_name = newname;
        break;
      }
      ptr = ptr->next;
    }
  }
}

void find_node(Graph* graph, char * taskname){
  for (int i = 0; i < SIZE; i++){
    Node* ptr = graph->head[i];
    while (ptr != NULL){
      if (strcmp(ptr->task_name, taskname) == 0){
        printf("Node %s is in the graph.\n", taskname);
        break;
      }
      ptr = ptr->next;
    }
  }
}

