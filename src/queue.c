#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        if(q==NULL || proc==NULL) return;

        if(q->size < MAX_QUEUE_SIZE){
                q->proc[q->size++] = proc;
        } else {
                printf("Queue is full !!! Cannot enqueue PID %u\n", proc->pid);
        }
;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if(q==NULL || q->size == 0) return NULL;

        int highest_idx = 0;
        for(int i=0; i<q->size; ++i)
        {
        #ifdef MLQ_SCHED
                if(q->proc[i]->prio < q->proc[highest_idx]->prio) highest_idx = i;
        #else
                if(q->proc[i]->priority < q->proc[highest_idx]->priority) highest_idx = i;
        #endif
        }

        struct pcb_t *ret = q->proc[highest_idx];

        for(int i = highest_idx; i<q->size-1; ++i){
                q->proc[i] = q->proc[i+1];
        }
        q->proc[--q->size] = NULL;

	return ret;
}

struct pcb_t *purgequeue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: remove a specific item from queue
         * */
        if(q==NULL || proc==NULL || q->size==0) return NULL;

        for(int i=0; i<q->size; ++i){
                if(q->proc[i] == proc){
                        struct pcb_t *ret = q->proc[i];
                        for(int j=i; j<q->size-1; ++j){
                                q->proc[j] = q->proc[j+1];
                        }
                        q->proc[--q->size] = NULL;
                        return ret;
                }
        }

        return NULL;
}