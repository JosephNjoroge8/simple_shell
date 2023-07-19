#!/bin/bash

pid_max_value=$(cat /proc/sys/kernel/pid_max)
echo "The maximum PID value is: $pid_max_value"
