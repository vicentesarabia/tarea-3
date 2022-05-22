#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "Map.h"
#include "treemap.h"

typedef struct
{
    void * word;
    int cont;
}Palabras;


int stringEqual(void * key1, void * key2) {
    const char * A = key1;
    const char * B = key2;
    return strcmp(A, B) == 0;
}

char* next_word (FILE *f) {
    char x[1024];
    /* assumes no word exceeds length of 1023 */
    if (fscanf(f, " %1023s", x) == 1)
        return strdup(x);
    else
        return NULL;
}

int hayQueEliminar(char c, char* string_chars){
    for(int i=0 ; i<strlen(string_chars) ; i++){
        if(string_chars[i]==c) return 1;
    }
    return 0;
}

char* quitar_caracteres(char* string, char* c){
    int i;
    int j;
    for(i=0 ; i < strlen(string) ; i++){
        if(hayQueEliminar(string[i], c)){
            for(j=i ; j<strlen(string)-1 ;j++){
                string[j] = string[j+1];
        }
        string[j]='\0';
        i--;
    }
}

    return string;
}



int main()
{
    Map * mapa = createMap(stringEqual);
    FILE *f;
    f=fopen("67944.txt","rt");
    char* word=next_word(f);
    for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
    word = quitar_caracteres(word, "!?\";");
    //Palabras * pal = (Palabras *) malloc (sizeof(Palabras));
    while(word){
    Palabras * search = searchMap(mapa, word);
    if (search == NULL)
    {
        Palabras * pal = (Palabras *) malloc (sizeof(Palabras));
        printf("no encontrado\n");
        pal->cont = 1;
        pal->word = strdup(word);
        insertMap(mapa, word, pal);
    }
    else
    {
        printf("encontrado\n");
        search->cont++;
    }
    word=next_word(f);
    if (word){
        for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
        word = quitar_caracteres(word, "!?\";");
    }
}
Palabras * pos = firstMap(mapa);
while (pos != NULL)
{
    printf("%s: %d\n", pos->word, pos->cont);
    pos = nextMap(mapa);
}

}