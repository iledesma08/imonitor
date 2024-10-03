#include "expose_metrics.h"
#define METRICS_COUNT 14
#define SLEEP_TIME 1

/** Mutex para sincronizacion de hilos */
pthread_mutex_t lock;

/** Metrica de Prometheus para el uso de CPU */
static prom_gauge_t* cpu_usage_metric;

/** Metrica de Prometheus para el uso de memoria */
static prom_gauge_t* memory_usage_metric;

/** Metrica de Prometheus para el uso de disco */
static prom_gauge_t* disk_usage_metric;

/** Metrica de Prometheus para el porcentaje de bateria */
static prom_gauge_t* battery_percentage_metric;

/** Metrica de Prometheus para la temperatura de la CPU */
static prom_gauge_t* cpu_temperature_metric;

/** Metricas de Prometheus para los procesos */
static prom_gauge_t* total_processes_metric;
static prom_gauge_t* suspended_processes_metric;
static prom_gauge_t* ready_processes_metric;
static prom_gauge_t* uninterruptible_processes_metric;
static prom_gauge_t* stopped_processes_metric;
static prom_gauge_t* zombie_processes_metric;
static prom_gauge_t* running_processes_metric;

/** Metrica de Prometheus para la velocidad de subida */
static prom_gauge_t* uploaded_bytes_metric;

/** Metrica de Prometheus para la velocidad de descarga */
static prom_gauge_t* downloaded_bytes_metric;

/** Metrica de Prometheus para la potencia entregada por la bateria */
static prom_gauge_t* battery_power_metric;

prom_metric_t* metrics[METRICS_COUNT];

void register_metrics()
{
    metrics[0] = cpu_usage_metric;
    metrics[1] = memory_usage_metric;
    metrics[2] = disk_usage_metric;
    metrics[3] = battery_percentage_metric;
    metrics[4] = cpu_temperature_metric;
    metrics[5] = total_processes_metric;
    metrics[6] = suspended_processes_metric;
    metrics[7] = ready_processes_metric;
    metrics[8] = uninterruptible_processes_metric;
    metrics[9] = stopped_processes_metric;
    metrics[10] = zombie_processes_metric;
    metrics[11] = running_processes_metric;
    metrics[12] = downloaded_bytes_metric;
    metrics[13] = battery_power_metric;

    int i;
    for (i = 0; i < METRICS_COUNT; i++)
    {
        if (prom_collector_registry_must_register_metric(metrics[i]) == NULL)
        {
            fprintf(stderr, "Error al registrar la metrica %d\n", i);
        }
    }
}

void update_cpu_gauge()
{
    double usage = get_cpu_usage();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(cpu_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de CPU\n");
    }
}

void update_memory_gauge()
{
    double usage = get_memory_usage();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(memory_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de memoria\n");
    }
}

void update_disk_gauge()
{
    double usage = get_disk_usage();
    if (usage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(disk_usage_metric, usage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el uso de disco\n");
    }
}

void update_battery_gauge()
{
    double percentage = get_battery_percentage();
    if (percentage >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(battery_percentage_metric, percentage, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener el porcentaje de bateria\n");
    }
}

void update_cpu_temperature_gauge()
{
    int temperature = get_cpu_temperature();
    if (temperature >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(cpu_temperature_metric, temperature, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener la temperatura de la CPU\n");
    }
}

void update_process_states_gauge()
{
    // Variables para almacenar los contadores de procesos
    int total = 0, suspended = 0, ready = 0, uninterruptible = 0, stopped = 0, zombie = 0, running = 0;

    // Llama a la funcion get_process_states para obtener el estado de los procesos
    get_process_states(&total, &suspended, &ready, &uninterruptible, &stopped, &zombie, &running);

    if (total >= 0 && suspended >= 0 && ready >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(total_processes_metric, total, NULL);                     // Total de procesos
        prom_gauge_set(suspended_processes_metric, suspended, NULL);             // Procesos suspendidos
        prom_gauge_set(ready_processes_metric, ready, NULL);                     // Procesos listos
        prom_gauge_set(uninterruptible_processes_metric, uninterruptible, NULL); // Procesos en estado uninterruptible
        prom_gauge_set(stopped_processes_metric, stopped, NULL);                 // Procesos detenidos
        prom_gauge_set(zombie_processes_metric, zombie, NULL);                   // Procesos zombie
        prom_gauge_set(running_processes_metric, running, NULL);                 // Procesos en ejecucion
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener los estados de los procesos\n");
    }
}

void update_downloaded_bytes(const char* interface)
{
    double speed = get_downloaded_bytes(interface, 1); // Intervalo de 1 segundo
    if (speed >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(downloaded_bytes_metric, speed, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener los bytes descargados\n");
    }
}

void update_battery_power_gauge()
{
    double power = get_battery_power_consumption(); // Obtener la potencia en vatios
    if (power >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(battery_power_metric, power, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener la potencia utilizada por la bateria\n");
    }
}

void* expose_metrics(void* arg)
{
    (void)arg; // Argumento no utilizado

    // Aseguramos que el manejador HTTP este adjunto al registro por defecto
    promhttp_set_active_collector_registry(NULL);

    // Iniciamos el servidor HTTP en el puerto 8000
    struct MHD_Daemon* daemon = promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL);
    if (daemon == NULL)
    {
        fprintf(stderr, "Error al iniciar el servidor HTTP\n");
    }

    // Mantenemos el servidor en ejecucion
    while (1)
    {
        sleep(1);
    }

    // Nunca deberia llegar aqui
    MHD_stop_daemon(daemon);
}

void init_metrics()
{
    // Inicializamos el mutex
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        fprintf(stderr, "Error al inicializar el mutex\n");
    }

    // Inicializamos el registro de coleccionistas de Prometheus
    if (prom_collector_registry_default_init() != 0)
    {
        fprintf(stderr, "Error al inicializar el registro de Prometheus\n");
    }

    // Creamos la metrica para el uso de CPU
    cpu_usage_metric = prom_gauge_new("cpu_usage_percentage", "Porcentaje de uso de CPU", 0, NULL);
    if (cpu_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de uso de CPU\n");
    }

    // Creamos la metrica para el uso de memoria
    memory_usage_metric = prom_gauge_new("memory_usage_percentage", "Porcentaje de uso de memoria", 0, NULL);
    if (memory_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de uso de memoria\n");
    }

    // Creamos la metrica para el uso de disco
    disk_usage_metric = prom_gauge_new("disk_usage_percentage", "Porcentaje de uso de disco", 0, NULL);
    if (disk_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de uso de disco\n");
    }

    // Creamos la metrica para el porcentaje de bateria
    battery_percentage_metric = prom_gauge_new("battery_percentage", "Porcentaje de bateria restante", 0, NULL);
    if (battery_percentage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de porcentaje de bateria\n");
    }

    // Creamos la metrica para la temperatura de la CPU
    cpu_temperature_metric =
        prom_gauge_new("cpu_temperature_celsius", "Temperatura de la CPU en grados Celsius", 0, NULL);
    if (cpu_temperature_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de temperatura de la CPU\n");
    }

    // Creamos las metricas para los procesos
    total_processes_metric = prom_gauge_new("total_processes", "Cantidad total de procesos", 0, NULL);
    if (total_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad total de procesos\n");
    }
    suspended_processes_metric = prom_gauge_new("suspended_processes", "Numero de procesos suspendidos", 0, NULL);
    if (suspended_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos suspendidos\n");
    }
    ready_processes_metric = prom_gauge_new("ready_processes", "Numero de procesos listos", 0, NULL);
    if (ready_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos listos\n");
    }
    uninterruptible_processes_metric =
        prom_gauge_new("uninterruptible_processes", "Numero de procesos en estado uninterruptible", 0, NULL);
    if (uninterruptible_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos en estado uninterruptible\n");
    }
    stopped_processes_metric = prom_gauge_new("stopped_processes", "Numero de procesos detenidos", 0, NULL);
    if (stopped_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos detenidos\n");
    }
    zombie_processes_metric = prom_gauge_new("zombie_processes", "Numero de procesos zombie", 0, NULL);
    if (zombie_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos zombie\n");
    }
    running_processes_metric = prom_gauge_new("running_processes", "Numero de procesos en ejecucion", 0, NULL);
    if (running_processes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de cantidad de procesos en ejecucion\n");
    }

    // Creamos la metrica para la velocidad de descarga
    downloaded_bytes_metric = prom_gauge_new("downloaded_bytes_per_second", "Bytes descargados por segundo", 0, NULL);
    if (downloaded_bytes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de velocidad de descarga\n");
    }

    // Creamos la metrica para la potencia entregada por la bateria
    battery_power_metric =
        prom_gauge_new("battery_power_watts", "Potencia entregada por la bateria en vatios", 0, NULL);
    if (battery_power_metric == NULL)
    {
        fprintf(stderr, "Error al crear la metrica de potencia entregada por la bateria\n");
    }

    // Registramos las metricas en el registro de coleccionistas de Prometheus
    register_metrics();
}

void destroy_mutex()
{
    pthread_mutex_destroy(&lock);
}
