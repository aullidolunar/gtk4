# python gen_updated_po.py "msgmerge_executable" "pot_file" "outdir_po"

import os
import sys
import glob
import datetime
import subprocess

msgmerge_executable = sys.argv[1]
pot_file = sys.argv[2]
outdir_po = sys.argv[3]

saved_cwd = os.getcwd()
po_dep = os.path.join(saved_cwd, '.dep.po')
pot_path = os.path.join(saved_cwd, pot_file)
os.chdir(outdir_po)

with open(po_dep, 'w') as dep_file:
	dep_file.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n'.format(datetime.datetime.now()))
	for po_file in glob.glob('*.po'):
		subprocess.call([
			msgmerge_executable,
			'-U',
			'--backup=off',
			po_file,
			pot_path
		])
		dep_file.write(f'{sys.argv[0]}: "{po_file}" merged.\n')

os.chdir(saved_cwd)

with open('.dep.mo', 'w') as m:
	m.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n'.format(datetime.datetime.now()))
