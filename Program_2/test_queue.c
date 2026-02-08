/*
 * This file contains executable code for testing your queue implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(void) {
  int simfront, simback, i, n = 16, k_deq = 4, k_enq = 8;
  int* test_data;
  int** simqueue;
  struct queue* q;

  /*
   * Create array of testing data.
   */
  test_data = malloc(n * sizeof(int));
  for (i = 0; i < n; i++) {
    test_data[i] = i * i;
  }

  /*
   * Create queue and enqueue part of the testing data into it.  Simulate a
   * queue in the simqueue array (with current front/back kept track of in
   * simfront/simback).
   */
  q = queue_create();
  simqueue = malloc(n * sizeof(int*));
  simfront = simback = 0;
  printf("== Enqueueing first %d of %d values.\n", k_enq, n);
  for (i = 0; i < k_enq; i++) {
    queue_enqueue(q, &test_data[i]);
    simqueue[simback++] = &test_data[i];
  }

  /*
   * Dequeue a few of the values held in the queue and make sure they're the
   * correct values.
   */
  printf("\n== Dequeueing some values: front / dequeued (expected)\n");
  for (i = 0; i < k_deq; i++) {
    int* expected = simqueue[simfront++];
    int* front = queue_front(q);
    int* dequeued = queue_dequeue(q);
    if (front && dequeued) {
      printf("  - %4d / %4d (%4d)\n", *front, *dequeued, *expected);
    } else {
      printf("  - front (%p) or dequeued (%p) is NULL (expected: %4d)\n", (void*)front,
        (void*)dequeued, *expected);
    }
  }

  /*
   * Enqueue remaining values into queue (and simulated queue).
   */
  printf("\n== Enqueueing remaining %d of %d values.\n", n - k_enq, n);
  for (i = k_enq; i < n; i++) {
    queue_enqueue(q, &test_data[i]);
    simqueue[simback++] = &test_data[i];
  }

  /*
   * Dequeue the remaining values held in the queue and make sure they're the
   * correct values.
   */
  printf("\n== Dequeueing remaining values: front / dequeued (expected)\n");
  while (simfront < simback && !queue_isempty(q)) {
    int* expected = simqueue[simfront++];
    int* front = queue_front(q);
    int* dequeued = queue_dequeue(q);
    if (front && dequeued) {
      printf("  - %4d / %4d (%4d)\n", *front, *dequeued, *expected);
    } else {
      printf("  - front (%p) or dequeued (%p) is NULL (expected: %4d)\n", (void*)front,
        (void*)dequeued, *expected);
    }
  }

  /*
   * Make sure the queue is actually empty and also exhausted all actual data.
   */
  printf("\n== Is queue empty (expect 1)? %d\n", queue_isempty(q));
  printf("== Saw all test data (expect 1)? %d\n", simfront == simback);

  queue_free(q);
  free(test_data);
  free(simqueue);

  return 0;
}
