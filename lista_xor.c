#include <stdio.h>
#include <stdlib.h>
#include "lista_xor.h"

//Crear nodo

nodo *nuevo_nodo(int e){
   nodo *nuevop;

   if( (nuevop = (nodo *)malloc(sizeof(nodo)))==NULL){
        fprintf(stderr, "nuevo_nodo: Error reservando memoria\n");
        exit(1);
   }
   nuevop->ptr = NULL;
   nuevop->valor = e;
   return nuevop;

}

//Crear lista

lista *nueva_lista(){
    lista *nuevop;

   if( (nuevop= (lista *)malloc(sizeof(lista)))==NULL){
        fprintf(stderr, "nueva_lista: Error reservando memoria\n");
        exit(1);
   }

   nuevop->ini = NULL;
   nuevop->fin = NULL;
   return nuevop;
}

//Inicializar lista (vaciar)

void inicializar_lista(lista *listp){
    if (!listp)
        return;

    nodo *actual = listp->ini;
    nodo *prev = NULL;
    nodo *temp;

    while (actual!=NULL){
       temp = actual;
       actual = XOR(actual->ptr, prev);
       prev = temp;
       free(temp);
    }

    listp->ini = listp->fin = NULL;
    return;

}

//Eliminar lista

void eliminar_lista(lista *listp){
    if (!listp)
      return;
    inicializar_lista(listp);
    free(listp);
}

//Revisa si una lista esta vacia

int vacia(lista* listp){
    if (!listp || !listp->ini)
      return 0;
    else
      return 1;
}

//Insertar un nuevo nodo al comienzo de la lista

int insertar_principio(lista *listp, int e){
    nodo *nuevop = nuevo_nodo(e);
     //Si hay error creando el nodo
    if (nuevop == NULL)
        return 0;

    //Si la lista esta vacia
    if (listp->ini == NULL){
        listp->ini = nuevop;
        listp->fin = nuevop;
    }
    //La lista no esta vacia
    else {
        nuevop->ptr = listp->ini;
        listp->ini->ptr = XOR(nuevop,listp->ini->ptr);
        listp->ini = nuevop;
    }
    return 1;
}

//Imprimir la inicia de izquierda a derecha

void listar_inicio_fin(lista *listp){
    nodo *actual = listp->ini;
    nodo *prev = NULL;
    nodo *sig;

    while(actual != NULL){
        printf("%d",actual->valor);
        //Obtener el siguiente nodo
        sig = XOR(actual->ptr,prev);

        //Actualizar el actual y el previo
        prev = actual;
        actual = sig;

        //Imprimir flechita si no es el ultimo elemento
        if (actual !=NULL)
            printf(" <-> ");
    }

}


