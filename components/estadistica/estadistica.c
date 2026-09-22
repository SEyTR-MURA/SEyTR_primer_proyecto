/* estadistica.c - implementacion del componente.
 *
 * Este fichero no sabe nada de la placa: son cuentas sobre un array. Esa es
 * precisamente la gracia de separarlo en un componente, porque se puede leer,
 * probar y reutilizar sin tener el hardware delante.
 */

#include "estadistica.h"

bool estadistica_resumen(const int *lecturas, size_t n,
                         estadistica_resumen_t *destino)
{
    if (lecturas == NULL || destino == NULL || n == 0) {
        return false;
    }

    int minimo = lecturas[0];
    int maximo = lecturas[0];
    long suma = 0;

    for (size_t i = 0; i < n; i++) {
        const int valor = lecturas[i];
        if (valor < minimo) {
            minimo = valor;
        }
        if (valor > maximo) {
            maximo = valor;
        }
        suma += valor;
    }

    destino->n = n;
    destino->minimo = minimo;
    destino->maximo = maximo;
    destino->media = (int)(suma / (long)n);

    return true;
}
