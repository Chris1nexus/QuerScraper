#include <stdio.h>
#include <stdlib.h>

/* function prototypes */
int square_recur(int **matrix, int dim, int *used, int k);
int test(int **matrice, int dim);
void *util_malloc(int size);

/*
 *  main program
 */
int main(void)
{
  int **matrix, *used, i, j, n;

  printf("Matrix size: ");
  scanf("%d", &n);

  used = (int *)util_malloc((n*n+1) * sizeof(int));
  matrix = (int **)util_malloc(n * sizeof(int *));
  for (i=0; i<n; i++) {
    matrix[i] = (int *)util_malloc(n*sizeof(int));
  }
  for (i=0; i<=n*n; i++) {
    used[i] = 0;
  }  
  
  if (square_recur(matrix, n, used, 0)) {
    printf("Magic square of size %d:\n", n);
    for (i=0; i<n; i++) {
      for (j=0; j<n; j++) {
        printf("%2d ", matrix[i][j]);
      }
      printf("\n");
    }
  } else {
    printf("Magic Square NOT found!\n");
  }
    
  free(used);
  for (i=0; i<n; i++) {
    free(matrix[i]);
  }
  free(matrix);

  return EXIT_SUCCESS;
}

/*
 *  compute a magic square of given size; return 1 upon success
 */
int square_recur(int **matrix, int dim, int *used, int k)
{
  int i, j, val;

  if (k == dim*dim) {
    return test(matrix, dim);
  }
  
  i = k/dim;
  j = k%dim;
  for (val=1; val<=dim*dim; val++) {
    if (used[val] == 0) {
      /* put a new value and recur */
      matrix[i][j] = val;
      used[val] = 1;
      if (square_recur(matrix, dim, used, k+1)){
        /* solution found: stop the process */
        return 1; 
      }
      /* backtrack */
      used[val] = 0;
    }
  }
  
  /* solution not found */
  return 0;
}

/*
 *  check whether a given matrix is a magic square; return 1 if yes
 */
int test(int **matrix, int dim)
{
  int i, j, sum, target=dim*(dim*dim+1)/2;
   
  /* rows */
  for (i=0; i<dim; i++) {
    sum = 0;
    for (j=0; j<dim; j++) {
      sum += matrix[i][j];
    }
    if (sum != target) {
      return 0;
    }
  }

  /* columns */
  for (j=0; j<dim; j++) {
    sum = 0;
    for (i=0; i<dim; i++) {
      sum += matrix[i][j];
    }
    if (sum != target) {
      return 0;
    }
  }
  
  /* diagonals */
  sum = 0;
  for (i=0; i<dim; i++) {
    sum += matrix[i][i];
  }
  if (sum != target) {
    return 0;
  }

  sum = 0;
  for (i=0; i<dim; i++) {
    sum += matrix[i][dim-1-i];
  }
  if (sum != target) {
    return 0;
  }

  return 1;
}

/*
 *  malloc (with check) utility function
 */
void *util_malloc(int size)
{
  void *ptr=malloc(size);
  if (ptr == NULL) {
    printf("Memory allocation error.\n");
    exit(EXIT_FAILURE);
  }  
  return ptr;
}
