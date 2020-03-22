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
void list_init(List *); // initialises the head and tail to NULL
Node *create_node(int, int, int, int, int, int, int); // creates the node with parameters (transition, jug[3], capacity[3])
void insert_at_end(List *, Node *); // insert the node at the end
void remove_at_end(List *);// remove the node at the end
void display(List *);   // display the entire list contents
int compare_nodes(Node *, Node *); // compare the jug parameters only of the node.
int compare_all_nodes(List *, Node *); // compares the node (compare_node) with all the list nodes but the last node.
void transition_func(Node *, Node *, int); // sets the parameters for the new node from the old node based on the transition function performed.

#endif
