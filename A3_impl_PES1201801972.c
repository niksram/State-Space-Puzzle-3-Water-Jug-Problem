#include "A3_header_PES1201801972.h"
void XtoY(Node *, Node *, int, int);

void list_init(List *list)
{
    list->head = NULL;
    list->tail = NULL;
}

Node *create_node(int transition, int j0, int j1, int j2, int c0, int c1, int c2)
{
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

void insert_at_end(List *list, Node *node)
{
    //empty list
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else // non-empty list
    {
        node->prev = list->tail;
        node->prev->next = node;
        list->tail = node;
    }
}

void remove_at_end(List *list)
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

void display(List *list)
{
    Node *node = list->head;
    while (node)
    {
        printf("%d %d %d    %d\n", node->jug[0], node->jug[1], node->jug[2], node->transition);
        node = node->next;
    }
}

int compare_nodes(Node *node1, Node *node2)
{
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
{
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
{
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
{
    if (source->jug[sj] <= source->cap[dj] - source->jug[dj])
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

void state_space_search(int (*mat)[3])
{
    Node *solution = create_node(-1, mat[2][0], mat[2][1], mat[2][2], mat[0][0], mat[0][1], mat[0][2]);
    List *list = (List *)malloc(sizeof(List));
    list_init(list);
    Node *node = create_node(-1, mat[1][0], mat[1][1], mat[1][2], mat[0][0], mat[0][1], mat[0][2]);
    insert_at_end(list, node);
    int count=0;
    while (1)
    {
        if (compare_nodes(solution, node))
        {
            display(list);
            printf("\n");
            count++;
        }

        if (node->prev && node->prev != list->head && node->transition == 6)
        {
            node = node->prev;
            int val = node->transition;
            node = node->prev;
            remove_at_end(list);
            remove_at_end(list);
            if (val <= 6)
            {
                Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
                if (val == 6)
                    val--;
                transition_func(node, new, val + 1);
                insert_at_end(list, new);
                node = node->next;
            }
        }
        else if (node->prev == list->head && node->transition == 6)
        {
            remove_at_end(list);
            break;
        }
        else if (node != list->head && (compare_all_nodes(list, node) || compare_nodes(solution, node)))
        {
            int val = node->transition;
            node = node->prev;
            remove_at_end(list);
            if (val <= 6)
            {
                Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
                if (val == 6)
                    val--;
                transition_func(node, new, val + 1);
                insert_at_end(list, new);
                node = node->next;
            }
        }
        else
        {
            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, 0);
            insert_at_end(list, new);
            node = node->next;
        }
    }
    printf("%d\n",count);
}