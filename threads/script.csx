using System;
using System.IO;
using System.Threading;
// dotnet script script.csx


// 1. Inicializamos el semáforo y la ruta del archivo a nivel de script
var semaforo = new SemaphoreSlim(1, 1);
string rutaArchivo = "log_hilos.txt";

Console.WriteLine("Iniciando simulación de escritura concurrente desde dotnet-script...\n");

// Limpiamos el archivo si ya existe
if (File.Exists(rutaArchivo)) File.Delete(rutaArchivo);

// Creamos un arreglo para guardar nuestros hilos
Thread[] hilos = new Thread[5];

// Arrancamos 5 hilos
for (int i = 0; i < 5; i++)
{
    int idHilo = i + 1; // Copia local para el closure
    hilos[i] = new Thread(() => EscribirEnArchivo(idHilo));
    hilos[i].Name = $"Hilo {idHilo}";
    hilos[i].Start();
}

// Esperamos a que todos los hilos terminen su trabajo
foreach (Thread hilo in hilos)
{
    hilo.Join();
}

Console.WriteLine("\nPrograma finalizado. Todos los hilos terminaron.");
Console.WriteLine("Contenido del archivo:");
Console.WriteLine(File.ReadAllText(rutaArchivo));

// Definimos la función que usarán los hilos abajo en el script
void EscribirEnArchivo(int id)
{
    Console.WriteLine($"[ESPERA] El Hilo {id} quiere acceder al archivo...");

    // 2. Solicitamos acceso al semáforo
    semaforo.Wait();

    try
    {
        // === SECCIÓN CRÍTICA ===
        Console.WriteLine($"[ENTRADA] El Hilo {id} tiene el control y está escribiendo.");
        
        Thread.Sleep(500); 
        
        string mensaje = $"Registro del Hilo {id} escrito a las {DateTime.Now:HH:mm:ss.fff}\n";
        File.AppendAllText(rutaArchivo, mensaje);
        // =======================
    }
    catch (Exception ex)
    {
        Console.WriteLine($"Error en el Hilo {id}: {ex.Message}");
    }
    finally
    {
        // 3. Liberamos el semáforo
        Console.WriteLine($"[SALIDA] El Hilo {id} terminó y liberó el semáforo.\n");
        semaforo.Release();
    }
}