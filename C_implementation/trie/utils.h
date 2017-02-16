#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "utils.h"

/*
  Contains function and struct definitions for general string and list (of strings) operations
*/

string_type new_string(char *str) {
    /*
        Create new string

        params:
            str (ptr): pointer to string
        returns:
            string (string_type): pointer to newly allocated string struct
    */
    string_type string = malloc(sizeof *string);

    if (str == NULL) {
        string->ptr = NULL;
        string->len = 0;
    }
    else {
        string->ptr = strdup(str);
        string->len = (int) strlen(str);
    }
        
    return string; 
}

string_type copy_string(string_type s) {
    /*
        Clone string_type object

        params:
            s (string_type): string_type object to be cloned
        returns:
            s_copy (string_type): pointer to newly allocated string struct
    */

    if (s == NULL) {
        printf("WARNING: string is null.\n");
        return NULL;
    }

    string_type s_copy = new_string(s->ptr);
    
    return s_copy;
}

void append_char(string_type s, char c) {
    /*
        Append char to string object

        params:
            s (string_type): pointer to string_type object
            c (char): character to be appended
    */

    if (s == NULL) {
        printf("WARNING: string is NULL.\n");
        return ;
    }
        
    int len = s->len;

    s->ptr = realloc(s->ptr, len + 2);
    s->ptr[len] = c;
    s->ptr[len + 1] = '\0';

    s->len++;
}

void pop_char(string_type s) {
    /*
        Remove char at the end of string

        params:
            s (string_type): pointer to string_type object
    */

    if (s == NULL || s->ptr == NULL) {
        printf("WARNING: string is NULL of empty.\n");
        return ;
    }

    s->ptr[s->len - 1] = '\0';
    s->len--;

    if (s->len == 0) {
        s->ptr = NULL;
    }    
}

void append_str(string_type s1, string_type s2) {
    /*
        Append another string to the end of this string

        params:
            s1 (string_type): pointer to string_type object
            s2 (string_type): pointer to string_type object to be appended 
    */

    if (s1 == NULL || s2 == NULL || s2->ptr == NULL) {
        if (s1 == NULL || s2 == NULL) {
            printf("WARNING: string s1 or s2 is NULL.\n");
        }
        return ;
    }

    int len = s1->len;

    s1->ptr = realloc(s1->ptr, len + s2->len + 1);
    strcpy(s1->ptr + len, s2->ptr);
  
    s1->len += s2->len; 
}

list_type new_list() {
    /*
        Create new list of string_type objects

        returns:
            list (list_type): pointer to newly allocated list_type object 
    */

    list_type list = malloc(sizeof *list);
    list->data = NULL;
    list->size = 0;
    return list;
}

void append_list(list_type l, string_type s) {
    /*
        Append string_type object to end of list

        params:
            l (list_type): pointer to list_type object
            s (string_type): pointer to string_type object to be appended
    */

    if (l == NULL) {
        printf("WARNING: list is NULL.\n");
        return ;
    }

    int size = l->size;    

    l->data = realloc(l->data, sizeof(*l->data) * (size + 1));
    l->data[size] = s;

    l->size++;
}
