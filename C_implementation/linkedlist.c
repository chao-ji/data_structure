#include <stdlib.h>
#include <stdio.h>
#include "linkedlist.h"

single_node new_node (int val) {
    /*
        Create new node

        params:
            val (int): data associated with node
        returns:
            node (ptr): pointer to the newly allocated node
    */
    single_node node = malloc(sizeof(single_node));
    node->val = val;
    node->next = NULL;
    return node;
}

single_list new_list (void) {
    /*
        Create new list

        returns:
            list (ptr): pointer to the newly allocated list
    */
    single_list list = malloc(sizeof(single_list));
    list->head = NULL;
    return list;
}

void push (single_list list, single_node node) {
    /*
        Append single node `node` to beginning of single list `list`

        params:
            list (ptr): pointer to single list to be appended
            node (ptr): pointer to single node to be appended to `list`
    */
    if (list == NULL || node == NULL) {
        printf("WARNING: list is null or node is null.\n");
        return ;
    }

    node->next = list->head;
    list->head = node;
}

single_node pop(single_list list) {
    /*
        Remove single node from the beginning of single list `list`

        params:
            list (ptr): pointer to single list where the first single node 
                        to be removed
        returns:
            node (ptr): pointer to single node removed
    */
    if (list == NULL || list->head == NULL) {
        printf("WARNING: list is null or empty.\n");
        return NULL;
    }

    else {
        single_node node = list->head;
        list->head = list->head->next;
        return node;
    }
}

single_node find(single_list list, int val) {
    /*
        Find the single node in single list with the corresponding value

        params:
            list (ptr): pointer to the single list
            val (int): the query value

        returns: pointer to the single node with the corresponding value            
    */
    if (list == NULL) {
        printf("WARNING: list is null.\n");
        return NULL;
    }

    single_node node;
    for (node = list->head; node != NULL; node = node->next) {
        if (node->val == val) {
            return node;
        }
    }
    return NULL;
}

void remove_node(single_list list, single_node node) {
    /*
        Remove single node from single list given the node's pointer
        and free its space

        params:
            list (ptr): pointer to single list to be operated on
            node (ptr): pointer to single node to be removed
    */
    if (list == NULL || node == NULL) {
        printf("WARNING: list is null or node is null.\n");
        return ;
    }

    single_node prev;
    if (node == list->head) {
        list->head = node->next;
        free(node);
        return ;
    }
    for (prev = list->head; prev != NULL; prev = prev->next) {
        if (prev->next == node) {
            prev->next = node->next;
            free(node);
            return ;
        } 
    }
}

void remove_list(single_list list) {
    /*
        Remove single list and free its space

        params:
            list (ptr): pointer to single list to be removed
    */
    if (list == NULL) {
        printf("WARNING: list is null.\n");
        return ;
    }

    single_node curr = list->head;
    single_node prev = NULL;
    list->head = NULL;

    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
    free(list);
}
