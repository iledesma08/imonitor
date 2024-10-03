#include "expose_metrics.h"
#define METRICS_COUNT 9
#define SLEEP_TIME 1 

/** Mutex para sincronización de hilos */
pthread_mutex_t lock;

/** Métrica de Prometheus para el uso de CPU */
static prom_gauge_t* cpu_usage_metric;

/** Métrica de Prometheus para el uso de memoria */
static prom_gauge_t* memory_usage_metric;

/** Métrica de Prometheus para el uso de disco */
static prom_gauge_t* disk_usage_metric;

/** Métrica de Prometheus para el porcentaje de batería */
static prom_gauge_t* battery_percentage_metric;

/** Métrica de Prometheus para la temperatura de la CPU */
static prom_gauge_t* cpu_temperature_metric;

/** Métrica de Prometheus para la cantidad de procesos */
static prom_gauge_t* process_count_metric;

/** Métrica de Prometheus para la velocidad de subida */
static prom_gauge_t* uploaded_bytes_metric;

/** Métrica de Prometheus para la velocidad de descarga */
static prom_gauge_t* downloaded_bytes_metric;

/** Métrica de Prometheus para la potencia consumida */
static prom_gauge_t* system_power_metric;

prom_metric_t* metrics[METRICS_COUNT];

void register_metrics() {
    metrics[0] = cpu_usage_metric;
    metrics[1] = memory_usage_metric;
    metrics[2] = disk_usage_metric;
    metrics[3] = battery_percentage_metric;
    metrics[4] = cpu_temperature_metric;
    metrics[5] = process_count_metric;
    metrics[6] = uploaded_bytes_metric;
    metrics[7] = downloaded_bytes_metric;
    metrics[8] = system_power_metric;

    int i;
    for (i = 0; i < METRICS_COUNT; i++) {
        if (prom_collector_registry_must_register_metric(metrics[i]) == NULL) {
            fprintf(stderr, "Error al registrar la métrica %d\n", i);
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

void update_process_count()
{
    int process_count = get_process_count();
    if (process_count >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(process_count_metric, (double)process_count, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener la cantidad de procesos\n");
    }
}

void update_uploaded_bytes(const char* interface)
{
    double speed = get_uploaded_bytes(interface, 1);  // Intervalo de 1 segundo
    if (speed >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(uploaded_bytes_metric, speed, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener los bytes subidos\n");
    }
}

void update_downloaded_bytes(const char* interface)
{
    double speed = get_downloaded_bytes(interface, 1);  // Intervalo de 1 segundo
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

void update_system_power_gauge()
{
    double power = get_system_power_consumption();  // Obtener la potencia en vatios
    if (power >= 0)
    {
        pthread_mutex_lock(&lock);
        prom_gauge_set(system_power_metric, power, NULL);
        pthread_mutex_unlock(&lock);
    }
    else
    {
        fprintf(stderr, "Error al obtener la potencia del sistema\n");
    }
}

void* expose_metrics(void* arg)
{
    (void)arg; // Argumento no utilizado

    // Aseguramos que el manejador HTTP esté adjunto al registro por defecto
    promhttp_set_active_collector_registry(NULL);

    // Iniciamos el servidor HTTP en el puerto 8000
    struct MHD_Daemon* daemon = promhttp_start_daemon(MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL);
    if (daemon == NULL)
    {
        fprintf(stderr, "Error al iniciar el servidor HTTP\n");
    }

    // Mantenemos el servidor en ejecución
    while (1)
    {
        sleep(1);
    }

    // Nunca debería llegar aquí
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

    // Creamos la métrica para el uso de CPU
    cpu_usage_metric = prom_gauge_new("cpu_usage_percentage", "Porcentaje de uso de CPU", 0, NULL);
    if (cpu_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de CPU\n");
    }

    // Creamos la métrica para el uso de memoria
    memory_usage_metric = prom_gauge_new("memory_usage_percentage", "Porcentaje de uso de memoria", 0, NULL);
    if (memory_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de memoria\n");
    }

    // Creamos la métrica para el uso de disco
    disk_usage_metric = prom_gauge_new("disk_usage_percentage", "Porcentaje de uso de disco", 0, NULL);
    if (disk_usage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de uso de disco\n");
    }

    // Creamos la métrica para el porcentaje de batería
    battery_percentage_metric = prom_gauge_new("battery_percentage", "Porcentaje de bateria restante", 0, NULL);
    if (battery_percentage_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de porcentaje de batería\n");
    }

    // Creamos la métrica para la temperatura de la CPU
    cpu_temperature_metric = prom_gauge_new("cpu_temperature_celsius", "Temperatura de la CPU en grados Celsius", 0, NULL);
    if (cpu_temperature_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de temperatura de la CPU\n");
    }

    // Creamos la métrica para la cantidad de procesos
    process_count_metric = prom_gauge_new("process_count", "Cantidad de procesos en ejecución", 0, NULL);
    if (process_count_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de cantidad de procesos\n");
    }

    // Creamos la métrica para la velocidad de subida
    uploaded_bytes_metric = prom_gauge_new("uploaded_bytes_per_second", "Bytes subidos por segundo", 0, NULL);
    if (uploaded_bytes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de velocidad de subida\n");
    }

    // Creamos la métrica para la velocidad de descarga
    downloaded_bytes_metric = prom_gauge_new("downloaded_bytes_per_second", "Bytes descargados por segundo", 0, NULL);
    if (downloaded_bytes_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de velocidad de descarga\n");
    }

    // Creamos la métrica para la potencia del sistema
    system_power_metric = prom_gauge_new("system_power_watts", "Potencia del sistema en vatios", 0, NULL);
    if (system_power_metric == NULL)
    {
        fprintf(stderr, "Error al crear la métrica de potencia del sistema\n");
    }

    // Registramos las métricas en el registro de coleccionistas de Prometheus
    register_metrics();
}

void destroy_mutex()
{
    pthread_mutex_destroy(&lock);
}
