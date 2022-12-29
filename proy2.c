#include <stdio.h>
#include <stdlib.h>
#include "lista_xor.h"

int main(){
    lista *prueba = nueva_lista();

    inicializar_lista(prueba);
    insertar_principio(prueba, 1);
    insertar_principio(prueba, 2);
    insertar_principio(prueba, 3);
    insertar_principio(prueba, 4);

    listar_inicio_fin(prueba);
    eliminar_lista(prueba);

    return 1;

}
