#ifndef TRIE_H
#define TRIE_H

#include "utils.h"
#define CHAR_SIZE 128


typedef struct trie_node *node_type;
struct trie_node {
    /*
        fields:
            key (ptr): pointer to string value assocaited with the node
            children (ptr): pointer to the array of child nodes
            count (int): number of words that correspond to sequence of edges
             from root to current node 
    */

    node_type *children;
    int count;
};

typedef struct trie *trie_type;
struct trie {
    /*
        fields:
            root (ptr): pointer to root of trie
    */
    node_type root;
};

node_type new_node();
trie_type new_trie();
void insert_word(trie_type, string_type);
int count_word(trie_type, string_type);

node_type prefix_node(trie_type, string_type);
list_type words_under_node(node_type);
list_type words_with_prefix(trie_type, string_type);
list_type keys(trie_type);

#endif
