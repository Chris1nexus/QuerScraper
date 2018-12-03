#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define  A_to_a  ('a'-'A')
#define  ALFA  'A'
#define  ZETA  'z'
#define  W_SIZE  100

typedef struct wordS {
  char *word;
  int freq;
  struct wordS *next;
} wordT;

wordT *listCreate (FILE *);
wordT *findWord (wordT *, char *);
void cleanWord (char *);
void writeList (wordT *, FILE *);
void cleanUp (wordT *);
wordT *push (wordT *, char *);

int
main (
  int argc,
  char *argv[]
  )
{
  FILE  *fpR, *fpW;
  wordT  *headP;
   
  headP = NULL;
   
  if ( argc > 2 ) {
    fpR = fopen (argv[1], "r");
    fpW = fopen (argv[2], "w");
    if (fpR==NULL || fpW==NULL) {
      printf("Error Opening Files.\n");
      return(1);
    }
  
    headP = listCreate(fpR);
  
    writeList(headP, fpW);
  
    fclose(fpR);
    fclose(fpW);
    cleanUp(headP);
  } else {
    printf("Wrong Parameters.\n");
  }
   
  return(0);
}

wordT *
listCreate (
  FILE *fp
  )
{
  wordT *headP = NULL, *tmpP;
  char buffer[W_SIZE+3];
  
  while ( (fscanf(fp, "%s", buffer))!=EOF ) {
    cleanWord(buffer);
    tmpP = findWord(headP, buffer);
    if ( tmpP !=NULL ) {
      tmpP->freq++;
    } else {
      headP = push (headP, buffer);
    }
  }
  
  return(headP);
}

wordT *push (
  wordT *headP,
  char *buffer
  )
{
  wordT *newP;

  newP = malloc (1*sizeof (wordT));
  if (newP == NULL) {
    printf("Allocation Error.\n");
    exit(1);
  }
  newP->word = malloc((strlen(buffer)+1)*sizeof(char));
  if ( newP->word == NULL ) {
    printf("Allocation Error.\n");
    exit(1);
  }
  strcpy (newP->word, buffer);
  newP->freq = 1;
  newP->next = headP;

  return (newP);
}

wordT *
findWord (
  wordT *headP,
  char *word
  )
{
  wordT *tmpP;
  int n, i, m;
  int found = 0;
   
  tmpP = headP;
  n = strlen(word);
   
  while ( tmpP!=NULL ) {
    m = strlen(tmpP->word);
    if ( m==n ) {
      for (i=0;i<n;i++) {
        if ( !(word[i]==(tmpP->word[i]))   &&
          !(word[i]==(tmpP->word[i]+A_to_a))  &&
          !(word[i]==(tmpP->word[i]-A_to_a))
        ) {
          found = 0;
          break;
        }
      }
   
      if (i==n) {
        found = 1;
        break;
      }
    } else {
      found = 0;
    }
    tmpP = tmpP->next;
  }
   
  if (!found) {
    tmpP = NULL;
  }
 
  return(tmpP);
}


void
cleanUp (
  wordT *headP
  )
{
  wordT *tmpP, *l_Next;
   
  tmpP = headP;
   
  while ( tmpP != NULL ) {
    l_Next = tmpP->next;
    free(tmpP);
    tmpP = l_Next;
  }

  headP = NULL;
  return;
}

void
cleanWord (
  char *word
  )
{
  int  i, j, n;
   
  n = strlen(word);
  for ( i=0; i<n; i++) {
    if (word[i]>ZETA  || word[i]<ALFA) {
      for ( j=i; j<n; j++) {
        word[j]=word[j+1];
      }
    }
  }
}

void
writeList (
  wordT *headP,
  FILE *fp 
  )
{
  wordT  *tmpP;
   
  tmpP = headP;
  while ( tmpP != NULL ) {
    fprintf(fp, "%s %d\n", tmpP->word, tmpP->freq);
    tmpP = tmpP->next;
  }

  return;
}
