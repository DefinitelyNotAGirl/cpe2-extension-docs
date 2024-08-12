#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import os
import platform

def execute(cmd: str):
	if os.system(cmd) != 0:
		exit (1)

execute("python ./build-system/main.py debug")
execute("cd ../cpe2Example && ./cp2 -Wno-unimplemented -MD  -Wno-deprecated -Bbuild -Ddocumentation -Iinc --fno-libc -NOD -S -c -o build/main.o src/main.c2")
print("debug run done")
