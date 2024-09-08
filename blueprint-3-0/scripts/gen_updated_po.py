# python gen_updated_po.py "msgmerge_executable" "outdir_po" "pot_file" "po_file" "dummy_depfile"

import os
import sys
import subprocess

msgmerge_executable = sys.argv[1]
pot_file = sys.argv[2]
po_file = sys.argv[3]
dummy_depfile = sys.argv[4]

subprocess.call([
	msgmerge_executable,
	'-U',
	'--backup=off',
	po_file,
	pot_file
])

with open(dummy_depfile, 'w') as updated_po_file:
	updated_po_file.write(f"File saved at\n{po_file}")

