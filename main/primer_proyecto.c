/* primer_proyecto.c - SEyTR, Unidad 1.
 *
 * Que hace este programa
 * ----------------------
 * Recorre una serie de lecturas de distancia y va publicando por el monitor un
 * resumen de cada ventana de lecturas: minimo, maximo y media. Si el minimo de
 * una ventana baja del umbral configurado, avisa.
 *
 * Importante: aqui no hay ningun sensor. Las lecturas estan escritas en el
 * propio programa, en el array de mas abajo. Sirven para tener algo que contar
 * mientras se aprende a manejar el proyecto; los sensores llegan en la U2.
 *
 * Todo lo que se puede ajustar sin tocar este fichero esta en la configuracion
 * del proyecto, en el menu "SEyTR - Primer proyecto".
 */

#include <stddef.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_chip_info.h"
#include "esp_log.h"
#include "sdkconfig.h"

#include "estadistica.h"

/* La etiqueta identifica al modulo que traza. Se declara una vez por fichero y
 * es lo que permite despues silenciar unos modulos y dejar hablar a otro. */
static const char *TAG = "principal";

/* -------------------------------------------------------------------------
 * U1-S4: escribe aqui tu nombre, guarda, vuelve a compilar y vuelve a grabar.
 * Es la forma mas corta de comprobar que el codigo que corre en la placa es el
 * tuyo y no el que clonaste.
 * ------------------------------------------------------------------------- */
static const char *AUTOR = "sin personalizar";

/* Lecturas simuladas, en centimetros: un robot que se acerca a un obstaculo.
 * Enteros a proposito, para no depender de como este configurado el formato de
 * coma flotante de la biblioteca estandar. */
static const int lecturas_cm[] = {
    185, 178, 171, 166, 158, 152,
    147, 139, 132, 126, 118, 111,
    104,  97,  89,  83,  74,  68,
     59,  52,  44,  37,  31,  26,
};

static const size_t total_lecturas = sizeof(lecturas_cm) / sizeof(lecturas_cm[0]);

void app_main(void)
{
    ESP_LOGI(TAG, "SEyTR - primer proyecto. Autor: %s", AUTOR);
    ESP_LOGI(TAG, "%u lecturas, ventanas de %d, umbral de aviso %d cm",
             (unsigned)total_lecturas, CONFIG_SEYTR_VENTANA, CONFIG_SEYTR_UMBRAL_CM);
    ESP_LOGW(TAG, "no hay sensor: las lecturas estan escritas en el programa");

    /* Estas dos lineas atan la configuracion con la realidad. El destino sale de
     * CONFIG_IDF_TARGET, que esta fijado en sdkconfig.defaults; los nucleos y la
     * revision los cuenta el propio chip. Si lo que sale por el monitor no es lo
     * que dice la configuracion, se esta grabando otra cosa. Se ve en U1-S5. */
    esp_chip_info_t chip;
    esp_chip_info(&chip);
    ESP_LOGI(TAG, "destino %s, %d nucleo(s), revision de silicio v%u.%u",
             CONFIG_IDF_TARGET, chip.cores,
             (unsigned)(chip.revision / 100), (unsigned)(chip.revision % 100));

    const size_t ventana = (size_t)CONFIG_SEYTR_VENTANA;

    if (ventana > total_lecturas) {
        ESP_LOGE(TAG, "la ventana (%u) es mayor que el numero de lecturas (%u);"
                      " baja el valor en la configuracion del proyecto",
                 (unsigned)ventana, (unsigned)total_lecturas);
        return;
    }

    size_t inicio = 0;
    int numero_de_ventana = 1;

    while (inicio < total_lecturas) {
        size_t disponibles = total_lecturas - inicio;
        size_t n = (disponibles < ventana) ? disponibles : ventana;

        if (n < ventana) {
            ESP_LOGW(TAG, "ultima ventana incompleta: %u lecturas de %u",
                     (unsigned)n, (unsigned)ventana);
        }

        /* Nivel verboso: una linea por lectura. No se ve salvo que se suba el
         * nivel, y por eso conviene que exista. */
        for (size_t i = 0; i < n; i++) {
            ESP_LOGV(TAG, "  lectura %u = %d cm",
                     (unsigned)(inicio + i), lecturas_cm[inicio + i]);
        }

        estadistica_resumen_t resumen;

        if (!estadistica_resumen(&lecturas_cm[inicio], n, &resumen)) {
            ESP_LOGE(TAG, "no se ha podido resumir la ventana %d", numero_de_ventana);
            return;
        }

        ESP_LOGD(TAG, "ventana %d: desde la lectura %u, %u valores",
                 numero_de_ventana, (unsigned)inicio, (unsigned)n);

        ESP_LOGI(TAG, "ventana %d: minimo %d cm, media %d cm, maximo %d cm",
                 numero_de_ventana, resumen.minimo, resumen.media, resumen.maximo);

        if (resumen.minimo < CONFIG_SEYTR_UMBRAL_CM) {
            ESP_LOGW(TAG, "aviso: el minimo (%d cm) baja del umbral (%d cm)",
                     resumen.minimo, CONFIG_SEYTR_UMBRAL_CM);
        }

        inicio += n;
        numero_de_ventana++;

        if (inicio < total_lecturas) {
            vTaskDelay(pdMS_TO_TICKS(CONFIG_SEYTR_PERIODO_MS));
        }
    }

    ESP_LOGI(TAG, "no quedan lecturas");

#ifdef CONFIG_SEYTR_FALLO_PROVOCADO
    ESP_LOGE(TAG, "fallo provocado a proposito: se escribe en una direccion invalida");
    volatile int *direccion_invalida = (volatile int *)0;
    *direccion_invalida = 1;
#endif

    /* Aqui termina app_main, y con ella la tarea que la ejecutaba. El sistema
     * no se para: sigue habiendo otras tareas en marcha. Por que es asi se ve
     * en U1-S5. */
    ESP_LOGI(TAG, "app_main termina");
}
