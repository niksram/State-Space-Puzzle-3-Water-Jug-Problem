#ifndef stte
#define stte
#include <stdio.h>
#include <stdlib.h>
typedef struct Node
{
    int jug[3];
    int cap[3];
    int transition;
    struct Node *prev;
    struct Node *next;
} Node;
typedef struct List
{
    Node *head;
    Node *tail;
} List;
void list_init(List *);
Node *create_node(int, int, int, int, int, int, int);
void insert_at_end(List *, Node *);
void remove_at_end(List *);
void display(List *);
int compare_nodes(Node *, Node *);
int compare_all_nodes(List *, Node *);
void transition_func(Node *, Node *, int);
void state_space_search(int (*)[3]);

#endif
