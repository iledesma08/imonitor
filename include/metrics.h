/**
 * @file metrics.h
 * @brief Programa para leer metricas del sistema.
 *
 * Este programa lee diversas metricas del sistema, como el uso de memoria, CPU,
 * disco, bateria, temperatura de la CPU, cantidad de procesos en cada estado y
 * velocidad de descarga de una interfaz de red.
 *
 * Las metricas se leen desde varios archivos en el sistema de archivos de Linux,
 * como /proc/meminfo, /proc/stat, /proc/statvfs, /sys/class/power_supply y /sys/class/thermal.
 */

#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <unistd.h>

/**
 * @def BUFFER_SIZE
 * @brief El tamaño del buffer utilizado para almacenar datos.
 *
 * Este macro define que el tamaño del buffer será de 512 bytes.
 */
#define BUFFER_SIZE 512

/**
 * @brief Obtiene el porcentaje de uso de memoria desde /proc/meminfo.
 *
 * Lee los valores de memoria total y disponible desde /proc/meminfo y calcula
 * el porcentaje de uso de memoria.
 *
 * @return Uso de memoria como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_memory_usage();

/**
 * @brief Obtiene el porcentaje de uso de CPU desde /proc/stat.
 *
 * Lee los tiempos de CPU desde /proc/stat y calcula el porcentaje de uso de CPU
 * en un intervalo de tiempo.
 *
 * @return Uso de CPU como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_cpu_usage();

/**
 * @brief Obtiene el porcentaje de uso de disco desde /proc/statvfs.
 *
 * Lee la informacion del sistema de archivos desde /proc/statvfs y calcula el
 * porcentaje de uso de disco.
 *
 * @return Uso de disco como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_disk_usage();

/**
 * @brief Obtiene el porcentaje de bateria restante desde /sys/class/power_supply.
 *
 * Lee el nivel de bateria restante desde /sys/class/power_supply y calcula el
 * porcentaje de bateria restante.
 *
 * @return Porcentaje de bateria restante (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_battery_percentage();

/**
 * @brief Obtiene la temperatura de la CPU desde /sys/class/thermal.
 *
 * Lee la temperatura de la CPU desde /sys/class/thermal y la devuelve en grados
 * Celsius.
 *
 * @return Temperatura de la CPU en grados Celsius, o -1.0 en caso de error.
 */
double get_cpu_temperature();

/**
 * @brief Obtiene la cantidad de procesos en cada estado desde /proc.
 *
 * Lee el estado de cada proceso desde /proc y cuenta la cantidad de procesos
 * totales, suspendidos y listos.
 *
 * @param total Puntero a la variable donde se almacenara la cantidad total de procesos.
 * @param suspended Puntero a la variable donde se almacenara la cantidad de procesos suspendidos.
 * @param ready Puntero a la variable donde se almacenara la cantidad de procesos listos.
 * @param uninterruptible Puntero a la variable donde se almacenara la cantidad de procesos en estado suspensión
 * ininterruptible.
 * @param stopped Puntero a la variable donde se almacenara la cantidad de procesos detenidos.
 * @param zombie Puntero a la variable donde se almacenara la cantidad de procesos zombie.
 * @param running Puntero a la variable donde se almacenara la cantidad de procesos en ejecución.
 */
void get_process_states(int* total, int* suspended, int* ready, int* uninterruptible, int* stopped, int* zombie,
                        int* running);

/**
 * @brief Obtiene la cantidad de bytes recibidos por una interfaz de red.
 *
 * @param interface
 * @return unsigned long
 */
unsigned long get_bytes_received(const char* interface);

/**
 * @brief Obtiene la velocidad de bajada de una interfaz de red.
 *
 * Lee la cantidad de bytes recibidos por una interfaz de red en dos momentos
 * y calcula la velocidad de bajada en bytes por segundo.
 *
 * @param interface Nombre de la interfaz de red (ej.: eth0 o wlan0).
 * @param interval Intervalo de tiempo en segundos.
 * @return Velocidad de bajada en bytes por segundo, o -1.0 en caso de error.
 */
double get_downloaded_bytes(const char* interface, int interval);

/**
 * @brief Obtiene el consumo de energia del sistema desde /sys/class/power_supply/BAT0.
 *
 * Lee los valores de voltaje y corriente de la bateria desde /sys/class/power_supply/BAT0
 * y calcula el consumo de energia del sistema.
 *
 * @return Consumo de energia en vatios, o -1.0 en caso de error.
 */
double get_battery_power_consumption();
