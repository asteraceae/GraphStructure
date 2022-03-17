#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "graph.h"
#include "thread.h"

#define SIZE 50
int counter = 0;
pthread_t id[SIZE + 1];
Graph* graph;

void save(Graph* g){
  graph = g;
}

void* run_me(void *tsd){
  int pre_done = 0;
  Node* task = (Node*) tsd; 
  
  /*to determine, atomically, whether the predecessors have finished. You will need pthread_cond_wait() to accomplish this, surrounded by a clever while loop that checks for whether all of the predecessor tasks have completed.*/
  lock(graph);
  Node* ptr = graph->head[0];
  while (ptr != task){
    if (ptr->done == 1){
      pre_done = 1;
    }
    ptr = ptr->next;
  }
  /*Third, upon confirming that the predecessor tasks have completed, you simply print the name of the task to the standard output.
 */
  if (pre_done == 0){
    printf("%s", task->task_name);
  }
  /*Fourth, efore releasing the lock, using pthread_mutex_unlock(), you will signal all waiting threads that the current task is done. Some cleverness is required here, because there can be multiple dependencies, e.g. T1 -> T2 and T1 -> T3. Each of T2 and T3 will need to get notified by T1. Note that you are not explicitly notifying these tasks. You are simply signalling all waiting threads that the state of the task graph has changed.*/
  if (pre_done == 0){
     unlock(graph);
  }

}

void lock(Graph* graph) {
    pthread_mutex_lock(&graph->mutex);
}

void unlock(Graph* graph) {
    pthread_mutex_unlock(&graph->mutex);
}