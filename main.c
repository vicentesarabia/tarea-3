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
    float cont;
}Palabras;

typedef struct 
{
    List* titulo;
    char* id;
    char* idtxt;
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
List* obtenertitulo(FILE* f)
{
    char aux[1024];
    char* token,*aux2;
    List* listaux=createList();
    while(fgets(aux,1023,f)!=NULL)
    {
        token=strtok(aux," ");
        if(strcmp(token,"Title:")==0)
        {
            aux2=token;
            while(token!=NULL){
            
                
                
                pushBack(listaux,token);
                token=strtok(NULL," ");
                if(token==aux2)break;
                
                


            }
            popFront(listaux);
            return listaux;
        }

    }
    return NULL;
}

libro * procesarArchivo(char* token)
{
    libro * librosPro=(libro*)malloc(sizeof(libro));
    librosPro->cantidaPala=0;
    Map * mapa = createMap(stringEqual);
    FILE *f;
    f=fopen(token,"rt");
    char* word=next_word(f);
    for (int i = 0; word[i]; i++) word[i] = tolower(word[i]);
    word = quitar_caracteres(word, ".,:_[]()!?\";");
    //Palabras * pal = (Palabras *) malloc (sizeof(Palabras));
    while(word){

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
        //printf("%s: %d\n", pos->word, pos->cont);
        librosPro->cantidaPala+=pos->cont;
        pos = nextMap(mapa);
    }
    pos = firstMap(mapa);
    while (pos != NULL){

        for(int i=0;i<10;i++){
           
            if(librosPro->frecuencia[i].cont<pos->cont/librosPro->cantidaPala){
                librosPro->frecuencia[i].cont=pos->cont/librosPro->cantidaPala;
                librosPro->frecuencia[i].word=strdup(pos->word);
                break;
            }
        }
        pos = nextMap(mapa);
    }
    librosPro->palabras=mapa;
    fseek(f,0,SEEK_END);

    librosPro->caracteres=ftell(f);
    fseek(f,0,SEEK_SET);
    librosPro->titulo=obtenertitulo(f);
    librosPro->idtxt=strdup(token);
    token=quitar_caracteres(token,".txt");
    librosPro->id=strdup(token);
    char* auxtitlea=firstList(librosPro->titulo);
        while(auxtitlea!=NULL)
        {
            printf("%s ",auxtitlea);
            auxtitlea=nextList(librosPro->titulo);
        }
    return librosPro;
    
}
void mostrarFrecuencia(TreeMap *mapa , char id[])
{

    Pair*aux=searchTreeMap(mapa,id);
    libro *libroaux=aux->value;
    if(libroaux==NULL)
    {
        printf("no esta el libro buscado\n");
        return;
    }
    for(int i=0;i<10;i++)
    {
        printf("%.4f , %s\n",libroaux->frecuencia[i].cont, libroaux->frecuencia[i].word);

    }

}
void mostrarDoc(TreeMap* mapa)
{
    Pair* pairaux=firstTreeMap(mapa);
    libro* libroaux;

    while(pairaux!=NULL)
    {
        libroaux=pairaux->value;
        printf("titulo: ");
        char* aux=firstList(libroaux->titulo);
        while(aux!=NULL)
        {
            printf("%s ",aux);//no entendemos pq se printea mal pq en el procesar archivo si se muestra bien
            aux=nextList(libroaux->titulo);
        }
        printf("\n");
        printf("id: %s\n",libroaux->id);
        printf("cantidad de palabras: %ld\n",libroaux->cantidaPala);
        printf("cantidad de caracteres: %ld\n",libroaux->caracteres);
        printf("a");
        pairaux=nextTreeMap(mapa);
        printf("2a");


    }
}
void mostrarContex(TreeMap*libros,char* busq){
    char titulo[1024];
    char* aux;
    char* token;
    printf("ingrese el titulo del libro");
    getchar();
    fgets(titulo,1023,stdin);
    Pair* auxpair=searchTreeMap(libros,titulo);
    libro* libroaux=auxpair->value;
    aux=strdup(libroaux->idtxt);
    FILE* entrada;
    entrada=fopen(aux,"rt");
    while(fgets(aux,1023,entrada)!=NULL)
    {
        
        token=strtok(aux," ");
        while(token!=NULL)
        {
            if(strcmp(token,busq)==0)
            {
                printf("%s\n",aux);

            }
            token=strtok(NULL," ");
        }
        

    }







}
void eleccionFunciones(int *funcion)
{
    printf("seleccione 0 para salir\n");
    printf("Seleccione 1 para importar un documento\n");//funcion esencial para la funcionalidad del codigo, listo
    printf("Seleccione 2 para mostrar documentos ingresados\n");
    printf("Seleccione 3 para buscar libro por su titulo\n");
    printf("Seleccione 4 para mostrar frecuenca de un libro\n");
    printf("Seleccione 5 para mostrar las palabras relevantes de un libro\n");
    printf("Seleccione 6 para buscar que libros contienen la palabra a ingresar\n");
    printf("Seleccione 7 para mostrar la palabra que se ingrese en su contexto\n");
    scanf("%i",funcion);//funcion que quiere ingresar
}

int main()
{
    int funcion;
    int a;
    
    char idtexto[101];
    libro * libromain;
    char id[101];
    TreeMap* mapadelibros=createTreeMap(stringEqual);
    TreeMap* iddelibros=createTreeMap(stringEqual);
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
            
            libromain=procesarArchivo(token);
            insertTreeMap(iddelibros,libromain->id,libromain);
            //insertTreeMap(mapadelibros,libromain->titulo,libromain);
        
            
            
            break;

            case 2:
            mostrarDoc(iddelibros);
            break;
            
            case 3:
            //mostrarLibros(libros)
            break;

            case 4:
            
            printf("ingrese la id del libro para ver su frecuencia\n");
            getchar();
            fgets(id,100,stdin);
            mostrarFrecuencia(iddelibros,id);
            break;

            case 5:
            //mostrarRelevancia(libros)
            break;

            case 6:
            //buscarPalabra
            break;

            case 7:
            printf("ingrese la palabra a buscar en su contexto\n");
            getchar();
            fgets(id,100,stdin);
            mostrarContex(iddelibros,id);
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
