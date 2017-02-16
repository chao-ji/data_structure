#include <stdlib.h>

#include "trie.h"
#include "utils.h"

node_type new_node() {
    /*
        Create new node of trie_type object

        returns:
            node (node_type): pointer to node_type object
    */

    node_type node = malloc(sizeof *node);

    node->children = calloc(CHAR_SIZE, sizeof(struct trie_node));
    int i = 0;
    for (i = 0; i < CHAR_SIZE; i++) {
        node->children[i] = NULL;
    }

    node->count = 0;

    return node;
}

trie_type new_trie() {
    /*
        Create new trie

        returns:
            trie (trie_type) pointer to trie_type object
    */

    trie_type trie = malloc(sizeof *trie);
    trie->root = new_node();
    return trie;
}

void insert_word(trie_type trie, string_type str) {
    /*
        Insert word to trie

        params:
            trie (trie_type): pointer to trie_type object
            str (string_type): pointer to string_type obejct
    */

    node_type node = trie->root;

    int i = 0;
    for (i = 0; i < str->len; i++) {
        if (node->children[(int) str->ptr[i]] == NULL) {
            node->children[(int) str->ptr[i]] = new_node();
        }
        node = node->children[(int) str->ptr[i]];
    }
    node->count++;
}

int count_word(trie_type trie, string_type str) {
    /*
        Count number of words 

        params:
            trie (trie_type): pointer to trie_type object
            str (string_type): pointer to string_type object to be queried
    */

    node_type node = trie->root;

    int i = 0;
    for (i = 0; i < str->len; i++) {
        if (node->children[(int) str->ptr[i]] == NULL) {
            return 0;
        }
        else {
            node = node->children[(int) str->ptr[i]];
        }
    }

    return node->count;
}

node_type prefix_node(trie_type trie, string_type pref) {
    /*
        Find the node that corresponds to the prefix

        params:
            trie (trie_type): pointer to trie_type object
            pref (string_type): pointer to string_type object that corresponds
            to prefix string
        returns:
            node (node_type): pointer to node_type
    */

    node_type node = trie->root;

    int i = 0;
    for (i = 0; i < pref->len; i++) {
        if (node->children[(int) pref->ptr[i]] == NULL) {
            return NULL;
        }
        else {
            node = node->children[(int) pref->ptr[i]];
        }
    }

    return node;
}

list_type words_under_node(node_type node) {
    /*
        Find words that corresponds to nodes in the tree rooted at `node`
        params:
            node (node_type): pointer to node_type object
        returns:
            list (list_type): pointer to list_type object that contains string_type objects
    */

    list_type list = new_list();
    int i = 0;
    for (i = 0; i < CHAR_SIZE; i++) {

        if (node->children[i] != NULL) {
            string_type str = new_string(NULL);
            append_char(str, (char) i);

            list_type new_list = words_under_node(node->children[i]);

            int j = 0;
            for (j = 0; j < new_list->size; j++) {
                string_type new_str = copy_string(str);
                append_str(new_str, new_list->data[j]);

                append_list(list, new_str);
            }
        }
    }

    if (node->count > 0) {
        append_list(list, new_string(""));
    }

    return list;
}

list_type words_with_prefix(trie_type trie, string_type str) {
    /*
        Find words with given prefix string

        params:
            trie (trie_type): pointer to trie_type object
            str (string_type): pointer to string_type object
        returns:
            list (list_type): pointer to list_type object that contains string_type objects with common prefix
    */

    node_type node = prefix_node(trie, str);
    list_type list = words_under_node(node);
    int i = 0;
    for (i = 0; i < list->size; i++) {
        string_type new_str = copy_string(str);
        append_str(new_str, list->data[i]);
        list->data[i] = new_str;
    }
    return list;
}

list_type keys(trie_type trie) {
    /*
        Find keys of trie (words with positive counts)

        params:
            trie (trie_type): pointer to trie_type objects
        returns:
            list (list_type): pointer to list_type objects that contains keys
    */
    return words_with_prefix(trie, new_string(""));
}
