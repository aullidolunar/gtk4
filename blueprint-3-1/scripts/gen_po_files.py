# python gen_po_files.py "msginit_executable" "pot_file" "outdir_po" "langs"

import os
import sys
import datetime
import subprocess

msginit_executable = sys.argv[1]
pot_file = sys.argv[2]
outdir_po = sys.argv[3]
langs = sys.argv[4:]

saved_cwd = os.getcwd()
pot_path = os.path.join(saved_cwd, pot_file)
dep_po_path = os.path.join(saved_cwd, '.dep.po')
os.chdir(outdir_po)

with open(dep_po_path, 'w') as dep_file:
	
	dep_file.write('Timestamp: {:%Y-%b-%d %H:%M:%S}\n'.format(datetime.datetime.now()))
	
	for lang in langs:
	
		lang_po = lang + '.po'
		lang_path = os.path.join(outdir_po, lang_po)
			
		if not os.path.exists(lang_path):
			subprocess.call([
				msginit_executable,
				'-i',
				pot_path,
				'-l',
				lang + '.UTF-8',
				'--no-translator',
				'-o',
				lang_po
			])
				
			dep_file.write(f'{sys.argv[0]}: "{lang_path}" created.\n')
			
		else:
			dep_file.write(f'{sys.argv[0]}: "{lang_po}" exists. Skipped.\n')

os.chdir(saved_cwd)
