#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trie.h"
#include "utils.h"

int main(void) {
    trie_type trie = new_trie();

    char *text = "it is not news that nathan milstein is a wizard of the violin . certainly not in orchestra hall where he has played countless recitals , and where thursday night he celebrated his 20th season with the chicago symphony orchestra , playing the brahms concerto with his own slashing , demon-ridden cadenza melting into the high , pale , pure and lovely song with which a violinist unlocks the heart of the music , or forever finds it closed . there was about that song something incandescent , for this brahms was milstein at white heat . not the noblest performance we have heard him play , or the most spacious , or even the most eloquent . those would be reserved for the orchestra's great nights when the soloist can surpass himself . this time the orchestra gave him some superb support fired by response to his own high mood . but he had in walter hendl a willing conductor able only up to a point . that is , when mr. milstein thrust straight to the core of the music , sparks flying , bow shredding , violin singing , glittering and sometimes spitting , mr. hendl could go along . but mr. hendl does not go straight to any point . he flounders and lets music sprawl ."; 

    /* tokenize `text` into words */
    char *prev = text;
    while (1) {
        char *next = strchr(prev, ' ');
        if (next == NULL){
            insert_word(trie, new_string(prev));
            break;
        }

        int n = (int) (next - prev);
        char *s = calloc(n, sizeof *s);
        strncpy(s, prev, n);
        insert_word(trie, new_string(s));
        prev = next + 1;   
    }

    /* Do a word-count on list of words */
    list_type list = keys(trie); 
    int i = 0;
    for (i = 0; i < list->size; i++) 
        printf("%s\t%d\n", list->data[i]->ptr, count_word(trie, list->data[i]));
}
