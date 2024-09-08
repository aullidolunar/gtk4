# python locales_uncleanup.py "dummy_depfile"

import os
import sys

dummy_depfile = sys.argv[1]

with open(dummy_depfile, 'w') as locales_uncleanup:
	pass

