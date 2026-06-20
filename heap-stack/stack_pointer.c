#include <stdio.h>
#include <stdint.h>

int main() {
    printf("=== HACKEANDO EL STACK POINTER (RSP) ===\n\n");

    // 1. Creamos una variable en el Stack que va a ser nuestra "cima" actual
    // Al ser la última variable declarada, el RSP debería andar muy cerca de ella.
    uint64_t valor_cima_secreto = 123456789; 

    // Variables para guardar nuestras lecturas
    uint64_t *rsp_value;
    uint64_t contenido_cima;

    // 2. MAGIA DE BAJO NIVEL: Le pedimos a la CPU el valor del registro RSP
    // "mov %%rsp, %0" significa: saca el valor de RSP y ponelo en la variable rsp_value
    __asm__("mov %%rsp, %0" : "=r"(rsp_value));

    printf("1. Direccion actual del Stack Pointer (RSP): %p\n", (void*)rsp_value);

    // 3. IR A BUSCAR el dato usando ese Stack Pointer (Desreferenciarlo)
    // Como rsp_value contiene una dirección de memoria, usamos '*' para ver qué hay adentro.
    contenido_cima = *rsp_value;

    printf("2. El valor guardado FISICAMENTE en la direccion a la que apunta el RSP es: %llu\n", 
           (unsigned long long)contenido_cima);

    // 4. Verificación de control:
    printf("\n--- Verificación ---\n");
    printf("Dirección de 'valor_cima_secreto' en C: %p\n", (void*)&valor_cima_secreto);
    printf("Valor real de 'valor_cima_secreto':      %llu\n", (unsigned long long)valor_cima_secreto);

    return 0;
}
