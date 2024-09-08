# python locales_cleanup.py "dummy_depfile" "clean_files:"

import os
import sys

dummy_depfile = sys.argv[1]
clean_files = sys.argv[2:]

for x in clean_files:
	try:
	    os.remove(x)
	except OSError:
	    pass	

try:
    os.remove(dummy_depfile)
except OSError:
    pass

