# python gen_po_files.py "pot_file" "outdir_po" "lang" "msginit_executable" "dummy_out"

import os
import sys
import subprocess
import datetime

pot_file = sys.argv[1]
outdir_po = sys.argv[2]
lang = sys.argv[3]
msginit_executable = sys.argv[4]
dummy_out = sys.argv[5]

if not os.path.exists(pot_file):
	print(f"{pot_file} was not localed.\n")
	sys.exit(1)

saved_cwd = os.getcwd()
os.chdir(outdir_po)

lang_po = lang + '.po'

subprocess.call([
	msginit_executable,
	'-i',
	pot_file,
	'-l',
	lang + '.UTF-8',
	'--no-translator',
	'-o',
	lang_po
])

os.chdir(saved_cwd)

po_file = os.path.join(outdir_po, lang_po)

with open(dummy_out, 'w') as dummy_file:
	dummy_file.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n'.format(datetime.datetime.now()))
	dummy_file.write(f'Path: {po_file}')

