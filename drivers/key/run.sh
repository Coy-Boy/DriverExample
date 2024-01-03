#!/bin/bash
name=chr_key_1
rm "${name}.ko"
make

    if [ -f  "${name}.mod.c" ];then
			rm "${name}.mod.c"
	fi

	if [ -f  "${name}.o" ];then
			rm "${name}.o"
	fi

	if [ -f  "${name}.mod.o" ];then
			rm "${name}.mod.o"
	fi

	if [ -f  "${name}.mod.c" ];then
			rm "${name}.mod.c"
	fi

    if [ -f  "Module.symvers" ];then
			rm "Module.symvers"
	fi

	if [ -f  "modules.order" ];then
			rm "modules.order"
	fi
 echo "build finish!"
# ls -l --time-style=full 


