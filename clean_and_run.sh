#! /bin/bash
make clean && make -j 12 qemu-nox CPUS=2 ;
