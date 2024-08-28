# python gen_updated_locales_po.py "msgmerge_executable" "pot_file" "outdir_po" "linguas" "num_langs" "langs_list"

import os
import sys
import subprocess

n = 1
msgmerge_executable = sys.argv[n]

n += 1
pot_file = sys.argv[n]

n += 1
outdir_po = sys.argv[n]

n += 1
linguas = sys.argv[n]

n += 1
num_langs = int(sys.argv[n])

saved_cwd = os.getcwd()
os.chdir(outdir_po)

po_files = []

for _ in range(0, int(num_langs)):
	n += 1
	lang = sys.argv[n]
	lang_po = lang + '.po'
	po_files.append(lang_po)
	subprocess.call(
		[
			msgmerge_executable,
			'-U',
			'--backup=off',
			lang_po,
			pot_file,
		]
	)

os.chdir(saved_cwd)

with open(linguas, 'w') as linguas_file:
	for po_file in po_files:
		linguas_file.write(f"{po_file}\n")
		
'''
'-U',
		'',
		'../locales/j.po',
		'../data/' + meson.project_name() + '.pot'

'''

