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
    if (!listp->ini)
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
    //si la lista no esta vacia
    else {
        nuevop->ptr = listp->ini;
        listp->ini->ptr = XOR(nuevop,listp->ini->ptr);
        listp->ini = nuevop;
    }
    return 1;
}

//Insertar un nuevo nodo al final de una lista

int insertar_final(lista *listp, int e){
    nodo *nuevop = nuevo_nodo(e);
     //Si hay error creando el nodo
    if (nuevop == NULL)
        return 0;

    //Si la lista esta vacia
    if (listp->ini == NULL){
        listp->ini = nuevop;
        listp->fin = nuevop;
    }
    //si la lista no esta vacia
    else {
        nuevop->ptr = listp->fin;
        listp->fin->ptr = XOR(nuevop,listp->fin->ptr);
        listp->fin = nuevop;
    }
    return 1;

}

//Insertar un nodo de forma ordenada en la lista

int insertar_ordenado(lista *listp, int e){

    //Si la lista esta vacia
    if (listp->ini==NULL){
        insertar_principio(listp,e);
        return 1;
    }

    //Recorrer la lista hasta encontrar la posicion ordenada
    nodo *actual=listp->ini;
    nodo *prev=NULL;
    nodo *sig;

    while(actual!=NULL && actual->valor < e){
        sig = XOR(actual->ptr,prev);
        prev = actual;
        actual = sig;
    }

     //Si es la primera posicion
    if (prev == NULL){
        insertar_principio(listp,e);
        return 1;
     //Si es la ultima posicion
    }else if(actual == NULL){
        insertar_final(listp,e);
        return 1;
     //Se inserta entre el prev y actual
    }else{
       nodo *nuevop=nuevo_nodo(e);
       nuevop->ptr = XOR(prev,actual);
       prev->ptr = XOR(nuevop,XOR(prev->ptr,actual));
       actual->ptr = XOR(nuevop,XOR(actual->ptr,prev));
    }
    return 1;
}

//Sacar el primer elemento y devolver su valor

int sacar_principio(lista *listp, int *e){
    //La lista esta vacia
    if (listp->ini == NULL)
        return 0;
    //Establecer punteros de apoyo
    nodo *primero = listp->ini;
    nodo *segundo = XOR(primero->ptr,NULL);

    //Si hay mas de un elemento modificar el puntero
    if (segundo)
            segundo->ptr = XOR(segundo->ptr,listp->ini);

    //Guardar el elemento en un puntero
    *e = primero->valor;

    listp->ini = segundo;

    //Si solo hay un elemento
    if (listp->fin == primero)
        listp->ini = NULL;

    free(primero);
    return 1;
}

//Sacar el ultimo elemento y devolver su valor

int sacar_final(lista *listp, int *e){
    //La lista esta vacia
    if (listp->ini == NULL)
        return 0;

    nodo *ultimo = listp->fin;
    nodo *penultimo = XOR(ultimo->ptr,NULL);

    //Si hay mas de un elemento modificar el puntero
    if (penultimo)
            penultimo->ptr = XOR(penultimo->ptr,listp->fin);

    //Guardar el valor en un puntero
    *e = ultimo->valor;

    listp->fin = penultimo;

    //Si solo hay un elemento
    if(listp->ini == ultimo)
        listp->ini = NULL;

    free(ultimo);
    return 1;

}

//Sacar primera ocurrencia

int sacar_primera_ocurrencia(lista *listp,int e){
    //Si la lista esta vacia
    if (listp->ini==NULL)
        return 0;

    nodo *actual = listp->ini;
    nodo *prev = NULL;
    nodo *sig;

    while (actual) {
        //Se encontro la primera ocurrencia
        if (actual->valor == e){
            sig = XOR(actual->ptr,prev);

            //Si hay siguiente modificar el puntero
            if (sig)
                sig->ptr = XOR(prev,XOR(sig->ptr,actual));
            //Si no hay siguiente es el ultimo
            else
                listp->fin = prev;

            //Si hay anterior modificar el puntero
            if (prev)
                prev->ptr = XOR(XOR(prev->ptr,actual),sig);
            //Si no hay anterior es el primero
            else
                listp->ini = sig;

            free(actual);
            return 1;
        }
        //Avanzar
        sig = XOR(actual->ptr,prev);
        prev = actual;
        actual = sig;
    }
    return 0;
}



//Buscar si aparece un elemento

int buscar(lista *listp, int e){
    //Si la lista esta vacia el elemento no esta
    if (listp->ini == NULL)
        return 0;

    //Recorrer la lista hasta encontrar la posicion ordenada
    nodo *actual=listp->ini;
    nodo *prev=NULL;
    nodo *sig;

    while(actual!=NULL){
        if(actual->valor == e)
            return 1;
        sig = XOR(actual->ptr,prev);
        prev = actual;
        actual = sig;
    }
    return 0;

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
    printf("\n");

}

//Imprimir la lista de derecha a izquierda

void listar_fin_inicio(lista *listp){
    nodo *actual = listp->fin;
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
    printf("\n");

}

int total_elementos(lista *listp){
    int total = 0;
    //Si la lista esta vacia
    if(listp->ini == NULL)
        return total;

    nodo *actual=listp->ini;
    nodo *prev=NULL;
    nodo *sig;
    //Recorrer la lista y sumar cada iteracion
    while(actual!=NULL){
        sig = XOR(actual->ptr,prev);
        prev = actual;
        actual = sig;
        total++;
    }
    return total;
}


