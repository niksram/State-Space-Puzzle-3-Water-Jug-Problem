#include "A3_header_PES1201801972.h"

int main()
{
    int mat[3][3];
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            scanf("%d",&mat[i][j]);
        }
    }
    Node *solution = create_node(-1, mat[2][0], mat[2][1], mat[2][2], mat[0][0], mat[0][1], mat[0][2]); // reference solution node
    List *list = (List *)malloc(sizeof(List));
    list_init(list); //initialising the doubly linked list
    Node *node = create_node(-1, mat[1][0], mat[1][1], mat[1][2], mat[0][0], mat[0][1], mat[0][2]);
    insert_at_end(list, node); //inserting root node, Transition arbitrarily set to -1
    int count = 0;             // counter to count the number of valid solutions
    int flag = 1;              // the flag based on which the main while loop runs
    if (compare_nodes(list->head, solution))
    { // if the root is the same as the solution state, the solution is the root itself
        display(list);  //this particular case is included outside the while loop as-
        printf("\n");   //- the while loop doesn't perform the travdrsal condition on the root
        count++;
        flag--; // no ned to proceed furthur, hence flag is made 0.
    }
    while (flag)
    {
        if (compare_nodes(solution, node)) // if the solution exists, then display
        {
            display(list);
            printf("\n");
            count++;    //counter increment to count the valid solution
        }

        if (node->prev && node->prev != list->head && node->transition >= 6)
        {   // if a node has undergone all transitions from 0 to 5 (ie- transition >=6) and previous is not head
            node = node->prev;
            int val = node->transition; //note down the previous transition to increment it
            node = node->prev;
            remove_at_end(list);
            remove_at_end(list); //back-track twice

            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, val + 1);    //perform the next transition
            insert_at_end(list, new);   //insert the node 'new' to the list
            node = node->next;
        }
        else if (node->prev == list->head && node->transition >= 6)
        {   // if the next node of the head undergone all transitions from 0 to 5 (ie- transition >=6)
            remove_at_end(list);    // remove node
            remove_at_end(list);    // remove root node 
            flag--; //to exit from the loop
        }
        else if (node != list->head && (compare_all_nodes(list, node) || compare_nodes(solution, node)))
        {   // if there exists a self-loop or we have reached a valid solution
            int val = node->transition; //note the transition to perform the next transition.
            node = node->prev;
            remove_at_end(list);    // back track once

            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, val + 1);    //perform the nextx transition.
            insert_at_end(list, new);   // insert the new node
            node = node->next;
        }
        else
        {   // else keep proceeding by inserting node with 0th transition below the list
            Node *new = create_node(-1, node->jug[0], node->jug[1], node->jug[2], mat[0][0], mat[0][1], mat[0][2]);
            transition_func(node, new, 0);
            insert_at_end(list, new);   
            node = node->next;
        }
    }
    free(list);//freeing the list
    free(solution);//freeing the solution node
    printf("%d\n", count);
}