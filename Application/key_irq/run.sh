#!/bin/bash
 
rm key_irq
echo "rm demo file"
echo "build demo new"

arm-none-linux-gnueabi-gcc key_irq.c -o key_irq
ls -l
