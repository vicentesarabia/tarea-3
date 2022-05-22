#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "Map.h"
#include "treemap.h"
#include <ctype.h>

typedef struct
{
    char* palabra;
    long cantidad;

}Mfrecuncia;

typedef struct 
{
    char* titulo;
    char* id;
    Mfrecuncia frecuencia[10];
    long cantidaPala;
    long caracteres;
    Map* palabras;

}libro;





int is_equal_string(void * key1, void * key2) 
{
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

Map * procesarArchivo(Map* libros,char* token)
{
    printf("%s",token);
    char*token2, *aux2;
    char aux[101];
    Mfrecuncia* kekw;
    libro* libroPro=(libro*)malloc(sizeof(libro));
    libroPro->palabras=createMap(is_equal_string);
    FILE* entrada=fopen(token,"rt");
    while(fgets(aux,200,entrada)){
        token2=strtok(aux,"\"");
        (*token2)=(tolower(*token2));
        aux2=token2;
        while(token2!=NULL)
        {
            kekw->palabra=strdup(token2);
            kekw->cantidad=1;
            
            Mfrecuncia *auxbuscar=searchMap(libroPro->palabras,token2);
            if(auxbuscar==NULL)
            {
                insertMap(libroPro->palabras,token2,kekw);
            }
            else{
                auxbuscar->cantidad++;
            }
            token2=strtok(aux,"\"");
            (*token2)=tolower(*token2);
            if(aux2==token2)break;
        }

        
    }
    Mfrecuncia *auxbuscar=firstMap(libroPro->palabras);
    printf("%s , %ld\n",auxbuscar->palabra,auxbuscar->cantidad);




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
    Map*libros=createMap(is_equal_string);
    char idtexto[100];
    eleccionFunciones(&funcion);
    while (funcion != 0)//ciclo repetitivo que permite seleccionar la funcion que quiere utilizar y con un 0 salir de estas 
    {
        //switch que permite seleccionar la funcion segun el numero ingresado
        switch (funcion)
        {
            case 1:
            printf("ingrese el/los id del texto a procesar: ");
            getchar();
            fgets(idtexto,100,stdin);
            char* token=strtok(idtexto,"\"");
            char* aux=token;
            while(token!=NULL)
            {  
                procesarArchivo(libros,token);
                token=strtok(idtexto,"\"");
                if(aux==token)break;
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
