/**
 * @file main.c
 * @brief Entry point of the system
 */

#include "expose_metrics.h"
#include <stdbool.h>

/**
 * @brief Programa principal.
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char* argv[])
{
    // Inicializamos las metricas y el mutex
    init_metrics();

    // Creamos un hilo para exponer las metricas via HTTP
    pthread_t tid;
    if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo del servidor HTTP\n");
        return EXIT_FAILURE;
    }

    // Bucle principal para actualizar las metricas cada segundo
    while (true)
    {
        update_cpu_gauge();
        update_memory_gauge();
        update_disk_gauge();
        update_battery_gauge();
        update_cpu_temperature_gauge();
        update_process_states_gauge();
        update_downloaded_bytes();
        update_battery_power_gauge();
        sleep(SLEEP_TIME);
    }

    return EXIT_SUCCESS;
}
