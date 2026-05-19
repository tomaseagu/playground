#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 100 millones de elementos
#define TAMANO 100000000

int *datos;

// Caso 1: Pasado por puntero (Referencia). Modifica la memoria en cada vuelta.
// Usamos un atributo especial para prohibirle al compilador optimizar esta función
__attribute__((noinline, optimize("O0")))
void sumarConReferencia(int *total) {
    *total = 0;
    for (int i = 0; i < TAMANO; i++) {
        *total += datos[i]; // Obligado a escribir en memoria RAM/Caché
    }
}

// Caso 2: Variable Local. Todo ocurre en los registros de la CPU.
__attribute__((noinline, optimize("O0")))
void sumarConLocal(int *total) {
    int suma_local = 0; // Se asigna a un registro del procesador
    for (int i = 0; i < TAMANO; i++) {
        suma_local += datos[i]; // Ultra rápido en el silicio
    }
    *total = suma_local; // Una sola escritura al final
}

int main() {
    // Reservamos memoria para el arreglo gigante
    datos = (int *)malloc(TAMANO * sizeof(int));
    if (datos == NULL) {
        printf("No hay suficiente memoria.\n");
        return 1;
    }

    // Llenamos el arreglo con unos
    for (int i = 0; i < TAMANO; i++) {
        datos[i] = 1;
    }

    printf("--- Iniciando Pruebas en C (Sin Optimización) ---\n");

    clock_t inicio, fin;
    double tiempo;
    int resultado = 0;

    // ==========================================================
    // PRUEBA 1: POR REFERENCIA / PUNTERO
    // ==========================================================
    inicio = clock();
    sumarConReferencia(&resultado);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Caso 1 (Referencia): %.2f ms. Resultado = %d\n", tiempo, resultado);

    // ==========================================================
    // PRUEBA 2: VARIABLE LOCAL
    // ==========================================================
    resultado = 0;
    inicio = clock();
    sumarConLocal(&resultado);
    fin = clock();
    tiempo = ((double)(fin - inicio)) / CLOCKS_PER_SEC * 1000;
    printf("Caso 2 (Local)     : %.2f ms. Resultado = %d\n", tiempo, resultado);

    free(datos);
    return 0;
}