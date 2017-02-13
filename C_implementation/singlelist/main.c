#include <stdio.h>
#include "linkedlist.h"

int main(void) {
    /*
        Unit test: corner cases
    */
    push(NULL, NULL);
    pop(NULL);
    find(NULL, 1);
    remove_node(NULL, NULL);
    remove_list(NULL);

    single_list list = new_list();
    remove_node(list, NULL);
    push(list, NULL);
        

    /*
        Regular test cases
    */
    push(list, new_node(10));
    push(list, new_node(1));
    push(list, new_node(5));

    single_node node = list->head;
    while (node != NULL) {
        printf("%d\n", node->val);
        node = node->next;
    }

    node = find(list, 1);
    printf("%d\n", node->val);
    pop(list);

    push(list, new_node(3));
    node = list->head;
    while (node != NULL) {
        printf("%d\n", node->val);
        node = node->next;
    }

    remove_node(list, list->head->next->next);

    node = list->head;
    while (node != NULL) {
        printf("%d\n", node->val);
        node = node->next;
    }
    
    remove_list(list);
}
