PULP_LDFLAGS      += 
PULP_CFLAGS       += 
PULP_FC_ARCH_CFLAGS ?=  -march=rv32imfcxpulpv2 -mfdiv -D__riscv__
PULP_FC_CFLAGS    += -fdata-sections -ffunction-sections -I/home/wp/works/NEPES_FPGA/pulp-sdk/pkg/sdk/dev/install/include/io -I/home/wp/works/NEPES_FPGA/pulp-sdk/pkg/sdk/dev/install/include -include /home/wp/works/src/nepes/flash/build/pulpissimo/fc_config.h
PULP_FC_OMP_CFLAGS    += -fopenmp -mnativeomp
ifdef PULP_RISCV_GCC_TOOLCHAIN
PULP_FC_CC = $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-gcc 
PULP_CC = $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-gcc 
PULP_AR ?= $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-ar
PULP_LD ?= $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-gcc
PULP_FC_OBJDUMP ?= $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-objdump
PULP_OBJDUMP ?= $(PULP_RISCV_GCC_TOOLCHAIN)/bin/riscv32-unknown-elf-objdump
else
PULP_FC_CC = $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-gcc 
PULP_CC = $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-gcc 
PULP_AR ?= $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-ar
PULP_LD ?= $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-gcc
PULP_FC_OBJDUMP ?= $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-objdump
PULP_OBJDUMP ?= $(PULP_RISCV_GCC_TOOLCHAIN_CI)/bin/riscv32-unknown-elf-objdump
endif
PULP_ARCH_FC_OBJDFLAGS ?= -Mmarch=rv32imfcxpulpv2
PULP_ARCH_OBJDFLAGS ?= -Mmarch=rv32imfcxpulpv2
PULP_ARCH_LDFLAGS ?=  -march=rv32imfcxpulpv2 -mfdiv -D__riscv__
PULP_LDFLAGS_test = -nostartfiles -nostdlib -Wl,--gc-sections -L/home/wp/works/NEPES_FPGA/pulp-sdk/pkg/sdk/dev/install/rules -Tpulpissimo/link.ld -L/home/wp/works/NEPES_FPGA/pulp-sdk/pkg/sdk/dev/install/lib/pulpissimo -L/home/wp/works/NEPES_FPGA/pulp-sdk/pkg/sdk/dev/install/lib/pulpissimo/pulpissimo_zcu104 -lrt -lrtio -lrt -lgcc
PULP_OMP_LDFLAGS_test = -lomp
pulpRunOpt        += --dir=/home/wp/works/src/nepes/flash/build/pulpissimo --binary=test/test
