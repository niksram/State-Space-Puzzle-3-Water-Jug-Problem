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
{ // compares 2 node jug values to find if they are the indentical state or not
    for (int i = 0; i < 3; i++)
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
        XtoY(source, dest, 0, 1);
        break;
    }
    case 1:
    {
        XtoY(source, dest, 0, 2);
        break;
    }
    case 2:
    {
        XtoY(source, dest, 1, 0);
        break;
    }
    case 3:
    {
        XtoY(source, dest, 1, 2);
        break;
    }
    case 4:
    {
        XtoY(source, dest, 2, 0);
        break;
    }
    case 5:
    {
        XtoY(source, dest, 2, 1);
        break;
    }
    }
}

void XtoY(Node *source, Node *dest, int sj, int dj)
{                                                             //generic transition function to tranfer contents from jug 'sj' to jug 'dj'. Changes reflected in the destination node
    if (source->jug[sj] <= source->cap[dj] - source->jug[dj]) // if jug 'sj' content is less than empty space in jug 'dj'
    {
        dest->jug[dj] = source->jug[dj] + source->jug[sj];
        dest->jug[sj] = 0;
    }
    else
    {
        dest->jug[sj] = source->jug[sj] - (source->cap[dj] - source->jug[dj]);
        dest->jug[dj] = source->cap[dj];
    }
}

void state_space_search(int (*mat)[3]) // the master function which performs the task by taking in the 3X3 input matrix
{
    Node *solution = create_node(-1, mat[2][0], mat[2][1], mat[2][2], mat[0][0], mat[0][1], mat[0][2]); // reference solution node
    List *list = (List *)malloc(sizeof(List));
    list_init(list); //initialising the doubly linked list
    Node *node = create_node(-1, mat[1][0], mat[1][1], mat[1][2], mat[0][0], mat[0][1], mat[0][2]);
    insert_at_end(list, node); //inserting root node, Transition arbitrarily set to -1
    int count = 0;             // counter to count the number of valid solutions
    int flag = 1;              // the flag based on which the main while loop runs
    if (compare_nodes(list->head, solution))
    { // if the root is the same as the solution state, the solution is the root itself
        display(list);
        printf("\n");
        count++;
        flag--;
    }
    while (flag)
    {
        if (compare_nodes(solution, node)) // if the solution exists, then display
        {
            display(list);
            printf("\n");
            count++;
        }

        if (node->prev && node->prev != list->head && node->transition >= 6)
        {   // if a node has undergone all transitions from 0 to 5 (ie- transition >=6) and previous is not head
            node = node->prev;
            int val = node->transition;
            node = node->prev;
            remove_at_end(list);
            remove_at_end(list); //back-track twice

            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, val + 1);    //insert a node with next transition
            insert_at_end(list, new);
            node = node->next;
        }
        else if (node->prev == list->head && node->transition >= 6)
        {   // if the next node of the head undergone all transitions from 0 to 5 (ie- transition >=6)
            remove_at_end(list);    // remove node
            remove_at_end(list);    // remove root node 
            flag--;
        }
        else if (node != list->head && (compare_all_nodes(list, node) || compare_nodes(solution, node)))
        {   // if there exists a self-loop or we have reached a valid solution
            int val = node->transition;
            node = node->prev;
            remove_at_end(list);    // back track once

            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, val + 1);
            insert_at_end(list, new);   // insert node wit next transition.
            node = node->next;
        }
        else
        {
            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, 0);
            insert_at_end(list, new);   // else keep proceeding by inserting node with 0th transition.
            node = node->next;
        }
    }
    free(list);
    free(solution);
    printf("%d\n", count);
}