#include <stdint.h>


//Estructura de los datos

typedef struct Nodo{
        int valor;
        struct Nodo *ptr;
}
nodo;

typedef struct Lista{
        nodo *ini, *fin;
}
lista;

//Macro para desplazar y asignar punteros en la lista

#define XOR(ptr1,ptr2)(nodo *)((uintptr_t)ptr1 ^ (uintptr_t)ptr2)

//Prototipos de funciones basicas

nodo *nuevo_nodo(int e);
lista *nueva_lista();
void inicializar_lista(lista *listp);
int vacia(lista *listp);
void eliminar_lista(lista *listp);

//Prototipo de funciones del TAD

int insertar_principio(lista *listp, int e);
int insertar_final(lista *listp, int e);
int insertar_ordenado(lista *listp, int e);

int buscar(lista *listp, int e);

int sacar_principio(lista *listp, int *e);
int sacar_final(lista *listp, int *e);
int sacar_primera_ocurrencia(lista *listp, int e);

void listar_inicio_fin(lista *listp);
void listar_fin_inicio(lista *listp);

int total_elementos(lista *listp);
