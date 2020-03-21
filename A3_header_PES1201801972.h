#ifndef stte
#define stte
#include <stdio.h>
#include <stdlib.h>
typedef struct Node // node of doubly linked list
{
    int jug[3]; // array which holds the content in each jug
    int cap[3]; // array which holds the content in each jug
    int transition; // holds the index of the undergone transition (from 0 to 5), if its >= 6, then it signifies to pop out elements
    struct Node *prev; // link to previous node
    struct Node *next; // link to next node
} Node;
typedef struct List // list structure
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
