/**
 * @file metrics.h
 * @brief Funciones para obtener el uso de CPU y memoria desde el sistema de archivos /proc.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/statvfs.h>

#define BUFFER_SIZE 256

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
 * Lee la información del sistema de archivos desde /proc/statvfs y calcula el
 * porcentaje de uso de disco.
 *
 * @return Uso de disco como porcentaje (0.0 a 100.0), o -1.0 en caso de error.
 */
double get_disk_usage();

/**
 * @brief Obtiene el porcentaje de batería restante desde /sys/class/power_supply.
 *
 * Lee el nivel de batería restante desde /sys/class/power_supply y calcula el
 * porcentaje de batería restante.
 *
 * @return Porcentaje de batería restante (0.0 a 100.0), o -1.0 en caso de error.
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
 * @brief Obtiene la cantidad de procesos en ejecución desde /proc/loadavg.
 *
 * Lee la cantidad de procesos en ejecución desde /proc/loadavg y la devuelve.
 *
 * @return Cantidad de procesos en ejecución, o -1 en caso de error.
 */
int get_process_count();

/**
 * @brief Obtiene la cantidad de bytes transmitidos por una interfaz de red.
 *
 * Lee la cantidad de bytes transmitidos por una interfaz de red desde
 * /proc/net/dev y la devuelve.
 *
 * @param interface Nombre de la interfaz de red (eth0 o wlan0).
 * @return Cantidad de bytes transmitidos, o -1 en caso de error.
 */
unsigned long get_bytes_transmitted(const char* interface);

/**
 * @brief Obtiene la velocidad de subida de una interfaz de red.
 *
 * Lee la cantidad de bytes transmitidos por una interfaz de red en dos momentos
 * y calcula la velocidad de subida en bytes por segundo.
 *
 * @param interface Nombre de la interfaz de red (eth0 o wlan0).
 * @param interval Intervalo de tiempo en segundos.
 * @return Velocidad de subida en bytes por segundo, o -1.0 en caso de error.
 */
double get_upload_speed(const char* interface, int interval);

/**
 * @brief Obtiene la cantidad de bytes recibidos por una interfaz de red.
 *
 * Lee la cantidad de bytes recibidos por una interfaz de red desde
 * /proc/net/dev y la devuelve.
 *
 * @param interface Nombre de la interfaz de red (ej.: eth0 o wlan0).
 * @return Cantidad de bytes transmitidos, o -1 en caso de error.
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