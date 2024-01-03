#!/bin/bash
 
rm key_demo
echo "rm demo file"
echo "build demo new"

arm-none-linux-gnueabi-gcc demo.c -o key_demo
