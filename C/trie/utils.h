#ifndef UTILS_H
#define UTILS_H

typedef struct c_string *string_type;
struct c_string {
    /*
        fields:
            ptr (ptr): pointer to string
            len (int): string length
    */

    char *ptr;
    int len;
};

string_type new_string(char *);
string_type copy_string(string_type);
void append_char(string_type, char);
void pop_char(string_type);
void append_str(string_type, string_type);

typedef struct string_list *list_type;
struct string_list {
    /*
        fields:
            data (ptr): pointer to string_type (array of pointers)
            size (int): array length
    */

    string_type *data;
    int size;
};

list_type new_list();
void append_list(list_type, string_type);
#endif
