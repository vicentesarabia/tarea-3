#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "treemap.h"
#include <ctype.h>

typedef struct
{
    void * word;
    int cont;
}Palabras;

typedef struct 
{
    List* titulo;
    char* id;
    Palabras frecuencia[10];
    long cantidaPala;
    long caracteres;
    Map* palabras;

}libro;


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



int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

Map * procesarArchivo(char* token)
{
    libro * librosPro=(libro*)malloc(sizeof(libro));
    librosPro->cantidaPala=0;
    Map * mapa = createMap(stringEqual);
    FILE *f;
    long auxtitle;
    f=fopen(token,"rt");
    char* word=next_word(f);
    for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
    word = quitar_caracteres(word, ".,:_[]()!?\";");
    //Palabras * pal = (Palabras *) malloc (sizeof(Palabras));
    while(word){
        if(strcmp(word,"title")==0)
        {
            auxtitle=ftell(f);

        }

        Palabras * search = searchMap(mapa, word);
        if (search == NULL)
        {
            Palabras * pal = (Palabras *) malloc (sizeof(Palabras));
        
            pal->cont = 1;
            pal->word = strdup(word);
            insertMap(mapa, word, pal);
        }
        else
        {
        
            search->cont++;
        }
        word=next_word(f);
        if (word){
            for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
            word = quitar_caracteres(word, ".,:_[]()!?\";");
        }
    }

    Palabras * pos = firstMap(mapa);
    for(int i=0;i<10;i++)
    {
        librosPro->frecuencia[i].cont=0;
    }
    while (pos != NULL)
    {
        for(int i=0;i<10;i++){
            
            if(librosPro->frecuencia[i].cont<pos->cont){
                librosPro->frecuencia[i].cont=pos->cont;
                librosPro->frecuencia[i].word=strdup(pos->word);
                break;
            }
        }
        

        //printf("%s: %d\n", pos->word, pos->cont);
        librosPro->cantidaPala+=pos->cont;
        pos = nextMap(mapa);
    }
    fseek(f,0,SEEK_END);
    librosPro->caracteres=ftell(f);
    printf("%ld\n",librosPro->caracteres);
    printf("%ld\n",librosPro->cantidaPala);
    fseek(f,auxtitle,SEEK_CUR);
    fgets(word,1023,f);
    printf("%ld\n",auxtitle);
    for(int i=0;i<10;i++)
    {
        printf("%ld , %s\n",librosPro->frecuencia[i].cont, librosPro->frecuencia[i].word);

    }
    token=quitar_caracteres(token,".txt");
    librosPro->id=token;
    printf("%s\n",librosPro->id);
    
}

void eleccionFunciones(int *funcion)
{
    printf("seleccione 0 para salir\n");
    printf("Seleccione 1 para importar un archivo\n");//funcion esencial para la funcionalidad del codigo, listo
    printf("Seleccione 2 para exportar a un archivo\n");
    printf("Seleccione 3 si quiere agregar un producto a la lista\n");
    printf("Seleccione 4 si quiere buscar un producto por su tipo\n");
    printf("Seleccione 5 si quiere buscar por marca del/los productos\n");
    printf("Seleccione 6 si quiere buscar un producto por su nombre\n");
    printf("Seleccione 7 si quiere mostrar todos los productos\n");
    scanf("%i",funcion);//funcion que quiere ingresar
}

int main()
{
    int funcion;
    int a;
    char idtexto[100];
    eleccionFunciones(&funcion);
    while (funcion != 0)//ciclo repetitivo que permite seleccionar la funcion que quiere utilizar y con un 0 salir de estas 
    {
        //switch que permite seleccionar la funcion segun el numero ingresado
        switch (funcion)
        {
            case 1:
            a=1;
            printf("ingrese el id del texto a procesar, ingrese 0 ara fnalizar la operacion: ");
            getchar();
            fgets(idtexto,100,stdin);
            char* token=strtok(idtexto,"\n");
            char* aux=token;
   
            while(token!=0)
            {  
                procesarArchivo(token);
                fgets(idtexto,100,stdin);
                getchar();
                token=strtok(idtexto,"\n");
            }
            break;

            case 2:
            //mostrarDoc(libros)
            break;
            
            case 3:
            //mostrarLibros(libros)
            break;

            case 4:
            //mostrarFrecuencia(libros)
            break;

            case 5:
            //mostrarRelevancia(libros)
            break;

            case 6:
            //buscarPalabra
            break;

            case 7:
            //mostrarContex(libros)
            break;

            default:
            printf("Numero ingresado no valido. Ingrese un numero valido\n");
            break;
            return 0;
        }
        eleccionFunciones(&funcion);
        if(funcion == 0)
        {
            printf("Ha finalizado el proceso.");
        }
    }
}
