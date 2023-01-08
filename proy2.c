#include <stdio.h>
#include <stdlib.h>
#include "lista_xor.h"

int pedir_dato(){
    int valor;
    printf("Ingrese el valor: ");
    scanf("%d",&valor);
    fflush(stdin);
    return valor;

}

int main(){
    int opc;
    lista *listap = nueva_lista();
    int elemento;

    do {
        system("clear");
        printf("--LISTAS XOR--\n\n 1.  Inicializar lista\n 2.  Revisar si la lista esta vacia\n 3.  Insertar elemento al principio\n 4.  Insertar elemento al final\n 5.  Insertar elemento ordenado\n 6.  Buscar elemento\n 7.  Sacar primer elemento\n 8.  Sacar ultimo elemento\n 9.  Sacar primera ocurrencia de un elemento\n 10. Listar de inicio a fin\n 11. Listar de fin a inicio\n 12. Cantidad de elementos\n 13. Salir\n Opcion: ");
        scanf("%d",&opc);
        fflush(stdin);

        switch (opc){
            case 1:
                inicializar_lista(listap);
                printf("Lista inicializada\n");
                getchar();
                getchar();
                break;

            case 2:
                if (vacia(listap))
                    printf("La lista no esta vacia\n");
                else
                    printf("La lista esta vacia\n");
                getchar();
                getchar();
                break;

            case 3:
                elemento = pedir_dato();
                insertar_principio(listap,elemento);
                break;

            case 4:
                elemento = pedir_dato();
                insertar_final(listap,elemento);
                break;

            case 5:
                elemento = pedir_dato();
                insertar_ordenado(listap,elemento);
                break;

            case 6:
                elemento = pedir_dato();
                if (buscar(listap,elemento))
                    printf("Si esta en la lista\n");
                else
                    printf("No esta en la lista\n");
                getchar();
                getchar();
                break;

            case 7:
                sacar_principio(listap,&elemento);
                printf("El elemento sacado fue %i \n",elemento);
                getchar();
                getchar();
                break;

            case 8:
                sacar_final(listap,&elemento);
                printf("El elemento sacado fue %i \n",elemento);
                getchar();
                getchar();
                break;

            case 9:
                elemento = pedir_dato();
                if (sacar_primera_ocurrencia(listap,elemento))
                    printf("Se saco la primera ocurrencia de %i\n",elemento);
                else
                    printf("%i no aparece en la lista\n",elemento);
                getchar();
                getchar();
                break;


            case 10:
                listar_inicio_fin(listap);
                getchar();
                getchar();
                break;

            case 11:
                listar_fin_inicio(listap);
                getchar();
                getchar();
                break;

            case 12:
                printf("Cantidad de elementos: %i",total_elementos(listap));
                getchar();
                getchar();
                break;

        }
    } while (opc != 13);
    eliminar_lista(listap);

    return 1;

}
