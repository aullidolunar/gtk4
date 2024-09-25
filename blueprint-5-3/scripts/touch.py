# python touch.py file_path

import os
import sys

def touch(_file):
	try:
		os.mknod(_file)
	except FileExistsError:
		pass

touch(sys.argv[1])
