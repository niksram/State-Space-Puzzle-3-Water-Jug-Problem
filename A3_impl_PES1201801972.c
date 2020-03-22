#include "A3_header_PES1201801972.h"
void XtoY(Node *, Node *, int, int);

void list_init(List *list) // initialises the list with pointers pointing to NULL
{
    list->head = NULL;
    list->tail = NULL;
}

Node *create_node(int transition, int j0, int j1, int j2, int c0, int c1, int c2)
{ // creates a node with respective jug values as well as its Max-Capacity
    Node *node = (Node *)malloc(sizeof(Node));
    node->jug[0] = j0;
    node->jug[1] = j1;
    node->jug[2] = j2;
    node->cap[0] = c0;
    node->cap[1] = c1;
    node->cap[2] = c2;
    node->transition = transition;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insert_at_end(List *list, Node *node) //node insertion at th end of the doubly-linked list
{
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->prev = list->tail;
        node->prev->next = node;
        list->tail = node;
    }
}

void remove_at_end(List *list) //node deletion at th end of the doubly-linked list
{
    if (list->tail)
    {
        if (list->tail == list->head)
        {
            list->head = NULL;
        }
        else
        {
            list->tail->prev->next = NULL;
        }
        Node *temp = list->tail;
        list->tail = list->tail->prev;
        free(temp);
    }
}

void display(List *list) // displays the entire list with contents of all 3 jugs in each line
{
    Node *node = list->head;
    while (node)
    {
        printf("%d %d %d\n", node->jug[0], node->jug[1], node->jug[2]);
        node = node->next;
    }
}

int compare_nodes(Node *node1, Node *node2)
{ // compares 2 node 'jug' values to find if they are the indentical state or not
    for (int i = 0; i < 3; i++) // here, only the 'jug' values are compared, not other parameters
    {
        if (node1->jug[i] != node2->jug[i])
        {
            return 0;
        }
    }
    return 1;
}

int compare_all_nodes(List *list, Node *node)
{ // compares all the nodes but the last with the given node to find if there exists a loop
    Node *lnode = list->head;
    while (lnode && lnode != list->tail)
    {
        if (compare_nodes(node, lnode))
        {
            return 1;
        }
        lnode = lnode->next;
    }
    return 0;
}

void transition_func(Node *source, Node *dest, int val)
{ //calls the repective transition function in the mentioned order based on val
    dest->transition = val;
    switch (val)
    {
    case 0:
    {
        XtoY(source, dest, 0, 1); // A to B
        break;
    }
    case 1:
    {
        XtoY(source, dest, 0, 2); // A to C
        break;
    }
    case 2:
    {
        XtoY(source, dest, 1, 0); // B to A
        break;
    }
    case 3:
    {
        XtoY(source, dest, 1, 2); // B to C
        break;
    }
    case 4:
    {
        XtoY(source, dest, 2, 0); // C to A
        break;
    }
    case 5:
    {
        XtoY(source, dest, 2, 1); // C to B
        break;
    }
    }
}

void XtoY(Node *old, Node *new, int source, int dest) //generic transition function to tranfer contents from jug 'source' to jug 'dest'. Changes reflected in the new node
{
    if (old->jug[source] <= old->cap[dest] - old->jug[dest]) // if jug 'source' content is less than empty space in jug 'dest'
    {
        new->jug[dest] = old->jug[dest] + old->jug[source]; // pour entire jug 'source' into the jug 'dest'
        new->jug[source] = 0;
    }
    else
    {
        new->jug[source] = old->jug[source] - (old->cap[dest] - old->jug[dest]); // pour till empty space becomes 0
        new->jug[dest] = old->cap[dest];
    }
}