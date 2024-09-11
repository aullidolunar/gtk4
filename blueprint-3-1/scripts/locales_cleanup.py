# python locales_cleanup.py "clean_files"

import os
import sys
import shutil

clean_files = sys.argv[1:]

for f in clean_files:
	try:
		if os.path.isfile(f):
			os.remove(f)
		else:
			 shutil.rmtree(f)
	except OSError:
	    pass	

