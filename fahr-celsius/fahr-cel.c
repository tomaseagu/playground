#include <stdio.h>

/* Imprime la tabla Fahrentheit-Celsius 
 * 	para fhar = 0, 20, ..., 300; version del punto flotante */

int main()
{
    float fahr, celsius;
    int lower, upper, step;

    lower = 0; /* limite inferior tabla de temperaturas */
    upper = 300; /* limite superior */
    step = 20; /* tamano del incremento */

    fahr = lower; /* el int se convierta a float */

    printf("Fahr Celsius\n");

    while (fahr <= upper) 
    {
        celsius = (5.0/9.0) * (fahr - 32.0);

	printf("%3.0f %6.1f\n", fahr, celsius);
	
	fahr = fahr + step;
    }
}










