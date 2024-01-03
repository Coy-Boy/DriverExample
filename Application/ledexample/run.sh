#!/bin/bash
if [ -d "demo" ];then
	rm demo
fi
echo "rm demo file"
echo "build demo new"

arm-none-linux-gnueabi-gcc demo.c -o demo
