#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import os
import platform

def execute(cmd: str):
	if os.system(cmd) != 0:
		exit (1)

execute("python ./build-system/main.py debug")
