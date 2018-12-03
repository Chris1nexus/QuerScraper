#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20+1

/* structure declaration */
typedef struct m m_t;
typedef struct p p_t;

struct m {
  char *name;
  char *id;
  p_t *p;
  m_t *next;
};

struct p {
  char *name;
  int price;
  p_t *next;
};

m_t *load (char *, char *);
void printAll (m_t *);
void search (m_t *, char *);
void destroy (m_t *);

/*
 *  main program
 */
int
main (
  int argc,
  char *argv[]
  )
{
  m_t *head;
  char m[MAX];

  head = load (argv[1], argv[2]);

#if 1
  printAll (head);
#endif

  do {
    fprintf (stdout, "Manufacturer: ");
    scanf ("%s", m);

    if (strcmp (m, "end")) {
      search (head, m);
    }
  } while (strcmp (m, "end") != 0);

  destroy (head);

  return EXIT_SUCCESS;
}

m_t *load (
  char *filename1,
  char *filename2
  )
{
  m_t *head, *new1;
  p_t *new2;
  FILE *fp;
  int price, found;
  char str1[MAX], str2[MAX];

  head = NULL;
  fp = fopen (filename1, "r");
  while (fscanf (fp, "%s%s", str1, str2) != EOF) {
    new1 = (m_t *) malloc (sizeof (m_t));
    if (new1==NULL) {
      fprintf (stdout, "Allocation error.\n");
      exit (1);
    }
    new1->name = strdup (str1);
    new1->id = strdup (str2);
    new1->p = NULL;
    new1->next = head;
    head = new1;
  }
  fclose(fp);

  fp = fopen (filename2, "r");
  while (fscanf (fp, "%s%s%d", str1, str2, &price) != EOF) {
    new2 = (p_t *) malloc (sizeof (p_t));
    if (new2==NULL) {
      fprintf (stdout, "Allocation error.\n");
      exit (1);
    }
    new2->name = strdup (str2);
    new2->price = price;
    found = 0;
    new1 = head;
    while (new1!=NULL && found==0) {
      if (strcmp (new1->id, str1)==0) {
        found = 1;
      } else {
        new1 = new1->next;
      }
    }
    if (found==1) {
      new2->next = new1->p;
      new1->p = new2;
    } else {
      fprintf (stderr, "There is no such a brand ...  Rule-out model\n");
    }
  }
  fclose(fp);

  return head;
}

void printAll (
  m_t *head
  )
{
  m_t *tmp1;
  p_t *tmp2;

  tmp1 = head;
  while (tmp1 != NULL) {
    fprintf (stdout, "%s %s\n", tmp1->name, tmp1->id);
    tmp2 = tmp1->p;
    while (tmp2 != NULL) {
      fprintf (stdout, "  - %s %d\n", tmp2->name, tmp2->price);
      tmp2 = tmp2 ->next;
    }
    tmp1 = tmp1->next;
  }

  return;
}

void search (
  m_t *head,
  char *name
  )
{
  m_t *tmp1;
  p_t *tmp2;

  tmp1 = head;
  while (tmp1 != NULL) {
    if (strcmp (tmp1->name, name) == 0) {
      tmp2 = tmp1->p;
       while (tmp2 != NULL) {
        fprintf (stdout, "  - %s %d\n", tmp2->name, tmp2->price);
        tmp2 = tmp2 ->next;
      }
      break;
    } else {
      tmp1 = tmp1->next;
    }
  }

  return;
}

void
destroy (
  m_t *head
  )
{
  m_t *tmp1a, *tmp1b;
  p_t *tmp2a, *tmp2b;

  tmp1a = head;
  while (tmp1a != NULL) {
    tmp2a = tmp1a->p;
    while (tmp2a != NULL) {
      tmp2b = tmp2a->next;
      free (tmp2a->name);
      free (tmp2a);
      tmp2a = tmp2b;
    }
    tmp1b = tmp1a->next;
    free (tmp1a->name);
    free (tmp1a->id);
    free (tmp1a);
    tmp1a = tmp1b;
  }
}
