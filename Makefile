task: task.c graph.c thread.c
	gcc task.c graph.c thread.c -o task -Wall -lpthread

clean:
	rm task
