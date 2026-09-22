/* estadistica.h - resumen de una serie de lecturas enteras.
 *
 * Cabecera publica del componente. Lo que aparece aqui es lo que pueden usar
 * los demas componentes; lo que no aparece, no.
 *
 * Las lecturas son enteros en centimetros a proposito: evitan depender de como
 * este configurado el formato de coma flotante de la biblioteca estandar.
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Resultado de resumir una ventana de lecturas. */
typedef struct {
    size_t n;       /* numero de lecturas resumidas */
    int    minimo;  /* lectura mas pequena, en centimetros */
    int    maximo;  /* lectura mas grande, en centimetros */
    int    media;   /* media truncada, en centimetros */
} estadistica_resumen_t;

/* Resume n lecturas consecutivas a partir de lecturas.
 *
 * Devuelve true si ha podido calcular el resumen, y false si los argumentos no
 * son validos: puntero nulo, n igual a cero o destino nulo. En ese caso no
 * escribe nada en destino.
 */
bool estadistica_resumen(const int *lecturas, size_t n,
                         estadistica_resumen_t *destino);

#ifdef __cplusplus
}
#endif
