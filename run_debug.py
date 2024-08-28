#!/usr/bin/env python3
# -*- coding:utf-8 -*-
import os
import platform

def execute(cmd: str):
	if os.system(cmd) != 0:
		exit (1)

execute("python ./build-system/main.py debug")
execute("install_name_tool cpe2-extension-docs -id .cpe2/bin/cpe2-extension-docs")
execute("touch ../../bin/compiler")
execute("rm ../../../c2docs/generated/layout.json")
execute("make -C ../../../")
execute("cd ../../../ && c2dc")
print("done")
