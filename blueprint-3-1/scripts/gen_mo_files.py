# python gen_mo_files.py "msgfmt_executable" "po_dir" "program_name" "mo_depfile"

import os
import glob
import sys
import subprocess
import datetime
from pathlib import Path

msgfmt_executable = sys.argv[1]
po_dir = sys.argv[2]
program_name = sys.argv[3]
mo_depfile = sys.argv[4]

with open(mo_depfile, 'w') as m:
	m.write('')

saved_cwd = os.getcwd()
po_dep = os.path.join(saved_cwd, '.dep.po')
os.chdir(po_dir)

if not os.path.isfile(po_dep):
	 print(f'{sys.argv[0]}: {po_dep} not found. Exiting.')
	 exit()
else:
	for po_file in glob.glob('*.po'):
		po_path = os.path.join(po_dir, po_file)
		mo_path = os.path.join(saved_cwd, 'locale', po_file[:-3], 'LC_MESSAGES')
		os.makedirs(mo_path, exist_ok = True)
		mo_file = os.path.join(mo_path, program_name + '.mo')
		subprocess.call([
			msgfmt_executable,
			po_file,
			'-o',
			mo_file
		])
		print(f'{sys.argv[0]}: "{mo_file}" created.')

os.chdir(saved_cwd)
