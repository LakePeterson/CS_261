/*
 * This file contains executable code for testing your dynamic array
 * implementation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "dynarray.h"
#include "test_data.h"

/*
 * Function to run tests on dynamic array implementation.
 */
void test_dynarray(struct student** students, int n)
{
  struct dynarray* da;
  struct student* repl, * s;
  int i, n_removed = 0;

  /*
   * Create a dynamic array.
   */
  da = dynarray_create();
  printf("Checking that array is not NULL... ");
  fflush(stdout);

  if(da == NULL)
  {
    printf("FAIL\n");
  }
  else
  {
    printf("OK\n");
  }

  /*
   * Add students to dynamic array.
   */
  printf("\n");
  for(i = 0; i < n; i++)
  {
    printf("Adding students[%d] to the array... ", i);
    fflush(stdout);
    dynarray_insert(da, students[i]);
    printf("OK (check for correct array contents below)\n");
  }

  /*
   * Check dynamic array size.
   */
  printf("\nChecking array size (%d == %d?)... ", n, dynarray_size(da));
  fflush(stdout);
  if(n == dynarray_size(da))
  {
    printf("OK\n");
  }
  else
  {
    printf("FAIL\n");
  }

  /*
   * Check that we can fetch values from the dynamic array.
   */
  printf("\nArray contents:\n");
  for (i = 0; i < dynarray_size(da); i++)
  {
    s = dynarray_get(da, i);
    if(s)
    {
      printf("  %-16s\t%d\t%f\n", s->name, s->id, s->gpa);
    }
    else
    {
      printf("  NULL\n");
    }
  }

  /*
   * Test updating values stored in the dynamic array.
   */
  repl = malloc(sizeof(struct student));
  repl->name = "Kylo Ren";
  repl->id = 933999999;
  repl->gpa = 0.75;
  for(i = n - 1; i > 0; i /= 2)
  {
    printf("\nReplacing element %d... ", i);
    fflush(stdout);
    dynarray_set(da, i, repl);
    printf("OK (check that values below match)\n");
    printf("Inserted:  %-16s\t%d\t%f\n", repl->name, repl->id, repl->gpa);
    s = dynarray_get(da, i);
    if(s)
    {
      printf("Array @ %1d: %-16s\t%d\t%f\n", i, s->name, s->id, s->gpa);
    }
    else
    {
      printf("Array @ %1d: %-16s\n", i, "NULL");
    }
  }

  /*
   * Test removing elements from the dynamic array by removing the copies of
   * repl that were inserted above.
   */
  printf("\n");
  for(i = n - 1; i > 0; i /= 2)
  {
    printf("Removing element %d... ", i);
    fflush(stdout);
    dynarray_remove(da, i);
    printf("OK (check updated array contents below)\n");
    n_removed++;
  }

  printf("\nNew array size (should be %d): %d\n", n - n_removed,
    dynarray_size(da));
  printf("New array contents (should have no %s):\n", repl->name);
  for(i = 0; i < dynarray_size(da); i++)
  {
    s = dynarray_get(da, i);
    if(s)
    {
      printf("  %-16s\t%d\t%f\n", s->name, s->id, s->gpa);
    }
    else
    {
      printf("  NULL\n");
    }
  }

  free(repl);

  printf("\nFreeing array... ");
  fflush(stdout);
  dynarray_free(da);
  printf("OK (check valgrind output to ensure no memory leaks)\n");
}

int main(void)
{
  struct student** students;
  int i;

  /*
   * Create and fill an array of student structs.
   */
  students = malloc(NUM_TESTING_STUDENTS * sizeof(struct student*));
  for (i = 0; i < NUM_TESTING_STUDENTS; i++)
  {
    students[i] = malloc(sizeof(struct student));
    students[i]->name = TESTING_NAMES[i];
    students[i]->id = TESTING_IDS[i];
    students[i]->gpa = TESTING_GPAS[i];
  }

  test_dynarray(students, NUM_TESTING_STUDENTS);

  /*
   * Free the array of student structs.
   */
  for(i = 0; i < NUM_TESTING_STUDENTS; i++)
  {
    free(students[i]);
  }
  free(students);
}
