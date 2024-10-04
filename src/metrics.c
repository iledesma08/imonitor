#include "metrics.h"

double get_memory_usage()
{
    FILE* fp;
    char buffer[BUFFER_SIZE];
    unsigned long long total_mem = 0, free_mem = 0;

    /* Abrir el archivo /proc/meminfo */
    fp = fopen("/proc/meminfo", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/meminfo");
        return -1.0;
    }

    /* Leer los valores de memoria total y disponible */
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (sscanf(buffer, "MemTotal: %llu kB", &total_mem) == 1)
        {
            continue; /* MemTotal encontrado */
        }
        if (sscanf(buffer, "MemAvailable: %llu kB", &free_mem) == 1)
        {
            break; /* MemAvailable encontrado, podemos dejar de leer */
        }
    }

    fclose(fp);

    /* Verificar si se encontraron ambos valores */
    if (total_mem == 0 || free_mem == 0)
    {
        fprintf(stderr, "Error al leer la informacion de memoria desde /proc/meminfo\n");
        return -1.0;
    }

    /* Calcular el porcentaje de uso de memoria */
    double used_mem = total_mem - free_mem;
    double mem_usage_percent = (used_mem / total_mem) * 100.0;

    return mem_usage_percent;
}

double get_cpu_usage()
{
    static unsigned long long prev_user = 0, prev_nice = 0, prev_system = 0, prev_idle = 0, prev_iowait = 0,
                              prev_irq = 0, prev_softirq = 0, prev_steal = 0;
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
    unsigned long long totald, idled;
    double cpu_usage_percent;

    /* Abrir el archivo /proc/stat */
    FILE* fp = fopen("/proc/stat", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/stat");
        return -1.0;
    }

    char buffer[BUFFER_SIZE * 4];
    if (fgets(buffer, sizeof(buffer), fp) == NULL)
    {
        perror("Error al leer /proc/stat");
        fclose(fp);
        return -1.0;
    }
    fclose(fp);

    /* Analizar los valores de tiempo de CPU */
    int ret = sscanf(buffer, "cpu  %llu %llu %llu %llu %llu %llu %llu %llu", &user, &nice, &system, &idle, &iowait,
                     &irq, &softirq, &steal);
    if (ret < 8)
    {
        fprintf(stderr, "Error al parsear /proc/stat\n");
        return -1.0;
    }

    /* Calcular las diferencias entre las lecturas actuales y anteriores */
    unsigned long long prev_idle_total = prev_idle + prev_iowait;
    unsigned long long idle_total = idle + iowait;

    unsigned long long prev_non_idle = prev_user + prev_nice + prev_system + prev_irq + prev_softirq + prev_steal;
    unsigned long long non_idle = user + nice + system + irq + softirq + steal;

    unsigned long long prev_total = prev_idle_total + prev_non_idle;
    unsigned long long total = idle_total + non_idle;

    totald = total - prev_total;
    idled = idle_total - prev_idle_total;

    if (totald == 0)
    {
        fprintf(stderr, "Totald es cero, no se puede calcular el uso de CPU!\n");
        return -1.0;
    }

    /* Calcular el porcentaje de uso de CPU */
    cpu_usage_percent = ((double)(totald - idled) / totald) * 100.0;

    /* Actualizar los valores anteriores para la siguiente lectura */
    prev_user = user;
    prev_nice = nice;
    prev_system = system;
    prev_idle = idle;
    prev_iowait = iowait;
    prev_irq = irq;
    prev_softirq = softirq;
    prev_steal = steal;

    return cpu_usage_percent;
}

double get_disk_usage()
{
    struct statvfs buf;

    if (statvfs("/", &buf) != 0)
    {
        perror("Error al obtener la informacion del sistema de archivos");
        return -1.0;
    }

    unsigned long total = buf.f_blocks * buf.f_frsize;
    unsigned long available = buf.f_bfree * buf.f_frsize;
    unsigned long used = total - available;

    return (double)used / total * 100.0;
}

double get_battery_percentage()
{
    FILE* fp = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (fp == NULL)
    {
        perror("Error al abrir el archivo de capacidad de la bateria");
        return -1.0;
    }

    int battery_percentage;
    if (fscanf(fp, "%d", &battery_percentage) != 1)
    {
        perror("Error al leer el porcentaje de bateria");
        fclose(fp);
        return -1.0;
    }

    fclose(fp);
    return (double)battery_percentage;
}

double get_cpu_temperature()
{
    FILE* fp = fopen("/sys/class/thermal/thermal_zone1/temp", "r");
    if (fp == NULL)
    {
        perror("Error al abrir el archivo de temperatura de la CPU");
        return -1.0;
    }

    int temperature_millidegrees;
    if (fscanf(fp, "%d", &temperature_millidegrees) != 1)
    {
        perror("Error al leer la temperatura de la CPU");
        fclose(fp);
        return -1.0;
    }

    fclose(fp);

    /* Convertimos la temperatura de miligrados Celsius a grados Celsius */
    return temperature_millidegrees / 1000;
}

void get_process_states(int* total, int* suspended, int* ready, int* uninterruptible, int* stopped, int* zombie,
                        int* running)
{
    DIR* proc_dir = opendir("/proc");
    if (proc_dir == NULL)
    {
        perror("Error al abrir /proc");
        return;
    }

    struct dirent* entry;
    *total = 0;
    *suspended = 0;
    *ready = 0;
    *uninterruptible = 0; /* Uninterrumpible sleep */
    *stopped = 0;
    *zombie = 0;
    *running = 0;

    while ((entry = readdir(proc_dir)) != NULL)
    {
        if (isdigit(entry->d_name[0]))
        {
            char path[BUFFER_SIZE];
            snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);

            FILE* fp = fopen(path, "r");
            if (fp == NULL)
            {
                continue;
            }

            char state;
            if (fscanf(fp, "%*d %*s %c", &state) == 1)
            {
                (*total)++;
                switch (state)
                {
                case 'S':
                    (*suspended)++;
                    break;
                case 'R':
                    (*ready)++;
                    break;
                case 'D':
                    (*uninterruptible)++;
                    break;
                case 'T':
                    (*stopped)++;
                    break;
                case 'Z':
                    (*zombie)++;
                    break;
                }
            }

            fclose(fp);
        }
    }

    closedir(proc_dir);

    *running = *total - *suspended - *ready - *uninterruptible - *stopped - *zombie;
}

unsigned long get_bytes_received(const char* interface)
{
    FILE* fp = fopen("/proc/net/dev", "r");
    if (fp == NULL)
    {
        perror("Error al abrir /proc/net/dev");
        return -1;
    }
    char buffer[BUFFER_SIZE];
    unsigned long bytes_received = 0;
    // Saltar las dos primeras lineas de encabezado
    fgets(buffer, sizeof(buffer), fp);
    fgets(buffer, sizeof(buffer), fp);
    // Buscar la interfaz deseada
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        if (strstr(buffer, interface) != NULL)
        {
            // Parsear la linea para obtener los bytes recibidos (el primer campo despues del nombre de la interfaz)
            sscanf(buffer, "%*s %lu", &bytes_received);
            break;
        }
    }
    fclose(fp);
    return bytes_received;
}

double get_downloaded_bytes(const char* interface, int interval)
{
    unsigned long bytes1 = get_bytes_received(interface);
    sleep(interval);
    unsigned long bytes2 = get_bytes_received(interface);

    if (bytes1 == (unsigned long)-1 || bytes2 == (unsigned long)-1)
    {
        return -1.0; /* Error al obtener los bytes descargados */
    }

    return (double)(bytes2 - bytes1) / interval; /* Bytes descargados por segundo */
}

double get_battery_power_consumption()
{
    FILE* fp;
    int power;

    /* Abrir el archivo que contiene la potencia en microvatios */
    fp = fopen("/sys/class/power_supply/BAT0/power_now", "r");
    if (fp == NULL)
    {
        perror("Error al abrir el archivo de potencia");
        return -1.0;
    }

    /* Leer la potencia en microvatios */
    if (fscanf(fp, "%d", &power) != 1)
    {
        perror("Error al leer la potencia");
        fclose(fp);
        return -1.0;
    }

    fclose(fp);

    return (double)power / 1e6; /* Convertir microvatios a vatios */
}