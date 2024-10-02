#!/bin/bash

# Function to check if a process is running and start it if it is not
check_and_start_process() {
    local process_name=$1
    local start_command=$2

    if ! pgrep -x "$process_name" > /dev/null; then
        echo "$process_name is not running. Starting it..."
        eval "$start_command"
    else
        echo "$process_name is already running."
    fi
}

# Function to check if a process is running and terminate it if it is
check_and_terminate_process() {
    local process_name=$1

    if pgrep -x "$process_name" > /dev/null; then
        echo "$process_name is running. Terminating it..."
        pkill -x "$process_name"
    else
        echo "$process_name is not running."
    fi
}

# Check and start Grafana
check_and_start_process "grafana" "sudo /bin/systemctl start grafana-server &"

# Check and start the executable
check_and_start_process "executable" "./executable &"

# Check and start Prometheus
check_and_start_process "prometheus" "./utilities/prometheus-2.55.0-rc.0.linux-amd64/prometheus --config.file=./utilities/prometheus-2.55.0-rc.0.linux-amd64/prometheus.yml &"

# Check if executable is running and terminate it
check_and_terminate_process "executable"

# Wait for background processes to finish
wait