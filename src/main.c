/**
 * @file main.c
 * @brief Entry point of the system
 */

#include "expose_metrics.h"
#include <stdbool.h>

#define SLEEP_TIME 1
#define RED_INTERFACE "wlp0s20f3"

int main(int argc, char* argv[])
{
    // Inicializamos las métricas y el mutex
    init_metrics();
    
    // Creamos un hilo para exponer las métricas vía HTTP
    pthread_t tid;
    if (pthread_create(&tid, NULL, expose_metrics, NULL) != 0)
    {
        fprintf(stderr, "Error al crear el hilo del servidor HTTP\n");
        return EXIT_FAILURE;
    }

    // Bucle principal para actualizar las métricas cada segundo
    while (true)
    {
        update_cpu_gauge();
        update_memory_gauge();
        update_disk_gauge();
        update_battery_gauge();
        update_cpu_temperature_gauge();
        update_process_count_gauge();
        update_upload_speed_gauge(RED_INTERFACE);
        update_downloaded_bytes_gauge(RED_INTERFACE);
        sleep(SLEEP_TIME);
    }

    return EXIT_SUCCESS;
}
