# python gen_locales_po.py "msgfmt_executable" "program_name" "dir_po" "dir_mo" "dummy_depfile"

import os
import glob
import sys
import subprocess
from pathlib import Path

n = 1
msgfmt_executable = sys.argv[n]

n += 1
program_name = sys.argv[n]

n += 1
dir_po = sys.argv[n]

n += 1
dir_mo = sys.argv[n]

n += 1
dummy_depfile = sys.argv[n]

saved_cwd = os.getcwd()
os.chdir(dir_mo)

mo_files = []

po_files = glob.glob(dir_po + '/*.po')
for po_file in po_files:
	lang = Path(po_file).stem
	lc_messages_path = Path(lang + '/LC_MESSAGES')
	lc_messages_path.mkdir(parents=True, exist_ok=True)
	mo_file = program_name + '.mo'
	mo_path = lc_messages_path / mo_file
	
	mo_files.append(mo_path)
	
	subprocess.call(
		[
			msgfmt_executable,
			po_file,
			'-o',
			mo_path
		]
	)

os.chdir(saved_cwd)

with open(dummy_depfile, 'w') as dep_file:
	for mo_file in mo_files:
		dep_file.write(f"{mo_file}\n")