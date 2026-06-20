#include <stdio.h>
#include <stdlib.h>

void funcion_demostracion(int conteo) {
    // Variable local (vive en el Stack)
    int variable_stack_local = 99;
    
    printf("   En llamada recursiva %d:\n", conteo);
    printf("      Dirección de variable_stack_local: %p\n", (void*)&variable_stack_local);
}

int main() {
    printf("=== DEMOSTRACIÓN DE STACK VS HEAP ===\n\n");

    // ---------------------------------------------------------
    // 1. EL STACK (Variables locales y estáticas)
    // ---------------------------------------------------------
    printf("--- 1. El Stack (Crece hacia abajo) ---\n");
    int stack_var1 = 10;
    int stack_var2 = 20;
    
    printf("Dirección de stack_var1: %p\n", (void*)&stack_var1);
    printf("Dirección de stack_var2: %p\n", (void*)&stack_var2);
    
    // Demostración de cómo se apilan las funciones en el Stack
    funcion_demostracion(1);
    funcion_demostracion(2);
    
    printf("\n");

    // ---------------------------------------------------------
    // 2. EL HEAP (Memoria dinámica)
    // ---------------------------------------------------------
    printf("--- 2. El Heap (Asignación dinámica) ---\n");
    
    // Solicitamos memoria al sistema usando malloc()
    int *heap_ptr1 = (int*)malloc(sizeof(int));
    int *heap_ptr2 = (int*)malloc(sizeof(int));
    
    if (heap_ptr1 == NULL || heap_ptr2 == NULL) {
        printf("Error al asignar memoria en el Heap.\n");
        return 1;
    }

    *heap_ptr1 = 100;
    *heap_ptr2 = 200;

    // Ojo: Imprimimos la dirección a la que APUNTAN (donde vive el dato en el Heap)
    printf("Dirección del dato en heap_ptr1 (Heap): %p\n", (void*)heap_ptr1);
    printf("Dirección del dato en heap_ptr2 (Heap): %p\n", (void*)heap_ptr2);
    
    // Pero el puntero en sí mismo... ¡vive en el Stack!
    printf("Dirección del puntero heap_ptr1 en sí mismo (Stack): %p\n", (void*)&heap_ptr1);

    // ---------------------------------------------------------
    // 3. LIMPIEZA (Fundamental en el Heap)
    // ---------------------------------------------------------
    // El Stack se limpia solo al salir de la función. El Heap DEBÉS liberarlo vos.
    free(heap_ptr1);
    free(heap_ptr2);
    
    printf("\nMemoria del Heap liberada correctamente.\n");

    return 0;
}
