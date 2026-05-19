using System.Diagnostics;

const int Size = 100_000_000;
int[] data = new int[Size];
Array.Fill(data, 1);

Console.WriteLine("--- START ---");

// ==========================================================
// PRUEBA 1: PASADO POR REFERENCIA (Lento)
// ==========================================================
int totalRef = 0;

var sw1 = Stopwatch.StartNew();

SumWithRef(ref totalRef);

sw1.Stop();

Console.WriteLine($"Caso 1 (Ref): {sw1.ElapsedMilliseconds} ms. Result = {totalRef}");

// ==========================================================
// PRUEBA 2: VARIABLE LOCAL (Rápido)
// ==========================================================
int totalLocal = 0;

Stopwatch sw2 = Stopwatch.StartNew();

SumWithLocal(ref totalLocal);

sw2.Stop();

Console.WriteLine($"Caso 2 (Local): {sw2.ElapsedMilliseconds} ms. Result = {totalLocal}");


void SumWithRef(ref int total)
{
    total = 0;
    for (int i = 0; i < data.Length; i++)
    {
        total += data[i]; 
    }
}

void SumWithLocal(ref int total)
{
    int sumaLocal = 0;
    for (int i = 0; i < data.Length; i++)
    {
        sumaLocal += data[i];
    }
    total = sumaLocal;
}