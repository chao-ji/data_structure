#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct single_linked_node *single_node;
struct single_linked_node {
    /*
        fields:
            val (int): holds data
            next (ptr): pointer to next node
    */
    int val;
    single_node next;
};

typedef struct single_linked_list *single_list;
struct single_linked_list {
    /*
        fields:
            head (ptr): pointer to head of list
    */
    single_node head;
};

single_node new_node (int);
single_list new_list (void);
void push (single_list, single_node);
single_node pop (single_list);
single_node find(single_list, int);
void remove_node(single_list, single_node);
void remove_list(single_list);

#endif
