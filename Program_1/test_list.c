/*
 * This file contains executable code for testing your linked list
 * implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "test_data.h"

/*
 * Function to run tests on linked list implementation.
 */
void test_list(struct student** students, int n) {
  struct list* list;
  struct student* s;
  int i, p;

  /*
   * Create a list.
   */
  list = list_create();
  printf("Checking that list is not NULL... ");
  fflush(stdout);
  if (list == NULL) {
    printf("FAIL\n");
  } else {
    printf("OK\n");
  }

  /*
   * Add students to list (in reverse order, so the list order matches the
   * order of the input array).
   */
  printf("\n");
  for (i = n - 1; i >= 0; i--) {
    printf("Adding students[%d] to the list... ", i);
    fflush(stdout);
    list_insert(list, students[i]);
    printf("OK (check for correct positions below)\n");
  }

  /*
   * Check that we can fetch values from the dynamic array.
   */
  printf("\n");
  for (i = 0; i < n; i++) {
    printf("Position of students[%d] (should be %d)... ", i, i);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }

  /*
   * Reverse list and check for reversed positions.
   */
  printf("\nReversing list... ");
  fflush(stdout);
  list_reverse(list);
  printf("OK (check for correct positions below)\n");
  for (i = 0; i < n; i++) {
    printf("Position of students[%d] (should be %d)... ", i, n - i - 1);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }

  /*
   * Check for nonexistent student.
   */
  s = malloc(sizeof(struct student));
  s->name = "Kylo Ren";
  s->id = 933999999;
  s->gpa = 0.75;
  printf("\nPosition of non-existent student (should be -1)... ");
  fflush(stdout);
  p = list_position(list, s, &compare_students);
  printf("%d\n", p);
  free(s);

  /*
   * Test removing students.
   */
  for (i = n - 1; i > 0; i /= 2) {
    printf("\nRemoving students[%d]... ", i);
    fflush(stdout);
    list_remove(list, students[i], &compare_students);
    printf("OK (check below to make sure removed correctly)\n");
    printf("Position of students[%d] (should be -1)... ", i);
    fflush(stdout);
    p = list_position(list, students[i], &compare_students);
    printf("%d\n", p);
  }

  printf("\nFreeing list... ");
  fflush(stdout);
  list_free(list);
  printf("OK (check valgrind output to ensure no memory leaks)\n");
}

int main(void) {
  struct student** students;
  int i;

  /*
   * Create and fill an array of student structs.
   */
  students = malloc(NUM_TESTING_STUDENTS * sizeof(struct student*));
  for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
    students[i] = malloc(sizeof(struct student));
    students[i]->name = TESTING_NAMES[i];
    students[i]->id = TESTING_IDS[i];
    students[i]->gpa = TESTING_GPAS[i];
  }

  test_list(students, NUM_TESTING_STUDENTS);

  /*
   * Free the array of student structs.
   */
  for (i = 0; i < NUM_TESTING_STUDENTS; i++) {
    free(students[i]);
  }
  free(students);
}
