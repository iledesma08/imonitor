/**
 * @file expose_metrics.h
 * @brief Programa para leer el uso de CPU y memoria y exponerlos como métricas de Prometheus.
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

#define BUFFER_SIZE 256

/**
 * @brief Registra las métricas en el registro de coleccionistas de Prometheus. 
 */
void register_metrics();

/**
 * @brief Actualiza la métrica de uso de CPU.
 */
void update_cpu_gauge();

/**
 * @brief Actualiza la métrica de uso de memoria.
 */
void update_memory_gauge();

/**
 * @brief Actualiza la métrica de uso de disco.
 */
void update_disk_gauge();

/**
 * @brief Actualiza la métrica de porcentaje de batería.
 */
void update_battery_gauge();

/**
 * @brief Actualiza la métrica de temperatura de la CPU.
 */
void update_cpu_temperature_gauge();

/**
 * @brief Actualiza la métrica de cantidad de procesos.
 */
void update_process_count_gauge();

/**
 * @brief Actualiza la métrica de velocidad de subida.
 * @param interface Interfaz de red a monitorear.
 */
void update_upload_speed_gauge(const char* interface);

/**
 * @brief Actualiza la métrica de velocidad de descarga.
 * @param interface Interfaz de red a monitorear.
 */
void update_downloaded_bytes_gauge(const char* interface);

/**
 * @brief Función del hilo para exponer las métricas vía HTTP en el puerto 8000.
 * @param arg Argumento no utilizado.
 * @return NULL
 */
void* expose_metrics(void* arg);

/**
 * @brief Inicializar mutex y métricas.
 */
void init_metrics();

/**
 * @brief Destructor de mutex
 */
void destroy_mutex();
