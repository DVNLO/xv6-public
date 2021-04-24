#! /bin/bash
make clean && make -j 12 qemu-nox-gdb CPUS=1 ;
