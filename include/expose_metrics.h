/**
 * @file expose_metrics.h
 * @brief Funciones para exponer metricas via HTTP.
 *
 * Este archivo contiene las funciones necesarias para exponer las metricas
 * recolectadas por el programa en un servidor HTTP en el puerto 8000.
 *
 * Las metricas se exponen en formato Prometheus, y se actualizan cada segundo.
 *
 * Para compilar el programa, se debe enlazar con las bibliotecas de Prometheus
 *
 * Las metricas se exponen a traves de una interfaz HTTP utilizando la biblioteca
 * Prometheus C Client.
 */

#include "metrics.h"
#include <errno.h>
#include <prom.h>
#include <promhttp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Para sleep

/**
 * @brief Mutex para sincronizacion de hilos.
 * 
 * Se utiliza para proteger el acceso a las metricas.
 */
#define METRICS_COUNT 14

/**
 * @brief Tiempo de espera entre actualizaciones de metricas.
 * 
 * Se actualizan cada segundo.
 */
#define SLEEP_TIME 1

/**
 * @brief Registra las metricas en el registro de coleccionistas de Prometheus.
 */
void register_metrics();

/**
 * @brief Actualiza la metrica de uso de CPU.
 */
void update_cpu_gauge();

/**
 * @brief Actualiza la metrica de uso de memoria.
 */
void update_memory_gauge();

/**
 * @brief Actualiza la metrica de uso de disco.
 */
void update_disk_gauge();

/**
 * @brief Actualiza la metrica de porcentaje de bateria.
 */
void update_battery_gauge();

/**
 * @brief Actualiza la metrica de temperatura de la CPU.
 */
void update_cpu_temperature_gauge();

/**
 * @brief Actualiza las metricas de los procesos.
 */
void update_process_states_gauge();

/**
 * @brief Actualiza la metrica de velocidad de descarga.
 * @param interface Interfaz de red a monitorear.
 */
void update_downloaded_bytes(const char* interface);

/**
 * @brief Actualiza la metrica de potencia del sistema.
 */
void update_battery_power_gauge();

/**
 * @brief Funcion del hilo para exponer las metricas via HTTP en el puerto 8000.
 * @param arg Argumento no utilizado.
 * @return NULL
 */
void* expose_metrics(void* arg);

/**
 * @brief Inicializar mutex y metricas.
 */
void init_metrics();

/**
 * @brief Destructor de mutex
 */
void destroy_mutex();
