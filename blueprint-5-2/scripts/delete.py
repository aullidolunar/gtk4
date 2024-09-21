# python delete.py file_path

import os
import sys

try:
	os.remove(sys.argv[1])
except:
	pass
