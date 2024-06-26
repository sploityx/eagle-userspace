# Eagle Userspace Corrections

## Introduction
This userspace application provides a simple interface for interacting with the custom /proc file created by the custom kernel eagle idle governor.

The idle governor dynamically adjusts system idle states to optimize power consumption based on system load and other factors. 

This application allows users to read from and write to the /proc file associated with the idle governor, providing a means to view and modify its dynamic configurations.

## Eagle
In order to utilize the userspace interface, you first need to compile and install the custom kernel featuring [Eagle](https://github.com/sploityx/linux/tree/sys-gov).
