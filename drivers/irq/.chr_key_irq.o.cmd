cmd_/home/liuyang/Driver/key_irq/chr_key_irq.o := /usr/local/share/arm-toolchain/bin/arm-none-linux-gnueabi-gcc -Wp,-MD,/home/liuyang/Driver/key_irq/.chr_key_irq.o.d  -nostdinc -isystem /usr/local/share/arm-toolchain/bin/../lib/gcc/arm-none-linux-gnueabi/4.4.1/include -I/opt/arm_file/iTop4412_Kernel_3.0/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-exynos/include -Iarch/arm/plat-s5p/include -Iarch/arm/plat-samsung/include -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs -fno-strict-aliasing -fno-common -Werror-implicit-function-declaration -Wno-format-security -fno-delete-null-pointer-checks -mtune=cortex-a9 -march=armv7-a -mfpu=neon -O2 -marm -fno-dwarf2-cfi-asm -fno-omit-frame-pointer -mapcs -mno-sched-prolog -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -msoft-float -Uarm -Wframe-larger-than=1024 -fno-stack-protector -fno-omit-frame-pointer -fno-optimize-sibling-calls -g -Wdeclaration-after-statement -Wno-pointer-sign -fno-strict-overflow -fconserve-stack  -DMODULE -fno-pic -D"KBUILD_STR(s)=\#s" -D"KBUILD_BASENAME=KBUILD_STR(chr_key_irq)"  -D"KBUILD_MODNAME=KBUILD_STR(chr_key_irq)" -c -o /home/liuyang/Driver/key_irq/chr_key_irq.o /home/liuyang/Driver/key_irq/chr_key_irq.c

source_/home/liuyang/Driver/key_irq/chr_key_irq.o := /home/liuyang/Driver/key_irq/chr_key_irq.c

deps_/home/liuyang/Driver/key_irq/chr_key_irq.o := \

/home/liuyang/Driver/key_irq/chr_key_irq.o: $(deps_/home/liuyang/Driver/key_irq/chr_key_irq.o)

$(deps_/home/liuyang/Driver/key_irq/chr_key_irq.o):
