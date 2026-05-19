using System;
using System.Diagnostics;
using System.Runtime.CompilerServices;

// Tamaño del arreglo: 100 millones de elementos
const int Tamano = 100_000_000;
int[] datos = new int[Tamano];

// Llenamos el arreglo con unos (1)
Array.Fill(datos, 1);

Console.WriteLine("--- Iniciando Pruebas en modo Script ---");

// ==========================================================
// PRUEBA 1: PASADO POR REFERENCIA (Lento)
// ==========================================================
int totalReferencia = 0;
Stopwatch sw1 = Stopwatch.StartNew();

SumarConReferencia(ref totalReferencia);

sw1.Stop();
Console.WriteLine($"Caso 1 (Referencia): {sw1.ElapsedMilliseconds} ms. Resultado = {totalReferencia}");

// ==========================================================
// PRUEBA 2: VARIABLE LOCAL (Rápido)
// ==========================================================
int totalLocal = 0;
Stopwatch sw2 = Stopwatch.StartNew();

SumarConLocal(ref totalLocal);

sw2.Stop();
Console.WriteLine($"Caso 2 (Local)     : {sw2.ElapsedMilliseconds} ms. Resultado = {totalLocal}");


// Obligamos al JIT a NO optimizar esta función.
// Esto lo forzará a ir a la memoria RAM/Caché en cada iteración.
[MethodImpl(MethodImplOptions.NoOptimization)]
void SumarConReferencia(ref int total)
{
    total = 0;
    for (int i = 0; i < datos.Length; i++)
    {
        total += datos[i]; 
    }
}

// También desactivamos optimización aquí para que la comparación de los bucles sea justa,
// pero verás cómo el diseño de usar la variable local sigue siendo superior sin ayuda del JIT.
[MethodImpl(MethodImplOptions.NoOptimization)]
void SumarConLocal(ref int total)
{
    int sumaLocal = 0;
    for (int i = 0; i < datos.Length; i++)
    {
        sumaLocal += datos[i];
    }
    total = sumaLocal;
}